#include "FmSound.h"
#include <cmath>
#include <unordered_map>

namespace {
	/*クリッピング*/
	std::unordered_map<std::uint32_t, std::function<std::int32_t(const std::int32_t&)>>clipping = {
		{1, [&](const std::int32_t& signal)->std::int32_t {
			if (signal > 0xff) {
				return 0xff;
			}

			return signal;
		}},
		{2, [&](const std::int32_t& signal)->std::int32_t {
			if (signal > 0x7fff) {
				return 0x7fff;
			}
			else if (signal < -0x7fff) {
				return -0x7fff;
			}

			return signal;
		}},
	};
}

/*信号の生成(デフォルト)
.FmSoundのポインタ
return 信号*/
template <typename T>
std::int32_t Default(FM::FmSound<T>* fm) {
	return fm->op[0].CreateSignalSimple();
}
template std::int32_t Default(FM::FmSound<std::uint8_t>*);
template std::int32_t Default(FM::FmSound<std::int16_t>*);

template<typename T>
FM::FmSound<T>::FmSound()
{
	SetSample(48000);
	SetFreq(440U);
	ApplyParameter({ {} });
	ApplyAlgorithmFunction(&Default<T>);
}
template FM::FmSound<std::uint8_t>::FmSound();
template FM::FmSound<std::int16_t>::FmSound();

template<typename T>
FM::FmSound<T>::FmSound(const std::uint32_t& sample, const std::uint32_t& freq)
{
	SetSample(sample);
	SetFreq(freq);
	ApplyParameter({ {} });
	ApplyAlgorithmFunction(&Default<T>);
}
template FM::FmSound<std::uint8_t>::FmSound(const std::uint32_t&, const std::uint32_t&);
template FM::FmSound<std::int16_t>::FmSound(const std::uint32_t&, const std::uint32_t&);

template<typename T>
void FM::FmSound<T>::ApplyParameter(const Parameter<float>& parameter)
{
	op.resize(parameter.param.size());
	for (std::uint32_t i = 0; i < op.size(); ++i) {
		op[i].SetFreq(parameter.param[i].freq);
		op[i].fb.SetGain(parameter.param[i].fb_gain);
		op[i].ev.adsr.SetAttackLevel(std::pow(parameter.param[i].attackLevel, 2.0f) * parameter.param[i].gain);
		op[i].ev.adsr.SetSustainLevel(std::pow(parameter.param[i].sustainLevel, 2.0f) * parameter.param[i].gain);
		op[i].ev.adsr.attack  = std::uint32_t(float(sample) * parameter.param[i].attack);
		op[i].ev.adsr.decay   = std::uint32_t(float(sample) * parameter.param[i].decay);
		op[i].ev.adsr.release = std::uint32_t(float(sample) * parameter.param[i].release);
		
		op[i].SetSpeed(freq, sample);
	}
}
template void FM::FmSound<std::uint8_t>::ApplyParameter(const Parameter<float>&);
template void FM::FmSound<std::int16_t>::ApplyParameter(const Parameter<float>&);

template<typename T>
void FM::FmSound<T>::ApplyParameterFix(const Parameter<std::uint32_t>& parameter)
{
	op.resize(parameter.param.size());
	for (std::uint32_t i = 0; i < op.size(); ++i) {
		op[i].SetFreq(parameter.param[i].freq);
		op[i].fb.SetGain(parameter.param[i].fb_gain);
		op[i].ev.adsr.SetAttackLevel(parameter.param[i].attackLevel);
		op[i].ev.adsr.SetSustainLevel(parameter.param[i].sustainLevel);
		op[i].ev.adsr.attack  = parameter.param[i].attack;
		op[i].ev.adsr.decay   = parameter.param[i].decay;
		op[i].ev.adsr.release = parameter.param[i].release;

		op[i].SetSpeed(sample);
	}
}
template void FM::FmSound<std::uint8_t>::ApplyParameterFix(const Parameter<std::uint32_t>&);
template void FM::FmSound<std::int16_t>::ApplyParameterFix(const Parameter<std::uint32_t>&);

template<typename T>
void FM::FmSound<T>::ApplyAlgorithmFunction(const std::function<std::int32_t(FmSound*)>& func)
{
	function = func;
}
template void FM::FmSound<std::uint8_t>::ApplyAlgorithmFunction(const std::function<std::int32_t(FmSound*)>&);
template void FM::FmSound<std::int16_t>::ApplyAlgorithmFunction(const std::function<std::int32_t(FmSound*)>&);

template<typename T>
void FM::FmSound<T>::Start(void)
{
	for (Operator<T>& i : op) {
		i.Start();
	}
}
template void FM::FmSound<std::uint8_t>::Start(void);
template void FM::FmSound<std::int16_t>::Start(void);

template<typename T>
void FM::FmSound<T>::Stop(void)
{
	for (Operator<T>& i : op) {
		i.Stop();
	}
}
template void FM::FmSound<std::uint8_t>::Stop(void);
template void FM::FmSound<std::int16_t>::Stop(void);

template<typename T>
void FM::FmSound<T>::CreateSignal(T* buf, const std::uint32_t& num)
{
	std::int32_t signal = 0;
	for (std::uint32_t i = 0; i < num; ++i) {
		signal = function(this);
		signal >>= 24;// ((sizeof(signal) - sizeof(T)) * 8);
		buf[i] = T(clipping[sizeof(T)](signal));
	}
}
template void FM::FmSound<std::uint8_t>::CreateSignal(std::uint8_t*, const std::uint32_t&);
template void FM::FmSound<std::int16_t>::CreateSignal(std::int16_t*, const std::uint32_t&);

template<typename T>
void FM::FmSound<T>::SetSample(const std::uint32_t& sample)
{
	this->sample = sample;
	for (Operator<T>& i : op) {
		i.SetSpeed(freq, this->sample);
	}
}
template void FM::FmSound<std::uint8_t>::SetSample(const std::uint32_t&);
template void FM::FmSound<std::int16_t>::SetSample(const std::uint32_t&);

template<typename T>
void FM::FmSound<T>::SetFreq(const float& freq)
{
	this->freq = std::uint32_t(freq * float(0x10000));
	for (Operator<T>& i : op) {
		i.SetSpeed(this->freq, sample);
	}
}
template void FM::FmSound<std::uint8_t>::SetFreq(const float&);
template void FM::FmSound<std::int16_t>::SetFreq(const float&);

template<typename T>
void FM::FmSound<T>::SetFreq(const std::uint32_t& freq)
{
	this->freq = (freq << 16);
	for (Operator<T>& i : op) {
		i.SetSpeed(this->freq, sample);
	}
}
template void FM::FmSound<std::uint8_t>::SetFreq(const std::uint32_t&);
template void FM::FmSound<std::int16_t>::SetFreq(const std::uint32_t&);
