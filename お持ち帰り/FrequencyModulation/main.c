#include "code/include/Carrier.h"
#include "code/include/XAudio2.h"
#include <math.h>

/*サンプリング周波数*/
#define SAMPLE_PER_SEC 48000
/*量子化ビット数*/
#ifndef SOUND_8BIT
#define QUANTAIZATION_BITS 16
#else 
#define QUANTAIZATION_BITS 8
#endif
/*チャンネル数*/
#define CHANNEL 1

/*パラメータ一覧*/
const Parameter preset[][MOD_NUM] = {
	/*SYN_BASS*//*No2*/
	{{ 0.9f,  0.85f, 0.0f, 1.0f, 0.5f, 0.5f, 0.0f,  1.0f },
	 { 0.8f,  0.2f,  0.0f, 1.5f, 0.5f, 0.5f, 0.0f,  2.0f },
	 { 0.25f, 0.7f,  0.2f, 1.3f, 0.3f, 2.0f, 0.0f,  2.0f },
	 { 0.9f,  0.2f,  0.0f, 0.6f, 0.5f, 0.5f, 0.57f, 2.0f }},
	/*BELL*//*No4*/
	{{ 0.9f,  0.15f, 0.0f, 6.0f, 0.5f, 1.0f, 0.0f,  0.5f },
	 { 0.5f,  0.1f,  0.0f, 6.0f, 0.5f, 3.5f, 0.0f,  1.0f },
	 { 0.85f, 0.4f,  0.0f, 6.3f, 0.5f, 1.0f, 0.0f,  0.5f },
	 { 0.7f,  0.1f,  0.0f, 6.0f, 0.5f, 3.5f, 0.01f, 1.0f }},
	/*DX_PIANO*//*No4*/
	{{ 0.9f,  0.2f,  0.0f,  6.0f, 0.5f, 1.0f, 0.0f,  0.5f },
	 { 0.8f,  0.01f, 0.0f,  0.3f, 0.5f, 1.0f, 0.0f,  1.0f },
	 { 0.85f, 0.3f,  0.15f, 3.5f, 1.0f, 1.0f, 0.0f,  0.5f },
	 { 0.5f,  0.3f,  0.0f,  1.0f, 0.8f, 2.0f, 0.15f, 1.0f }},
	/*SYN_BRASS*//*No0*/
	{{ 0.9f,  0.7f,  0.1f, 0.2f, 1.0f, 1.0f, 0.0f,  2.0f },
	 { 0.25f, 0.7f,  0.0f, 0.5f, 0.5f, 1.0f, 0.0f,  2.0f },
	 { 0.75f, 0.5f,  0.1f, 0.5f, 0.5f, 0.5f, 0.0f,  2.0f },
	 { 0.4f,  0.05f, 0.0f, 0.4f, 0.5f, 3.0f, 0.28f, 1.0f }},
	/*PIPE_ORGAN*//*No7*/
	{{ 1.0f, 1.0f, 0.05f, 0.25f, 0.5f, 0.5f, 0.0f, 0.25f },
	 { 1.0f, 1.0f, 0.1f,  0.25f, 0.8f, 2.0f, 0.0f, 0.25f },
	 { 0.9f, 1.0f, 0.1f,  0.15f, 1.2f, 1.0f, 0.0f, 0.25f },
	 { 0.3f, 0.4f, 0.4f,  0.1f,  1.2f, 4.0f, 1.0f, 0.25f }},
};

/*プリセット用アルゴリズム処理
.Carrierのポインタ
return 信号*/
static int32_t Preset_Function_No0(Carrier* carrier)
{
	int32_t signal = Modulator_GenerateSignalFB(&carrier->modulator[3]);
	signal = Modulator_GenerateSignalModulation(&carrier->modulator[2], signal);
	signal = Modulator_GenerateSignalModulation(&carrier->modulator[1], signal);
	signal = Modulator_GenerateSignalModulation(&carrier->modulator[0], signal);
	return signal;
}

/*プリセット用アルゴリズム処理
.Carrierのポインタ
return 信号*/
static int32_t Preset_Function_No1(Carrier* carrier)
{
	int32_t pcm    = Modulator_GenerateSignalFB(&carrier->modulator[3]);
	int32_t signal = Modulator_GenerateSignalSimple(&carrier->modulator[2]);
	signal = Modulator_GenerateSignalModulation(&carrier->modulator[1], signal + pcm);
	signal = Modulator_GenerateSignalModulation(&carrier->modulator[0], signal);
	return signal;
}

