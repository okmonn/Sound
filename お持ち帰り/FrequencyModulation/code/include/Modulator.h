#ifndef FM_MODULATOR
#define FM_MODULATOR

/*8BIT音源切り替え用*/
#define SOUND_8BIT

#include "Envelope.h"
#include "Feedback.h"

/*モジュレータの動作停止状態*/
#define MOD_STATE_STOP      0x00
/*モジュレータの動作中状態*/
#define MOD_STATE_EXECUTION 0x01

typedef struct {
	/*エンベロープ*/
	Envelope envelope;
	/*フィードバック*/
	Feedback feedback;
	/*サンプリング周波数*/
	uint32_t sample_freq;
	/*現在のサイン波配列の参照番号*/
	uint32_t table_index;
	/*サイン波配列の参照位置の移動量*/
	uint32_t index_move_value;
	/*変調周波数の比率(小数部：16bit)*/
	uint32_t mod_freq;
	/*サイン波配列*/
#ifndef SOUND_8BIT
	const int16_t* sin_wave;
#else
	const uint8_t* sin_wave;
#endif
	/*動作状態*/
	uint8_t state;
} Modulator;

/*コンストラクタ
.Modulatorのポインタ
.サンプリング周波数
.サイン波配列のポインタ*/
#ifndef SOUND_8BIT
void Modulator_Constructor(Modulator* modulator, const uint32_t sample_freq, const int16_t* sin_wave);
#else
void Modulator_Constructor(Modulator* modulator, const uint32_t sample_freq, const uint8_t* sin_wave);
#endif
/*変調周波数の比率の設定
.Modulatorのポインタ
.変調周波数の比率(0.0f～1.0f)*/
void Modulator_SetModulationFrequencyRatio(Modulator* modulator, const float modulation_freq_ratio);
/*変調周波数の設定
.Modulatorのポインタ
.生成周波数*/
void Modulator_SetModulationFrequency(Modulator* modulator, const uint32_t generate_freq);
/*信号生成の開始
.Modulatorのポインタ*/
void Modulator_Start(Modulator* modulator);
/*信号生成の停止
.Modulatorのポインタ*/
void Modulator_Stop(Modulator* modulator);
/*1サンプル分の信号の生成
.Modulatorのポインタ
return 1サンプル分の信号*/
int32_t Modulator_GenerateSignalSimple(Modulator* modulator);
/*1サンプル分の信号の生成
.Modulatorのポインタ
return 1サンプル分の信号*/
int32_t Modulator_GenerateSignalFB(Modulator* modulator);
/*1サンプル分の信号の生成
.Modulatorのポインタ
.モジュレーション信号
return 1サンプル分の信号*/
int32_t Modulator_GenerateSignalModulation(Modulator* modulator, const int32_t mod_signal);

#endif
