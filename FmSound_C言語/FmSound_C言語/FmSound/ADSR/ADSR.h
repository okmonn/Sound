#pragma once
#include <stdint.h>

typedef struct {
	/*アタック時の最大入力レベル*/
	uint32_t attackLevel;
	/*アタック時の持続サンプル数*/
	uint32_t attack;
	/*ディケイ時の持続サンプル数*/
	uint32_t decay;
	/*サスティン時の最大入力レベル*/
	uint32_t sustainLevel;
	/*リリース時の持続サンプル数*/
	uint32_t release;
}ADSR;

/*コンストラクタ
.ADSRのポインタ*/
void ADSR_Constructor(ADSR* adsr);
/*アタック時の最大入力レベルの設定
.ADSRのポインタ
.入力レベル比率*/
void ADSR_SetAttackLevel(ADSR* adsr, const float level);
/*サスティン時の最大入力レベルの設定
.ADSRのポインタ
.入力レベル比率*/
void ADSR_SetSustainLevel(ADSR* adsr, const float level);
