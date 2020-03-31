#include "../include/XAudio2.h"
#include <assert.h>

#pragma comment(lib, "xaudio2.lib")

/*XAudio2のコア部分*/
IXAudio2* audio = 0;
/*マスタリングボイス*/
IXAudio2MasteringVoice* mastering_voice = 0;

/*エンジン部分の生成
.サンプリング周波数
.チャンネル数*/
static void XAudio2_EngineStart(const uint32_t sample_freq, const uint16_t channel)
{
	int32_t hr = CoInitializeEx(0, COINIT_MULTITHREADED);
	assert(hr == S_OK);

	hr = XAudio2Create(&audio, XAUDIO2_DEBUG_ENGINE, XAUDIO2_USE_DEFAULT_PROCESSOR);
	assert(hr == S_OK);

	hr = audio->lpVtbl->CreateMasteringVoice(audio, &mastering_voice, channel, sample_freq, 0, 0, 0, AudioCategory_Other);
	assert(hr == S_OK);
}

/*サウンドフォーマットの取得
.サンプリング周波数
.量子化ビット数
.チャンネル数
return フォーマット*/
static WAVEFORMATEX XAudio2_GetFormat(uint32_t sample_freq, const uint16_t quantization_bits, const uint16_t channel)
{
	WAVEFORMATEX fmt;
	fmt.cbSize          = sizeof(WAVEFORMATEX);
	fmt.wFormatTag      = WAVE_FORMAT_PCM;
	fmt.nChannels       = channel;
	fmt.nSamplesPerSec  = sample_freq;
	fmt.wBitsPerSample  = quantization_bits;
	fmt.nBlockAlign     = (fmt.wBitsPerSample / 8) * fmt.nChannels;
	fmt.nAvgBytesPerSec = fmt.nSamplesPerSec * fmt.nBlockAlign;

	return fmt;
}

void XAudio2_Constructor(XAudio2* xaudio2, const uint32_t sample_freq, const uint16_t quantization_bits, const uint16_t channel)
{
	if (audio == 0) {
		XAudio2_EngineStart(sample_freq, channel);
	}

	WAVEFORMATEX fmt = XAudio2_GetFormat(sample_freq, quantization_bits, channel);
	int32_t hr = audio->lpVtbl->CreateSourceVoice(audio, &xaudio2->rsc_voice, (WAVEFORMATEX*)&fmt, 0, 1.0f, 0, 0, 0);
	assert(hr == S_OK);

	xaudio2->state = XAUDIO2_STATE_STOP;
}

void XAudio2_Destructor(XAudio2* xaudio2, const uint32_t xaudio2_num)
{
	for (uint32_t i = 0; i < xaudio2_num; ++i) {
		xaudio2[i].rsc_voice->lpVtbl->DestroyVoice(xaudio2[i].rsc_voice);
	}
	mastering_voice->lpVtbl->DestroyVoice(mastering_voice);
	audio->lpVtbl->Release(audio);
	CoUninitialize();
}

#ifndef SOUND_8BIT
void XAudio2_Play(XAudio2* xaudio2, const int16_t* wave_buffer, const uint32_t buffer_size)
#else
void XAudio2_Play(XAudio2* xaudio2, const uint8_t* wave_buffer, const uint32_t buffer_size)
#endif
{
	if (xaudio2->state != XAUDIO2_STATE_EXECUTION) {
		int32_t hr = xaudio2->rsc_voice->lpVtbl->Start(xaudio2->rsc_voice, 0, 0);
		assert(hr == S_OK);

		xaudio2->state = XAUDIO2_STATE_EXECUTION;
	}

	XAUDIO2_BUFFER buffer;
	buffer.AudioBytes = buffer_size;
	buffer.Flags      = XAUDIO2_END_OF_STREAM;
	buffer.LoopBegin  = 0;
	buffer.LoopCount  = 0;
	buffer.LoopLength = 0;
	buffer.pAudioData = (uint8_t*)wave_buffer;
	buffer.pContext   = 0;
	buffer.PlayBegin  = 0;
	buffer.PlayLength = 0;

	int32_t hr = xaudio2->rsc_voice->lpVtbl->SubmitSourceBuffer(xaudio2->rsc_voice, &buffer, 0);
	assert(hr == S_OK);
}

void XAudio2_Stop(XAudio2* xaudio2)
{
	if (xaudio2->state != XAUDIO2_STATE_STOP) {
		int32_t hr = xaudio2->rsc_voice->lpVtbl->Stop(xaudio2->rsc_voice, XAUDIO2_PLAY_TAILS, 0);
		assert(hr == S_OK);
	}
}