/*プリセット用アルゴリズム処理
.Carrierのポインタ
return 信号*/
static int32_t Preset_Function_No2(Carrier* carrier)
{
	int32_t pcm    = Modulator_GenerateSignalFB(&carrier->modulator[3]);
	int32_t signal = Modulator_GenerateSignalSimple(&carrier->modulator[2]);
	signal = Modulator_GenerateSignalModulation(&carrier->modulator[1], signal);
	signal = Modulator_GenerateSignalModulation(&carrier->modulator[0], signal + pcm);
	return signal;
}

/*プリセット用アルゴリズム処理
.Carrierのポインタ
return 信号*/
static int32_t Preset_Function_No3(Carrier* carrier)
{
	int32_t signal = Modulator_GenerateSignalFB(&carrier->modulator[3]);
	signal = Modulator_GenerateSignalModulation(&carrier->modulator[2], signal);
	int32_t pcm = Modulator_GenerateSignalSimple(&carrier->modulator[1]);
	signal = Modulator_GenerateSignalModulation(&carrier->modulator[0], signal + pcm);
	return signal;
}

/*プリセット用アルゴリズム処理
.Carrierのポインタ
return 信号*/
static int32_t Preset_Function_No4(Carrier* carrier)
{
	int32_t signal = Modulator_GenerateSignalFB(&carrier->modulator[3]);
	signal = Modulator_GenerateSignalModulation(&carrier->modulator[2], signal);
	int32_t pcm = Modulator_GenerateSignalSimple(&carrier->modulator[1]);
	signal += Modulator_GenerateSignalModulation(&carrier->modulator[0], pcm);
	return signal;
}

/*プリセット用アルゴリズム処理
.Carrierのポインタ
return 信号*/
static int32_t Preset_Function_No5(Carrier* carrier)
{
	int32_t pcm    = Modulator_GenerateSignalFB(&carrier->modulator[3]);
	int32_t signal = Modulator_GenerateSignalModulation(&carrier->modulator[2], pcm);
	signal += Modulator_GenerateSignalModulation(&carrier->modulator[1], pcm);
	signal += Modulator_GenerateSignalModulation(&carrier->modulator[0], pcm);
	return signal;
}

/*プリセット用アルゴリズム処理
.Carrierのポインタ
return 信号*/
static int32_t Preset_Function_No6(Carrier* carrier)
{
	int32_t signal = Modulator_GenerateSignalFB(&carrier->modulator[3]);
	signal  = Modulator_GenerateSignalModulation(&carrier->modulator[2], signal);
	signal += Modulator_GenerateSignalSimple(&carrier->modulator[1]);
	signal += Modulator_GenerateSignalSimple(&carrier->modulator[0]);
	return signal;
}

/*プリセット用アルゴリズム処理
.Carrierのポインタ
return 信号*/
static int32_t Preset_Function_No7(Carrier* carrier)
{
	int32_t signal = Modulator_GenerateSignalFB(&carrier->modulator[3]);
	signal += Modulator_GenerateSignalSimple(&carrier->modulator[2]);
	signal += Modulator_GenerateSignalSimple(&carrier->modulator[1]);
	signal += Modulator_GenerateSignalSimple(&carrier->modulator[0]);
	return signal;
}

/*生成周波数の取得
.ノート番号
return 周波数*/
float GetNoteFrequency(const uint32_t note_no) {
	return 8.2f * powf(powf(2.0f, 1.0f / 12.0f), (float)note_no);
}

/*エントリーポイント*/
int main() {
	Carrier carrier;
	Carrier_Constructor(&carrier, SAMPLE_PER_SEC);
	Carrier_SetGenerateFrequency(&carrier, 440.0f);
	//Carrier_ApplyParameter(&carrier, preset[1], MOD_NUM);
	//Carrier_ApplyAlgorithmFunction(&carrier, &Preset_Function_No4);
	Carrier_Start(&carrier);

	XAudio2 xaudio2;
	XAudio2_Constructor(&xaudio2, SAMPLE_PER_SEC, QUANTAIZATION_BITS, CHANNEL);

#ifndef SOUND_8BIT
	int16_t wave[SAMPLE_PER_SEC * 5];
#else
	uint8_t wave[SAMPLE_PER_SEC * 5];
#endif
	for (uint32_t i = 0; i < sizeof(wave) / sizeof(wave[0]); ++i) {
		if (i == (sizeof(wave) / sizeof(wave[0])) * 0.8) {
			Carrier_Stop(&carrier);
		}

		wave[i] = Carrier_GenerateSignal(&carrier);
	}

	XAudio2_Play(&xaudio2, wave, sizeof(wave));
	while (!(GetKeyState(VK_ESCAPE) & 0x80)) {

	}
	XAudio2_Destructor(&xaudio2, 1);

	return 0;
}
