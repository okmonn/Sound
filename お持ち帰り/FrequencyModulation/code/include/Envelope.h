#ifndef FM_ENVELOPE
#define FM_ENVELOPE

#include "ADSR/Attack.h"
#include "ADSR/Decay.h"
#include "ADSR/Release.h"
#include "ADSR/Sustain.h"

/*エンベロープの動作状態*/
typedef enum {
	/*停止*/
	EV_STATE_STOP,
	/*アタック*/
	EV_STATE_ATTACK,
	/*ディケイ*/
	EV_STATE_DECAY,
	/*サスティン*/
	EV_STATE_SUSTAIN,
	/*ノートオフ*/
	EV_STATE_NOTEOFF,
	/*リリース*/
	EV_STATE_RELEASE,
	/*エンベロープの動作状態最大数*/
	EV_STATE_MAX
} EV_STATE;

typedef struct {
	/*アタック*/
	Attack attack;
	/*ディケイ*/
	Decay decay;
	/*サスティン*/
	Sustain sustain;
	/*リリース*/
	Release release;
	/*ゲイン*/
	uint32_t gain;
	/*ゲイン変化量*/
	int32_t gain_delta;
	/*状態持続カウント*/
	uint32_t state_count;
	/*動作状態*/
	EV_STATE state;
} Envelope;

/*コンストラクタ
.Envelopeのポインタ
.サンプリング周波数*/
void Envelope_Constructor(Envelope* envelope, const uint32_t sample_freq);
/*動作状態の設定
.Envelopeのポインタ
.エンベロープの動作状態*/
void Envelope_SetState(Envelope* envelope, const EV_STATE envelope_state);
/*エンベロープの更新
.Envelopeのポインタ
.モジュレータ動作状態格納バッファ
return ゲイン*/
uint32_t Envelope_UpDate(Envelope* envelope, uint8_t* modulator_state);

#endif
