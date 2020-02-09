#include "FmSound.h"
#include <cmath>

/*アルゴリズム関数(デフォルト)
.FmSoundのポインタ*/
std::int32_t Algorithm_Default(FmSound* fm) {
	return fm->op[0].CreateSignalSimple();
}

FmSound::FmSound()
{
	sample = 0;
	freq   = 0;
	ApplyAlgorithmFunction(&Algorithm_Default);
}

FmSound::FmSound(const std::uint32_t& sample, const std::uint32_t& freq)
{
	SetSample(sample);
	SetFreq(freq);
	ApplyParameter({ {} });
	ApplyAlgorithmFunction(&Algorithm_Default);
}

void FmSound::ApplyParameter(const Parameter& parameter)
{
	op.resize(parameter.param.size());
	for (std::uint32_t i = 0; i < op.size(); ++i) {
		op[i].SetRatio(parameter.param[i].freq_ratio);
		op[i].fb.SetGainFix(parameter.param[i].fb_gain);
		op[i].ev.adsr.SetAttackLevel(std::pow(parameter.param[i].attackLevel, 2.0f) * parameter.param[i].gain_ratio);
		op[i].ev.adsr.SetSustainLevel(std::pow(parameter.param[i].sustainLevel, 2.0f) * parameter.param[i].gain_ratio);
		op[i].ev.adsr.attack  = std::uint32_t(float(sample) * parameter.param[i].attack);
		op[i].ev.adsr.decay   = std::uint32_t(float(sample) * parameter.param[i].decay);
		op[i].ev.adsr.release = std::uint32_t(float(sample) * parameter.param[i].release);
	}

	SetFreq(freq);
}

void FmSound::ApplyAlgorithmFunction(const std::function<std::int32_t(FmSound*)>& algorithm)
{
	func = algorithm;
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
	std::int32_t signal = 0;
	for (std::uint32_t i = 0; i < num; ++i) {
		signal = func(this);
		signal >>= 16;
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

void FmSound::CreateSignal(std::uint8_t* buf, const std::uint32_t& num)
{
	std::int32_t signal = 0;
	for (std::uint32_t i = 0; i < num; ++i) {
		signal = func(this);
		signal >>= 16;
		if (signal > 0xff) {
			buf[i] = 0xff;
		}
		else {
			buf[i] = std::uint8_t(signal);
		}
	}
}

void FmSound::SetSample(const std::uint32_t& sample)
{
	this->sample = sample;
	for (Operator& i : op) {
		i.SetSpeed(freq, this->sample);
	}
}

void FmSound::SetFreq(const std::uint32_t& freq)
{
	this->freq = freq;
	for (Operator& i : op) {
		i.SetSpeed(this->freq, sample);
	}
}
