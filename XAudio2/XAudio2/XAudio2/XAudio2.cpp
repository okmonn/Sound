#include "XAudio2.h"
#include <cassert>
#include <xaudio2.h>

#pragma comment(lib, "xaudio2.lib")

namespace {
	/*インスタンス数*/
	std::uint32_t instance = 0;
}

XAudio2::XAudio2() : 
	audio(nullptr), mastering(nullptr)
{
	CreateAudio();
	CreateMastering();
}

XAudio2::~XAudio2()
{
	for (auto itr = voice.begin(); itr != voice.end();) {
		itr->second->Finish();
		itr = voice.erase(itr);
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
	auto hr = audio->CreateMasteringVoice(&mastering);
	assert(hr == S_OK);
}

std::uint8_t CreateXAudio2(XAudio2** engine)
{
	if (instance == 0) {
		(*engine) = new XAudio2();
		++instance;
		return 1;
	}

	return 0;
}

void DeleteXAudio2(XAudio2** engine)
{
	if (instance != 0) {
		delete (*engine);
		(*engine) = nullptr;
		--instance;
	}
}
