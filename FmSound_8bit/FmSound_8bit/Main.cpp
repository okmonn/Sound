#include "XAudio2/XAudio2.h"
#include "FmSound/FmSound.h"
#include <Windows.h>

namespace {
	const std::uint32_t sample = 48000;
	const std::uint8_t bit     = 8;
	const std::uint8_t channel = 1;
}

int main() {
	CoInitializeEx(nullptr, COINIT_MULTITHREADED);


	std::uint32_t index = 0;
	std::vector<std::uint8_t>wave(sample);
	for (std::uint32_t i = 0; i < wave.size(); ++i) {
		wave[i] = std::uint8_t((0x7f * std::sin(2.0f * std::acos(-1.0f) * i * 261.0f / wave.size())) + 0x7f);
	}


	XAudio2* engine = nullptr;
	CreateXAudio2(&engine);
	Voice voice(engine, sample, bit, channel);
	voice.Play();

	FmSound fm(sample);
	fm.SetFreq(261U);

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
		/*voice.AddSoundQueue(&wave[index], wave.size() / 100);
		index = (index + 480) % wave.size();*/
	}

	DeleteXAudio2(&engine);

	CoUninitialize();
	return 0;
}