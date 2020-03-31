#ifndef FM_FEEDBACK
#define FM_FEEDBACK

#include <stdint.h>

typedef struct {
	/*フィードバック用ゲイン比率*/
	uint32_t gain;
	/*1つ前の信号*/
	int32_t old_signal;
} Feedback;

/*コンストラクタ
.Feedbackのポインタ*/
void Feedback_Constructor(Feedback* feedback);
/*フィートバック用ゲイン比率の設定
.Feedbackのポインタ
.ゲイン比率(0.0f～1.0f)*/
void Feedback_SetGain(Feedback* feedback, const float gain_ratio);

#endif
