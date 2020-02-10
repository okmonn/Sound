#include "FmSound.h"
#include <cmath>

/*信号の生成(デフォルト)
.FmSoundのポインタ
return 信号*/
std::int32_t Default(FmSound* fm) {
	return fm->op[0].CreateSignalFB();
}

FmSound::FmSound()
{
	SetSample(48000);
	SetFreq(440U);
	ApplyParameter({ {} });
	ApplyAlgorithmFunction(&Default);
}

FmSound::FmSound(const std::uint32_t& sample, const std::uint32_t& freq)
{
	SetSample(sample);
	SetFreq(freq);
	ApplyParameter({ {} });
	ApplyAlgorithmFunction(&Default);
}

void FmSound::ApplyAlgorithmFunction(const std::function<std::int32_t(FmSound*)>& func)
{
	this->func = func;
}

void FmSound::ApplyParameter(const Parameter<float>& parameter)
{
	op.resize(parameter.param.size());
	for (std::uint32_t i = 0; i < op.size(); ++i) {
		op[i].ev.adsr.SetAttackLevel(std::pow(parameter.param[i].attackLevel, 2.0f) * parameter.param[i].gain);
		op[i].ev.adsr.SetSustainLevel(std::pow(parameter.param[i].sustainLevel, 2.0f) * parameter.param[i].gain);
		op[i].ev.adsr.attack  = std::uint32_t(float(sample) * parameter.param[i].attack);
		op[i].ev.adsr.decay   = std::uint32_t(float(sample) * parameter.param[i].decay);
		op[i].ev.adsr.release = std::uint32_t(float(sample) * parameter.param[i].release);
		op[i].SetRatio(parameter.param[i].freq);
		op[i].fb.SetGainFix(parameter.param[i].fb_gain);

		op[i].SetSpeed(freq, sample);
	}
}

void FmSound::ApplyParameterFix(const Parameter<std::uint32_t>& parameter)
{
	op.resize(parameter.param.size());
	for (std::uint32_t i = 0; i < op.size(); ++i) {
		op[i].ev.adsr.SetAttackLevel(parameter.param[i].attackLevel);
		op[i].ev.adsr.SetSustainLevel(parameter.param[i].sustainLevel);
		op[i].ev.adsr.attack  = parameter.param[i].attack;
		op[i].ev.adsr.decay   = parameter.param[i].decay;
		op[i].ev.adsr.release = parameter.param[i].release;
		op[i].SetRatio(parameter.param[i].freq);
		op[i].fb.SetGain(parameter.param[i].fb_gain);

		op[i].SetSpeed(freq, sample);
	}
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

void FmSound::CreateSignal(std::uint8_t* buf, const std::uint32_t& num)
{
	std::int32_t signal = 0;
	for (std::uint32_t i = 0; i < num; ++i) {
		signal = func(this);
		signal >>= 24;
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

void FmSound::SetFreq(const float& freq)
{
	this->freq = std::uint32_t(freq * float(0x10000));
	for (Operator& i : op) {
		i.SetSpeed(this->freq, this->sample);
	}
}

void FmSound::SetFreq(const std::uint32_t& freq)
{
	this->freq = freq << 16;
	for (Operator& i : op) {
		i.SetSpeed(this->freq, this->sample);
	}
}
