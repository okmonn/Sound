#pragma once
#include <stdint.h>

typedef struct {
	/*フィードバック用入力レベル*/
	uint32_t gain;
	/*前回の出力データ*/
	int32_t data;
}Feedback;

/*コンストラクタ
.Feedbackのポインタ*/
void Feedback_Constructor(Feedback* fb);
/*フィードバック用入力レベルの設定
.Feedbackのポインタ
.入力レベル比率*/
void Feedback_SetGain(Feedback* fb, const float gain);
