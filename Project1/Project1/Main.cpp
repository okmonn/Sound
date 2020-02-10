#include <XAudio2.h>
#include <cassert>
#include <combaseapi.h>

#include "FmSound.h"

#pragma comment(lib, "XAudio2.lib")

namespace {
	const std::uint32_t sample = 48000;
	const std::uint8_t bit = 8;
	const std::uint8_t channel = 1;
}

int main() {
	auto hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(hr == S_OK);

	XAudio2* engine = nullptr;
	hr = CreateXAudio2(&engine);
	Voice voice(engine, sample, bit, channel);
	voice.Play();

	FmSound fm(sample);

	bool key = false;
	std::uint8_t buf[sample / 100];
	while (!(GetKeyState(VK_ESCAPE) & 0x80)) {
		if (GetKeyState(VK_SPACE) & 0x80) {
			if (key == false) {
				key = true;
				fm.Start();
			}
		}
		else {
			if (key == true) {
				key = false;
				fm.Stop();
			}
		}

		fm.CreateSignal(buf, _countof(buf));
		voice.AddSoundQueue(buf, _countof(buf));
	}

	DeleteXAudio2(&engine);
	CoUninitialize();
	return 0;
}