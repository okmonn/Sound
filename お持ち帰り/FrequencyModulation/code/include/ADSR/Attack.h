#ifndef ADSR_ATTACK
#define ADSR_ATTACK

#include <stdint.h>

typedef struct {
	/*最大ゲイン(0x00～0xFFFFFFFF)*/
	uint32_t max_gain;
	/*持続期間(サンプル数)*/
	uint32_t duration;
} Attack;

/*コンストラクタ
.Attackのポインタ*/
void Attack_Constructor(Attack* attack);
/*最大ゲインの設定
.Attackのポインタ
.ゲイン比率(0.0f～1.0f)
.音量比率*/
void Attack_SetMaxGain(Attack* attack, const float gain_ratio, const float valume_ratio);
/*持続期間の設定
.Attackのポインタ
持続期間(サンプル数)*/
void Attack_SetDuration(Attack* attack, const uint32_t duration);

#endif
