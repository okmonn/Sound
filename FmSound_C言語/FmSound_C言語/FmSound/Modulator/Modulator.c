#include "Modulator.h"
#include <math.h>

void Modulator_Constructor(Modulator* mod, const uint32_t sample)
{
	mod->sample = sample;
	mod->freq   = 0;
	for (uint32_t i = 0; i < OP_NUM; ++i) {
		Operator_Constructor(&mod->op[i]);
	}
}

void Modulator_ApplyParameter(Modulator* mod, const Parameter* parameter, const uint32_t num)
{
	if (num <= OP_NUM) {
		uint32_t i = 0;
		for (; i < num; ++i) {
			mod->op[i].adsr.attack  = (uint32_t)((float)(mod->sample) * parameter[i].attack);
			mod->op[i].adsr.decay   = (uint32_t)((float)(mod->sample) * parameter[i].decay);
			mod->op[i].adsr.release = (uint32_t)((float)(mod->sample) * parameter[i].release);

			Operator_SetRatio(&mod->op[i], parameter[i].freq_ratio);
			ADSR_SetAttackLevel(&mod->op[i].adsr, powf(parameter[i].attackLevel, 2.0f) * parameter[i].gain_ratio);
			ADSR_SetSustainLevel(&mod->op[i].adsr, powf(parameter[i].sustainLevel, 2.0f) * parameter[i].gain_ratio);
			Feedback_SetGain(&mod->op[i].fb, parameter[i].fb_gain);
		}

		Parameter tmp;
		Parameter_Constructor(&tmp);
		for (; i < OP_NUM; ++i) {
			mod->op[i].adsr.attack  = (uint32_t)((float)(mod->sample) * tmp.attack);
			mod->op[i].adsr.decay   = (uint32_t)((float)(mod->sample) * tmp.decay);
			mod->op[i].adsr.release = (uint32_t)((float)(mod->sample) * tmp.release);

			Operator_SetRatio(&mod->op[i], tmp.freq_ratio);
			ADSR_SetAttackLevel(&mod->op[i].adsr, powf(tmp.attackLevel, 2.0f) * tmp.gain_ratio);
			ADSR_SetSustainLevel(&mod->op[i].adsr, powf(tmp.sustainLevel, 2.0f) * tmp.gain_ratio);
			Feedback_SetGain(&mod->op[i].fb, tmp.fb_gain);
		}
	}
}

void Modulator_Start(Modulator* mod)
{
	for (uint32_t i = 0; i < OP_NUM; ++i) {
		Operator_Start(&mod->op[i]);
	}
}

void Modulator_Stop(Modulator* mod)
{
	for (uint32_t i = 0; i < OP_NUM; ++i) {
		Operator_Stop(&mod->op[i]);
	}
}

void Modulator_SetFreq(Modulator* mod, const uint32_t freq)
{
	mod->freq = freq << 16;
	for (uint32_t i = 0; i < OP_NUM; ++i) {
		Operator_SetSpeed(&mod->op[i], mod->freq, mod->sample);
	}
}
