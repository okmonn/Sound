#ifndef FM_CARRIER
#define FM_CARRIER

#include "Modulator.h"
#include "Parameter.h"

/*モジュレータ数*/
#define MOD_NUM 4
/*サイン波配列の要素数*/
#define SIN_WAVE_NUM (4096 >> 4)

typedef struct {
	/*サンプリング周波数*/
	uint32_t sample_freq;
	/*生成周波数(小数部：16bit)*/
	uint32_t generate_freq;
	/*サイン波配列*/
#ifndef SOUND_8BIT
	int16_t sin_wave[SIN_WAVE_NUM];
#else
	uint8_t sin_wave[SIN_WAVE_NUM];
#endif
	/*モジュレータ*/
	Modulator modulator[MOD_NUM];
	/*アルゴリズム処理用関数ポインタ
	.Carrierのポインタ
	return 1サンプル分の信号*/
	int32_t(*function)(void* carrier);
} Carrier;

/*コンストラクタ
.Carrierのポインタ
.サンプリング周波数*/
void Carrier_Constructor(Carrier* carrier, const uint32_t sample_freq);
/*生成周波数の設定
.Carrierのポインタ
.生成周波数*/
void Carrier_SetGenerateFrequency(Carrier* carrier, const float generate_freq);
/*パラメータの適応
.Carrierのポインタ
.Parameterのポインタ
.パラメータ数(モジュレータ数以下)*/
void Carrier_ApplyParameter(Carrier* carrier, const Parameter* parameter, const uint32_t parameter_num);
/*アルゴリズム処理関数の適応
.Carrierのポインタ
.関数ポインタ*/
void Carrier_ApplyAlgorithmFunction(Carrier* carrier, int32_t(*functio)(Carrier*));
/*信号生成の開始
.Carrierのポインタ*/
void Carrier_Start(Carrier* carrier);
/*信号生成の停止
.Carrierのポインタ*/
void Carrier_Stop(Carrier* carrier);
/*1サンプル分の信号の生成
.Carrierのポインタ
return 1サンプル分の信号*/
#ifndef SOUND_8BIT
int16_t Carrier_GenerateSignal(Carrier* carrier);
#else
uint8_t Carrier_GenerateSignal(Carrier* carrier);
#endif

#endif
