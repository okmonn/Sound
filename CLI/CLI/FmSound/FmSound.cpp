#include "FmSound.h"
#include <cmath>

/*信号の生成(デフォルト)
.FmSoundのポインタ
return 信号*/
std::int32_t CreateSignalDefault(FmSound* fm) {
	return fm->op[0].CreateSignalSimple();
}

FmSound::FmSound()
{
	sample = 0;
	freq   = 0;
	op.resize(1);
	ApplyFunction(&CreateSignalDefault);
}

FmSound::FmSound(const std::uint32_t& sample, const std::uint32_t& freq)
{
	op.resize(1);
	SetSample(sample);
	SetCreateFreq(freq);
	ApplyFunction(&CreateSignalDefault);
}

void FmSound::Start(void)
{
	for (Operator& i : op) {
		i.Start();
	}
}

void FmSound::Stop(void)
{
	for (Operator& i : op) {
		i.Stop();
	}
}

void FmSound::CreateSignal(std::int16_t* buf, const std::uint32_t& num)
{
	for (std::uint32_t i = 0; i < num; ++i) {
		std::int32_t signal = function(this);
		if (signal > 0x7fff) {
			buf[i] = 0x7fff;
		}
		else if (signal < -0x7fff) {
			buf[i] = -0x7fff;
		}
		else {
			buf[i] = std::int16_t(signal);
		}
	}
}

void FmSound::SetSample(const std::uint32_t& sample)
{
	this->sample = sample;
	for (Operator& i : op) {
		i.SetSpeed(freq, sample);
	}
}

void FmSound::SetCreateFreq(const std::uint32_t& freq)
{
	this->freq = freq;
	for (Operator& i : op) {
		i.SetSpeed(freq, sample);
	}
}

void FmSound::ApplyParameter(const Parameter& parameter)
{
	op.resize(parameter.param.size());
	for (std::uint32_t i = 0; i < op.size(); ++i) {
		op[i].SetFreqRatio(parameter.param[i].freq_ratio);
		op[i].fb.SetGain(parameter.param[i].fb_gain);
		op[i].ev.adsr.SetAttackLevel(std::pow(parameter.param[i].attackLevel, 2.0f) * parameter.param[i].gain);
		op[i].ev.adsr.SetSustainLevel(std::pow(parameter.param[i].sustainLevel, 2.0f) * parameter.param[i].gain);
		op[i].ev.adsr.attack  = std::uint32_t(float(sample) * parameter.param[i].attack);
		op[i].ev.adsr.decay   = std::uint32_t(float(sample) * parameter.param[i].decay);
		op[i].ev.adsr.release = std::uint32_t(float(sample) * parameter.param[i].release);
		
		op[i].SetSpeed(freq, sample);
	}
}

void FmSound::ApplyFunction(const std::function<std::int32_t(FmSound*)>& func)
{
	function = func;
}
