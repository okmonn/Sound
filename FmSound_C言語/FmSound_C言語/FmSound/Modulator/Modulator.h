#pragma once
#include "../Operator/Operator.h"
#include "../Parameter/Parameter.h"

/*パラメータ数*/
#define OP_NUM 4

typedef struct {
	/*オペレータ*/
	Operator op[OP_NUM];
	/*サンプリング周波数*/
	uint32_t sample;
	/*生成周波数*/
	uint32_t freq;
}Modulator; 

/*コンストラクタ
.Modulatorのポインタ
.サンプリング周波数*/
void Modulator_Constructor(Modulator* mod, const uint32_t sample);
/*パラメータの適用
.Modulatorのポインタ
.Parameterのポインタ*/
void Modulator_ApplyParameter(Modulator* mod, const Parameter* parameter, const uint32_t num);
/*信号生成の開始
.Modulatorのポインタ*/
void Modulator_Start(Modulator* mod);
/*信号生成の停止
.Modulatorのポインタ*/
void Modulator_Stop(Modulator* mod);
/*生成周波数の設定
.Modulatorのポインタ
.生成周波数*/
void Modulator_SetFreq(Modulator* mod, const uint32_t freq);
