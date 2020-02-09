#include "FmSound/FmSound.h"
#include "XAudio2/XAudio.h"
#include <cassert>
#include <Windows.h>
#include <combaseapi.h>

namespace {
	const std::uint32_t sample = 48000;
	const std::uint8_t bit     = 8;
	const std::uint8_t channel = 1;
}

int main() {
	auto hr = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	assert(hr == S_OK);
	
	XAudio* engine = nullptr;
	hr = CreateXAudio(&engine);
	assert(hr == S_OK);
	SourceVoice voice(engine, sample, bit, channel);

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
		voice.Play(buf, _countof(buf));
	}

	Release(&engine);
	CoUninitialize();
	return 0;
}