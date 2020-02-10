#include "Window/Window.h"

#include <FmSound.h>
#include <XAudio2.h>

#pragma comment(lib, "XAudio2.lib")
#pragma comment(lib, "FmSound.lib")

namespace {
	/*サンプリング周波数*/
	const std::uint32_t sample = 48000;
	/*量子化ビット数*/
	const std::uint8_t bit     = 16;
	/*チャンネル数*/
	const std::uint8_t channel = 1;
	/*パラメータのプリセット*/
	Parameter<float> preset[] = {
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
			std::int32_t pcm    = fm->op[3].CreateSignalFB();
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

float GetNoteFreq(const std::uint32_t& note) {
	return 8.1758f * std::pow(std::pow(2.0f, 1.0f / 12.0f), float(note));
}

int main() {
	XAudio2* engine = nullptr;
	CreateXAudio2(&engine);
	Voice voice(engine, sample, bit, channel);
	voice.Play();

	FmSound fm(sample);
	fm.SetFreq(GetNoteFreq(60));
	fm.ApplyParameter(preset[0]);
	fm.ApplyAlgorithmFunction(algorithm[2]);

	Window win;

	bool key = false;
	std::int16_t buf[sample / 100];
	fm.Start();
	std::uint32_t cnt = 0;
	while (cnt < 300) {
		++cnt;
		if (cnt == 200) {
			fm.Stop();
		}
		fm.CreateSignal(buf, _countof(buf));
		voice.AddSoundQueue(buf, _countof(buf));

		System::Windows::Forms::Application::DoEvents();
	}

	DeleteXAudio2(&engine);
	return 0;
}