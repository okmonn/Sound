#pragma once
#include "../Envelope/Envelope.h"
#include "../Feedback/Feedback.h"

typedef struct {
	/*エンベロープ*/
	Envelope ev;
	/*ADSR*/
	ADSR adsr;
	/*フィードバック*/
	Feedback fb;
	/*読み出し位置*/
	uint32_t pos;
	/*読み出し速度*/
	uint32_t speed;
	/*生成周波数比率*/
	uint32_t ratio;
	/*動作フラグ*/
	uint8_t flag;
}Operator;

/*コンストラクタ
.Operatorのポインタ*/
void Operator_Constructor(Operator* op);
/*信号生成の開始
.Operatorのポインタ*/
void Operator_Start(Operator* op);
/*信号生成の停止
.Operatorのポインタ*/
void Operator_Stop(Operator* op);
/*信号の生成(モジュレーションなし、フィードバックなし)
.Operatorのポインタ
return 信号*/
int32_t CreateSignalSimple(Operator* op);
/*信号の生成(モジュレーションなし、フィードバックあり)
.Operatorのポインタ
return 信号*/
int32_t CreateSignalFB(Operator* op);
/*信号の生成(モジュレーションあり、フィードバックなし)
.Operatorのポインタ
.モジュレーション信号
return 信号*/
int32_t CreateSignalModulation(Operator* op, const int32_t mod);
/*読み出し速度の設定
.Operatorのポインタ
.生成周波数
.サンプリング周波数*/
void Operator_SetSpeed(Operator* op, const uint32_t freq, const uint32_t sample);
/*生成周波数比率の設定
.Operatorのポインタ
.生成周波数比率*/
void Operator_SetRatio(Operator* op, const float ratio);
