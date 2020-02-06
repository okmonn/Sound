#include "FmSound/FmSound.h"
#include "XAudio2/XAudio.h"

#include "CLI/Window/Window.h"

#include <cassert>
#include <combaseapi.h>

namespace {
	/*サンプリング周波数*/
	const std::uint32_t sample = 48000;
	/*量子化ビット数*/
	const std::uint8_t bit     = 16;
	/*チャンネル数*/
	const std::uint8_t channel = 1;
	/*パラメータのプリセット*/
	Parameter preset[] = {
		/*SYN_BASS(2)*/
		{{0.9f , 0.85f, 0.0f, 1.0f, 0.5f, 0.5f, 0.0f , 2.0f},
		 {0.8f , 0.2f , 0.0f, 1.5f, 0.5f, 0.5f, 0.0f , 2.0f},
		 {0.25f, 0.7f , 0.2f, 1.3f, 0.3f, 0.5f, 0.0f , 2.0f},
		 {0.9f , 0.2f , 0.0f, 0.6f, 0.5f, 0.5f, 0.57f, 2.0f}},
		/*BELL(4)*/
		{{0.9f , 0.15f, 0.0f, 6.0f, 0.5f, 1.0f, 0.0f , 0.5f},
		 {0.5f , 0.1f , 0.0f, 6.0f, 0.5f, 3.5f, 0.0f , 1.0f},
		 {0.85f, 0.4f , 0.0f, 6.3f, 0.5f, 1.0f, 0.0f , 0.5f},
		 {0.7f , 0.1f , 0.0f, 6.0f, 0.5f, 3.5f, 0.01f, 1.0f}},
		/*DX_PIANO(4)*/
		{{0.9f , 0.2f , 0.0f , 6.0f, 0.5f, 1.0f, 0.0f , 0.5f},
		 {0.8f , 0.01f, 0.0f , 0.3f, 0.5f, 1.0f, 0.0f , 1.0f},
		 {0.85f, 0.3f , 0.15f, 3.5f, 1.0f, 1.0f, 0.0f , 0.5f},
		 {0.5f , 0.3f , 0.0f , 1.0f, 0.8f, 2.0f, 0.15f, 1.0f}},
		/*SYN_BRASS(0)*/
		{{0.9f , 0.7f , 0.1f, 0.2f, 1.0f, 1.0f, 0.0f , 2.0f},
		 {0.25f, 0.7f , 0.0f, 0.5f, 0.5f, 1.0f, 0.0f , 2.0f},
		 {0.75f, 0.5f , 0.1f, 0.5f, 0.5f, 0.5f, 0.0f , 2.0f},
		 {0.4f , 0.05f, 0.0f, 0.4f, 0.5f, 3.0f, 0.28f, 1.0f}},
		/*PIPE_ORGAN(7)*/
		{{1.0f, 1.0f, 0.05f, 0.25f, 0.5f, 0.5f, 0.0f, 0.25f},
		 {1.0f, 1.0f, 0.1f , 0.25f, 0.8f, 2.0f, 0.0f, 0.25f},
		 {0.9f, 1.0f, 0.1f , 0.15f, 1.2f, 1.0f, 0.0f, 0.25f},
		 {0.3f, 0.4f, 0.4f , 0.1f , 1.2f, 4.0f, 1.0f, 0.25f}}
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
			std::int32_t pcm    = fm->op[3].CreateSignalFB();
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
			std::int32_t pcm    = fm->op[3].CreateSignalFB();
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
	XAudio* engine = nullptr;
	auto hr = CreateXAudio(&engine);
	assert(hr == 0);
	SourceVoice voice(engine, sample, bit, channel);

	FmSound fm(sample);
	bool key = false;
	int16_t buf[sample / 100];

	System::Windows::Forms::MessageBox::Show("テストです", "Test",
		System::Windows::Forms::MessageBoxButtons::OK,
		System::Windows::Forms::MessageBoxIcon::Information);


	CLI::Window win;
	while (win.ShowDialog() != System::Windows::Forms::DialogResult::Cancel) {

		fm.CreateSignal(buf, _countof(buf));
		voice.Play(buf, _countof(buf));
	}

	return 0;
}