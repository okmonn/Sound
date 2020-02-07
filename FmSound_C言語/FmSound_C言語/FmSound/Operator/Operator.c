#include "Operator.h"
#include "../SinTbl/SinTbl.h"

void Operator_Constructor(Operator* op)
{
	op->pos   = 0;
	op->speed = 0;
	op->flag  = 0;

	Envelope_Constructor(&op->ev);
	ADSR_Constructor(&op->adsr);
	Feedback_Constructor(&op->fb);
	Operator_SetRatio(op, 1.0f);
}

void Operator_Start(Operator* op)
{
	op->fb.data = 0;
	Envelope_Constructor(&op->ev);
	op->flag = Envelope_SetState(&op->ev, &op->adsr, (EV_STATE)((uint32_t)(op->ev.state + 1) % (uint32_t)(max)));
}

void Operator_Stop(Operator* op)
{
	if (op->flag == 1) {
		if (op->ev.state != release) {
			op->flag = Envelope_SetState(&op->ev, &op->adsr, release);
		}
	}
}

/*エンベロープの更新
.Operatorのポインタ
return 入力レベル*/
int32_t EnvelopeUpDate(Operator* op);
int32_t EnvelopeUpDate(Operator* op)
{
	if (op->ev.cnt == 0 && op->ev.state != sustain) {
		op->flag = Envelope_SetState(&op->ev, &op->adsr, (EV_STATE)((uint32_t)(op->ev.state + 1) % (uint32_t)(max)));
	}

	int32_t gain = (op->ev.gain >> 16);
	op->ev.gain += op->ev.delta;
	--op->ev.cnt;

	return gain;
}

int32_t CreateSignalSimple(Operator* op)
{
	if (op->flag == 0) {
		return 0;
	}

	int32_t signal = sinTbl[(op->pos >> 20)] * EnvelopeUpDate(op);
	op->pos += op->speed;

	return signal;
}

int32_t CreateSignalFB(Operator* op)
{
	if (op->flag == 0) {
		return 0;
	}

	int32_t gain   = EnvelopeUpDate(op);
	int32_t signal = sinTbl[((op->pos + op->fb.data * op->fb.gain) >> 20)] * gain;
	op->fb.data = ((sinTbl[op->pos >> 20] * gain) >> 12);
	op->pos += op->speed;

	return signal;
}

int32_t CreateSignalModulation(Operator* op, const int32_t mod)
{
	if (op->flag == 0) {
		return 0;
	}

	int32_t signal = sinTbl[((op->pos + mod) >> 20)] * EnvelopeUpDate(op);
	op->pos += op->speed;

	return signal;
}

void Operator_SetSpeed(Operator* op, const uint32_t freq, const uint32_t sample)
{
	op->speed = ((((freq >> 8) * (op->ratio >> 8)) / sample) << 16);
}

void Operator_SetRatio(Operator* op, const float ratio)
{
	op->ratio = (uint32_t)(ratio * (float)(0x10000));
}
