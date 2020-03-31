#include "../include/Carrier.h"
#include <math.h>

/*デフォルトのパラメータ*/
static const Parameter default_param = {
	1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f
};

/*サイン波配列の設定
.Carrierのポインタ*/
static Carrier_SetSinWave(Carrier* carrier)
{
	for (uint32_t i = 0; i < SIN_WAVE_NUM; ++i) {
		float tmp = sinf(2.0f * acosf(-1.0f) * i / (SIN_WAVE_NUM));
#ifndef SOUND_8BIT
		carrier->sin_wave[i] = (int16_t)(0x7FFF * tmp);
#else
		carrier->sin_wave[i] = (uint8_t)(0x7F * (tmp + 1.0f));
#endif
	}
}

/*デフォルトのアルゴリズム処理関数
.Carrierのポインタ
return 1サンプル分の信号*/
static int32_t Carrier_DefaultAlgorithmFunction(Carrier* carrier)
{
	return Modulator_GenerateSignalSimple(&carrier->modulator[0]);
}

/*クリッピング
.1サンプル分の信号
return クリッピングされた信号*/
int32_t Carrier_Clipping(const int32_t signal)
{
#ifndef SOUND_8BIT
	if (signal >= 0x7FFF) {
		return 0x7FFF;
	}
	else if (signal <= -0x7FFF) {
		return -0x7FFF;
	}
#else
	if (signal >= 0xFF) {
		return 0xFF;
	}
#endif

	return signal;
}

void Carrier_Constructor(Carrier* carrier, const uint32_t sample_freq)
{
	carrier->sample_freq = sample_freq;
	Carrier_SetSinWave(carrier);
	for (uint32_t i = 0; i < MOD_NUM; ++i) {
		Modulator_Constructor(&carrier->modulator[i], carrier->sample_freq, carrier->sin_wave);
	}
	Carrier_SetGenerateFrequency(carrier, 440.0f);
	Carrier_ApplyParameter(carrier, &default_param, 1);
	Carrier_ApplyAlgorithmFunction(carrier, &Carrier_DefaultAlgorithmFunction);
}

void Carrier_SetGenerateFrequency(Carrier* carrier, const float generate_freq)
{
	carrier->generate_freq = (uint32_t)(generate_freq * (float)0x10000);
	for (uint32_t i = 0; i < MOD_NUM; ++i) {
		Modulator_SetModulationFrequency(&carrier->modulator[i], carrier->generate_freq);
	}
}

void Carrier_ApplyParameter(Carrier* carrier, const Parameter* parameter, const uint32_t parameter_num)
{
	if (parameter_num > MOD_NUM) {
		return;
	}

	for (uint32_t i = 0; i < parameter_num; ++i) {
		Modulator_SetModulationFrequencyRatio(&carrier->modulator[i], parameter[i].mod_freq_ratio);
		Attack_SetMaxGain(&carrier->modulator[i].envelope.attack, parameter[i].attack_gain_ratio, parameter[i].volume_ratio);
		Sustain_SetMaxGain(&carrier->modulator[i].envelope.sustain, parameter[i].sustain_gain_ratio, parameter[i].volume_ratio);
		Attack_SetDuration(&carrier->modulator[i].envelope.attack, (uint32_t)(carrier->sample_freq * parameter[i].attack_duration_ratio));
		Decay_SetDuration(&carrier->modulator[i].envelope.decay, (uint32_t)(carrier->sample_freq * parameter[i].decay_duration_ratio));
		Release_SetDuration(&carrier->modulator[i].envelope.release, (uint32_t)(carrier->sample_freq * parameter[i].release_duration_ratio));
		Feedback_SetGain(&carrier->modulator[i].feedback, parameter[i].feedback_gain_ratio);

		Modulator_SetModulationFrequency(&carrier->modulator[i], carrier->generate_freq);
	}
}

void Carrier_ApplyAlgorithmFunction(Carrier* carrier, int32_t(*functio)(Carrier*))
{
	carrier->function = functio;
}

void Carrier_Start(Carrier* carrier)
{
	for (uint32_t i = 0; i < MOD_NUM; ++i) {
		Modulator_Start(&carrier->modulator[i]);
	}
}

void Carrier_Stop(Carrier* carrier)
{
	for (uint32_t i = 0; i < MOD_NUM; ++i) {
		Modulator_Stop(&carrier->modulator[i]);
	}
}

#ifndef SOUND_8BIT
int16_t Carrier_GenerateSignal(Carrier* carrier)
#else
uint8_t Carrier_GenerateSignal(Carrier* carrier)
#endif
{
	return Carrier_Clipping(carrier->function(carrier) >> ((sizeof(uint32_t) - sizeof(carrier->sin_wave[0])) * 8));
}
