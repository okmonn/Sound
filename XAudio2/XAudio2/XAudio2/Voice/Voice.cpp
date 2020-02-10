#include "Voice.h"
#include "../XAudio2.h"

#include <cstdint>
#include <cassert>
#include <xaudio2.h>

#include <ks.h>
#include <ksmedia.h>

namespace {
	/*�X�s�[�J�[��`*/
	const std::uint32_t spk[] = {
		KSAUDIO_SPEAKER_MONO,
		KSAUDIO_SPEAKER_STEREO,
	};
}

class VoiceCallback :
	public IXAudio2VoiceCallback {
public:
	/*�R���X�g���N�^*/
	VoiceCallback(Voice* voice) : voice(voice) {}
	/*�f�X�g���N�^*/
	~VoiceCallback() {}
	/*���݂̃o�b�t�@�̍ŏ��̃o�C�g��������O�ɌĂ΂��
	.XAUDIO2_BUFFER.pContext*/
	void __stdcall OnBufferStart(void* pBufferContext) {}
	/*���݂̃o�b�t�@�̍Ō�̃o�C�g������ꂽ�ۂɌĂ΂��
	.XAUDIO2_BUFFER.pContext*/
	void __stdcall OnBufferEnd(void* pBufferContext) {
		voice->read = (voice->read + 1) % voice->wave.size();
	}
	/*���[�v�̏I���ʒu�ɒB�����ۂɌĂ΂��
	.XAUDIO2_BUFFER.pContext*/
	void __stdcall OnLoopEnd(void* pBufferContext) {}
	/*�ŏI�o�b�t�@�̎g�p�����������ۂɌĂ΂��*/
	void __stdcall OnStreamEnd(void) {}
	/*�G���[�����������ۂɌĂ΂��
	.XAUDIO2_BUFFER.pContext*/
	void __stdcall OnVoiceError(void* pBufferContext, long error) {}
	/*�����̏����p�X���I�������ۂɌĂ΂��*/
	void __stdcall OnVoiceProcessingPassEnd() {}
	/*�L���[����f�[�^��ǂݎ��O�ɌĂ΂��
	.�K�v�f�[�^�o�C�g�T�C�Y*/
	void __stdcall OnVoiceProcessingPassStart(std::uint32_t BytesRequired) {
		voice->Submit();
	}

private:
	/*�{�C�X*/
	Voice* voice;
	/*�C�x���g�n���h��*/
	void* handle;
};

Voice::Voice(XAudio2* engine, const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel) :
	engine(engine), callback(std::make_unique<VoiceCallback>(this)), voice(nullptr)
{
	CreateVoice(GetFmt(sample, bit, channel));
	if (this->engine->voice.find(std::uint32_t(this)) == this->engine->voice.end()) {
		this->engine->voice[std::uint32_t(this)] = this;
	}
}

Voice::~Voice()
{
	Finish();
	if (engine != nullptr) {
		if (this->engine->voice.find(std::uint32_t(this)) != this->engine->voice.end()) {
			this->engine->voice.erase(this->engine->voice.find(std::uint32_t(this)));
		}
	}
}

void* Voice::GetFmt(const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel, const std::uint8_t& flag)
{
	static WAVEFORMATEXTENSIBLE fmt{};
	fmt.Format.cbSize               = sizeof(fmt) - sizeof(fmt.Format);
	fmt.Format.nSamplesPerSec       = sample;
	fmt.Format.wBitsPerSample       = bit;
	fmt.Format.nChannels            = channel;
	fmt.Format.nBlockAlign          = (fmt.Format.wBitsPerSample / 8) * fmt.Format.nChannels;
	fmt.Format.nAvgBytesPerSec      = fmt.Format.nSamplesPerSec * fmt.Format.nBlockAlign;
	fmt.Format.wFormatTag           = WAVE_FORMAT_EXTENSIBLE;
	fmt.dwChannelMask               = spk[fmt.Format.nChannels - 1];
	fmt.Samples.wValidBitsPerSample = fmt.Format.wBitsPerSample;
	fmt.SubFormat                   = (flag == 0) ? KSDATAFORMAT_SUBTYPE_PCM : KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;

	return (void*)&fmt;
}

void Voice::CreateVoice(void* fmt)
{
	auto hr = engine->audio->CreateSourceVoice(&voice, (WAVEFORMATEX*)fmt, 0, 1.0f, &(*callback), nullptr, nullptr);
	assert(hr == S_OK);
}

void Voice::Play(void)
{
	auto hr = voice->Start();
	assert(hr == S_OK);
}

void Voice::Stop(void)
{
	auto hr = voice->Stop();
	assert(hr == S_OK);
}

void Voice::AddSoundQueue(const std::int16_t* buf, const std::uint32_t& num)
{
	while (index != read) {}
	wave[index].assign(&buf[0], &buf[num]);
	index = (index + 1) % wave.size();
}

void Voice::Submit(void)
{
	if (wave[read].size() > 0) {
		XAUDIO2_BUFFER buf{};
		buf.AudioBytes = sizeof(wave[read][0]) * wave[read].size();
		buf.pAudioData = (std::uint8_t*)wave[read].data();

		auto hr = voice->SubmitSourceBuffer(&buf, nullptr);
		assert(hr == S_OK);
	}
}

void Voice::Finish(void)
{
	if (voice != nullptr) {
		Stop();
		voice->DestroyVoice();
		voice = nullptr;
	}
	engine = nullptr;
}
