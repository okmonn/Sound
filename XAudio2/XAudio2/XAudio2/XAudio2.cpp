#include "XAudio2.h"
#include <cassert>
#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

namespace {
	/*インスタンス数*/
	std::uint32_t instanceNum = 0;
}

XAudio2::XAudio2() : 
	audio(nullptr), mastering(nullptr)
{
	CreateAudio();
	CreateMastering();
}

XAudio2::~XAudio2()
{
	for (auto& i : list) {
		delete i.second;
	}

	if (mastering != nullptr) {
		mastering->DestroyVoice();
		mastering = nullptr;
	}
	if (audio != nullptr) {
		audio->Release();
		audio = nullptr;
	}
}

void XAudio2::CreateAudio(void)
{
	std::uint32_t flag = 0;
#ifdef _DEBUG
	flag = XAUDIO2_DEBUG_ENGINE;
#endif
	auto hr = XAudio2Create(&audio, flag, XAUDIO2_DEFAULT_PROCESSOR);
	assert(hr == S_OK);
}

void XAudio2::CreateMastering(void)
{
	auto hr = audio->CreateMasteringVoice(&mastering, XAUDIO2_DEFAULT_CHANNELS, XAUDIO2_DEFAULT_SAMPLERATE);
	assert(hr == S_OK);
}

std::uint8_t XAudio2::AddList(void* obj)
{
	if (list.find(std::uint32_t(obj)) == list.end()) {
		list[std::uint32_t(obj)] = obj;
		return 1;
	}

	return 0;
}

std::uint8_t XAudio2::DeleteList(void* obj)
{
	if (list.find(std::uint32_t(obj)) != list.end()) {
		list.erase(list.find(std::uint32_t(obj)));
		return 1;
	}

	return 0;
}

template<typename T>
std::uint8_t XAudio2::CreateVoice(Voice<T>** obj, const std::uint32_t& sample, const std::uint8_t& channel, const std::uint8_t& flag)
{
	(*obj) = new Voice<T>(this, sample, channel, flag);
	if ((*obj) != nullptr) {
		AddList((void*)(*obj));
		return 1;
	}

	return 0;
}
template std::uint8_t XAudio2::CreateVoice(Voice<std::uint8_t>**, const std::uint32_t&, const std::uint8_t& channel, const std::uint8_t&);
template std::uint8_t XAudio2::CreateVoice(Voice<std::int16_t>**, const std::uint32_t&, const std::uint8_t& channel, const std::uint8_t&);

std::uint8_t CreateXAudio2(XAudio2** obj)
{
	if (instanceNum == 0) {
		(*obj) = new XAudio2();
		++instanceNum;
		return 1;
	}

	return 0;
}

void DeleteXAudio2(XAudio2** obj)
{
	if (instanceNum > 0) {
		delete (*obj);
		--instanceNum;
	}
}
