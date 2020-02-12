#include "Voice.h"
#include "../XAudio2.h"
#include "../VoiceCallback.h"
#include <cassert>
#include <ks.h>
#include <ksmedia.h>

namespace {
	/*スピーカー定義*/
	const std::uint32_t spk[] = {
		KSAUDIO_SPEAKER_MONO,
		KSAUDIO_SPEAKER_STEREO,
	};
}

template<typename T>
Voice<T>::Voice(XAudio2* obj, const std::uint32_t& sample, const std::uint8_t& channel, const std::uint8_t& flag) :
	engine(obj), callback(std::make_unique<VoiceCallback<T>>(this)), voice(nullptr), index(0), read(0)
{
	CreateSourceVoice(GetFmt(sample, sizeof(T) * 8, channel, flag));
}
template Voice<std::uint8_t>::Voice(XAudio2*, const std::uint32_t&, const std::uint8_t&, const std::uint8_t&);
template Voice<std::int16_t>::Voice(XAudio2*, const std::uint32_t&, const std::uint8_t&, const std::uint8_t&);

template<typename T>
Voice<T>::~Voice()
{
	if (voice != nullptr) {
		voice->DestroyVoice();
		voice = nullptr;
	}
	engine->DeleteList(this);
}
template Voice<std::uint8_t>::~Voice();
template Voice<std::int16_t>::~Voice();

template<typename T>
void* Voice<T>::GetFmt(const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel, const std::uint8_t& flag)
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
template void* Voice<std::uint8_t>::GetFmt(const std::uint32_t&, const std::uint8_t&, const std::uint8_t&, const std::uint8_t&);
template void* Voice<std::int16_t>::GetFmt(const std::uint32_t&, const std::uint8_t&, const std::uint8_t&, const std::uint8_t&);

template<typename T>
void Voice<T>::CreateSourceVoice(const void* fmt)
{
	auto hr = engine->audio->CreateSourceVoice(&voice, (WAVEFORMATEX*)fmt, XAUDIO2_VOICE_USEFILTER, 1.0f, &(*callback));
	assert(hr == S_OK);
}
template void Voice<std::uint8_t>::CreateSourceVoice(const void*);
template void Voice<std::int16_t>::CreateSourceVoice(const void*);

template<typename T>
void Voice<T>::Play(void)
{
	auto hr = voice->Start();
	assert(hr == S_OK);
}
template void Voice<std::uint8_t>::Play(void);
template void Voice<std::int16_t>::Play(void);

template<typename T>
void Voice<T>::Stop(void)
{
	auto hr = voice->Stop(XAUDIO2_PLAY_TAILS);
	assert(hr == S_OK);
}
template void Voice<std::uint8_t>::Stop(void);
template void Voice<std::int16_t>::Stop(void);

template<typename T>
void Voice<T>::AddSoundBuffer(const T* buf, const std::uint32_t& num)
{
	while (index != read);
	wave[index].assign(&buf[0], &buf[num]);

	XAUDIO2_BUFFER buffer{};
	buffer.AudioBytes = std::uint32_t(sizeof(wave[index][0]) * wave[index].size());
	buffer.pAudioData = (std::uint8_t*)wave[index].data();

	auto hr = voice->SubmitSourceBuffer(&buffer, nullptr);
	assert(hr == S_OK);

	index = (index + 1) % wave.size();
}
template void Voice<std::uint8_t>::AddSoundBuffer(const std::uint8_t*, const std::uint32_t&);
template void Voice<std::int16_t>::AddSoundBuffer(const std::int16_t*, const std::uint32_t&);

template<typename T>
void Voice<T>::Reading(void)
{
	read = (read + 1) % wave.size();
}
template void Voice<std::uint8_t>::Reading(void);
template void Voice<std::int16_t>::Reading(void);
