#pragma once
#include "../ADSR/ADSR.h"

/*エンベロープの動作状態*/
typedef enum {
	/*完了*/
	done,
	/*アタック*/
	attack,
	/*ディケイ*/
	decay,
	/*サスティン*/
	sustain,
	/*リリース*/
	release,
	/*エンベロープの動作状態の最大数*/
	max
}EV_STATE;

typedef struct {
	/*動作状態*/
	EV_STATE state;
	/*現在の入力レベル*/
	uint32_t gain;
	/*入力レベル変化速度*/
	uint32_t delta;
	/*入力レベル変化カウンタ*/
	uint32_t cnt;
}Envelope;

/*コンストラクタ
.Envelopeのポインタ*/
void Envelope_Constructor(Envelope* ev);
/*動作状態の設定
.Envelopeのポインタ
.ADSRのポインタ
.エンベロープの動作状態
return 動作フラグ*/
uint8_t Envelope_SetState(Envelope* ev, const ADSR* adsr, const EV_STATE state);
