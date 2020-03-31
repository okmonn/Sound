#ifndef ADSR_SUSTAIN
#define ADSR_SUSTAIN

#include <stdint.h>

typedef struct {
	/*最大ゲイン(0x00～0xFFFFFFFF)*/
	uint32_t max_gain;
} Sustain;

/*コンストラクタ
.Sustainのポインタ*/
void Sustain_Constructor(Sustain* sustain);
/*最大ゲインの設定
.Sustainのポインタ
.ゲイン比率(0.0f～1.0f)
.音量調節*/
void Sustain_SetMaxGain(Sustain* sustain, const float gain_ratio, const float valume_ratio);

#endif
