#include "XAudio2/XAudio2.h"
#include "FmSound/FmSound.h"
#include <Windows.h>

namespace {
	/*サンプリング周波数*/
	const std::uint32_t sample = 48000;
	/*量子化ビット数*/
	const std::uint8_t bit     = 8;
	/*チャンネル数*/
	const std::uint8_t channel = 1;
	/*パラメータのプリセット*/
	Parameter<float> preset[] = {
		{{0.0f , 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f }},
		/*SYN_BASS(2)*/
		{{0.9f , 0.85f, 0.0f, 1.0f, 0.5f, 0.5f, 1.0f, 0.0f },
		 {0.8f , 0.2f , 0.0f, 1.5f, 0.5f, 0.5f, 2.0f, 0.0f },
		 {0.25f, 0.7f , 0.2f, 1.3f, 0.3f, 2.0f, 2.0f, 0.0f },
		 {0.9f , 0.2f , 0.0f, 0.6f, 0.5f, 0.5f, 2.0f, 0.57f}},
		/*BELL(4)*/
		{{0.9f , 0.15f, 0.0f, 6.0f, 0.5f, 1.0f, 0.5f, 0.0f },
		 {0.5f , 0.1f , 0.0f, 6.0f, 0.5f, 3.5f, 1.0f, 0.0f },
		 {0.85f, 0.4f , 0.0f, 6.3f, 0.5f, 1.0f, 0.5f, 0.0f },
		 {0.7f , 0.1f , 0.0f, 6.0f, 0.5f, 3.5f, 1.0f, 0.01f}},
		/*DX_PIANO(4)*/
		{{0.9f , 0.2f , 0.0f , 6.0f, 0.5f, 1.0f, 0.5f, 0.0f },
		 {0.8f , 0.01f, 0.0f , 0.3f, 0.5f, 1.0f, 1.0f, 0.0f },
		 {0.85f, 0.3f , 0.15f, 3.5f, 1.0f, 1.0f, 0.5f, 0.0f },
		 {0.5f , 0.3f , 0.0f , 1.0f, 0.8f, 2.0f, 1.0f, 0.15f}},
		/*SYN_BRASS(0)*/
		{{0.9f , 0.7f , 0.1f, 0.2f, 1.0f, 1.0f, 2.0f, 0.0f },
		 {0.25f, 0.7f , 0.0f, 0.5f, 0.5f, 1.0f, 2.0f, 0.0f },
		 {0.75f, 0.5f , 0.1f, 0.5f, 0.5f, 0.5f, 2.0f, 0.0f },
		 {0.4f , 0.05f, 0.0f, 0.4f, 0.5f, 3.0f, 1.0f, 0.28f}},
		/*PIPE_ORGAN(7)*/
		{{1.0f, 1.0f, 0.05f, 0.25f, 0.5f, 0.5f, 0.25f, 0.0f},
		 {1.0f, 1.0f, 0.1f , 0.25f, 0.8f, 2.0f, 0.25f, 0.0f},
		 {0.9f, 1.0f, 0.1f , 0.15f, 1.2f, 1.0f, 0.25f, 0.0f},
		 {0.3f, 0.4f, 0.4f , 0.1f , 1.2f, 4.0f, 0.25f, 1.0f}}
	};
	/*アルゴリズムごとの処理*/
	std::function<std::int32_t(FmSound*)>algorithm[] = {
		[](FmSound* fm)->std::int32_t {
			return fm->op[0].CreateSignalSimple();
		},
		[](FmSound* fm)->std::int32_t {
			std::int32_t signal = fm->op[3].CreateSignalFB();
			signal = fm->op[2].CreateSignalModulation(signal);
			signal = fm->op[1].CreateSignalModulation(signal);
			signal = fm->op[0].CreateSignalModulation(signal);
			return signal;
		},
		[](FmSound* fm)->std::int32_t {
			std::int32_t pcm = fm->op[3].CreateSignalFB();
			std::int32_t signal = fm->op[2].CreateSignalSimple();
			signal = fm->op[1].CreateSignalModulation(signal + pcm);
			signal = fm->op[0].CreateSignalModulation(signal);
			return signal;
		},
		[](FmSound* fm)->std::int32_t {
			std::int32_t pcm = fm->op[3].CreateSignalFB();
			std::int32_t signal = fm->op[2].CreateSignalSimple();
			signal = fm->op[1].CreateSignalModulation(signal);
			signal = fm->op[0].CreateSignalModulation(signal + pcm);
			return signal;
		},
		[](FmSound* fm)->std::int32_t {
			std::int32_t signal = fm->op[3].CreateSignalFB();
			signal = fm->op[2].CreateSignalModulation(signal);
			std::int32_t pcm = fm->op[1].CreateSignalSimple();
			signal = fm->op[0].CreateSignalModulation(signal + pcm);
			return signal;
		},
		[](FmSound* fm)->std::int32_t {
			std::int32_t signal = fm->op[3].CreateSignalFB();
			signal = fm->op[2].CreateSignalModulation(signal);
			std::int32_t pcm = fm->op[1].CreateSignalSimple();
			signal += fm->op[0].CreateSignalModulation(pcm);
			return signal;
		},
		[](FmSound* fm)->std::int32_t {
			std::int32_t pcm = fm->op[3].CreateSignalFB();
			std::int32_t signal = fm->op[2].CreateSignalModulation(pcm);
			signal += fm->op[1].CreateSignalModulation(pcm);
			signal += fm->op[0].CreateSignalModulation(pcm);
			return signal;
		},
		[](FmSound* fm)->std::int32_t {
			std::int32_t signal = fm->op[3].CreateSignalFB();
			signal = fm->op[2].CreateSignalModulation(signal);
			signal += fm->op[1].CreateSignalSimple();
			signal += fm->op[0].CreateSignalSimple();
			return signal;
		},
		[](FmSound* fm)->std::int32_t {
			std::int32_t signal = fm->op[3].CreateSignalFB();
			signal += fm->op[2].CreateSignalSimple();
			signal += fm->op[1].CreateSignalSimple();
			signal += fm->op[0].CreateSignalSimple();
			return signal;
		},
	};
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
	fm.SetFreq(440U);
	fm.ApplyParameter(preset[1]);
	fm.ApplyAlgorithmFunction(algorithm[3]);

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