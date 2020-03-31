#include "../include/Modulator.h"
#include "../include/Carrier.h"
#include <math.h>
#include <minmax.h>

/*サイン波配列の参照位置の移動量の設定
.Modulatorのポインタ
.変調周波数*/
static Modulator_SetIndexMoveValue(Modulator* modulator, const uint32_t mod_freq)
{
	uint32_t min_value = min(SIN_WAVE_NUM, 0x1000);
	uint32_t max_value = max(SIN_WAVE_NUM, 0x1000);

	modulator->index_move_value = (mod_freq / modulator->sample_freq) << (16 - (max_value - min_value));
}

/*1サンプル分の波形の取得
.Modulatorのポインタ
.サイン波配列の参照位置のオフセット
.フィードバック用過去データ格納バッファ
return 1サンプル分の波形*/
static int32_t Modulator_GenerateSignal(Modulator* modulator, const int32_t index_offset, int32_t* feedback_signal)
{
	int32_t gain = Envelope_UpDate(&modulator->envelope, &modulator->state) >> (sizeof(modulator->sin_wave[0]) * 8);
	
	uint32_t shift = (sizeof(uint32_t) * 8) - (uint32_t)log2(SIN_WAVE_NUM);

	if (feedback_signal != 0) {
		(*feedback_signal) = (modulator->sin_wave[modulator->table_index >> shift] * gain) >> (uint32_t)log2(SIN_WAVE_NUM);
	}

	return modulator->sin_wave[(modulator->table_index + index_offset) >> shift] * gain;
}

#ifndef SOUND_8BIT
void Modulator_Constructor(Modulator* modulator, const uint32_t sample_freq, const int16_t* sin_wave)
#else 
void Modulator_Constructor(Modulator* modulator, const uint32_t sample_freq, const uint8_t* sin_wave)
#endif
{
	modulator->index_move_value = 0;
	modulator->mod_freq         = 0;
	modulator->sample_freq      = sample_freq;
	modulator->sin_wave         = sin_wave;
	modulator->state            = MOD_STATE_STOP;
	modulator->table_index      = 0;

	Envelope_Constructor(&modulator->envelope, modulator->sample_freq);
	Feedback_Constructor(&modulator->feedback);
}

void Modulator_SetModulationFrequencyRatio(Modulator* modulator, const float modulation_freq_ratio)
{
	modulator->mod_freq = (uint32_t)(modulation_freq_ratio * (float)0x10000);
}

void Modulator_SetModulationFrequency(Modulator* modulator, const uint32_t generate_freq)
{
	Modulator_SetIndexMoveValue(modulator, (generate_freq >> 8) * (modulator->mod_freq >> 8));
}

void Modulator_Start(Modulator* modulator)
{
	if (modulator->state == MOD_STATE_STOP) {
		modulator->state               = MOD_STATE_EXECUTION;
		modulator->feedback.old_signal = 0;
	}
}

void Modulator_Stop(Modulator* modulator)
{
	if (modulator->state == MOD_STATE_EXECUTION) {
		if (modulator->envelope.state != EV_STATE_RELEASE) {
			Envelope_SetState(&modulator->envelope, EV_STATE_NOTEOFF);
		}
	}
	else {
		if (modulator->state != MOD_STATE_STOP) {
			modulator->state = MOD_STATE_STOP;
		}
	}
}

int32_t Modulator_GenerateSignalSimple(Modulator* modulator)
{
	if (modulator->state == MOD_STATE_STOP) {
		return 0;
	}

	int32_t signal = Modulator_GenerateSignal(modulator, 0, 0);
	modulator->table_index += modulator->index_move_value;

	return signal;
}

int32_t Modulator_GenerateSignalFB(Modulator* modulator)
{
	if (modulator->state == MOD_STATE_STOP) {
		return 0;
	}

	int32_t signal = Modulator_GenerateSignal(modulator, modulator->feedback.old_signal * modulator->feedback.gain, 
		&modulator->feedback.old_signal);
	modulator->table_index += modulator->index_move_value;

	return signal;
}

int32_t Modulator_GenerateSignalModulation(Modulator* modulator, const int32_t mod_signal)
{
	if (modulator->state == MOD_STATE_STOP) {
		return 0;
	}

	int32_t signal = Modulator_GenerateSignal(modulator, mod_signal, 0);
	modulator->table_index += modulator->index_move_value;

	return signal;
}
