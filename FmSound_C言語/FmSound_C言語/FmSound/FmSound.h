#pragma once
#include "Modulator/Modulator.h"

typedef struct {
	/*モジュレータ*/
	Modulator mod;
	/*関数ポインタ*/
	int32_t(*algorithm)(Modulator*);
}FmSound;

/*コンストラクタ
.FmSoundのポインタ
.サンプリング周波数*/
void FmSound_Constructor(FmSound* fm, const uint32_t sample);
/*アルゴリズム処理の適用
.FmSoundのポインタ
.関数ポインタ*/
void ApplyAlgorithmFunction(FmSound* fm, int32_t(*func)(Modulator*));
/*パラメータの適用
.FmSoundのポインタ
.Parameterのポインタ
.Parameterの数*/
void ApplyParameter(FmSound* fm, const Parameter* parameter, const uint32_t num);
/*信号生成の開始
.FmSoundのポインタ*/
void Start(FmSound* fm);
/*信号生成の停止
.FmSoundのポインタ*/
void Stop(FmSound* fm);
/*信号の生成
.FmSoundのポインタ
.格納バッファ
.バッファ数*/
void CreateSignal(FmSound* fm, int16_t* buf, const uint32_t num);
/*生成周波数の設定
.FmSoundのポインタ
.生成周波数*/
void SetFreq(FmSound* fm, const uint32_t freq);