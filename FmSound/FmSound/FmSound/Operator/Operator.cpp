#include "Operator.h"
#include "../SinTbl.h"
template<typename T>
FM::Operator<T>::Operator()
{
	flag  = 0;
	pos   = 0;
	speed = 0;
	freq  = 0;
	SetFreq(1.0f);
}
template FM::Operator<std::uint8_t>::Operator();
template FM::Operator<std::int16_t>::Operator();

template<typename T>
void FM::Operator<T>::Start(void)
{
	ev      = Envelope();
	fb.data = 0;
	flag    = ev.SetState(FM::EV_STATE((std::uint32_t(ev.state) + 1) % std::uint32_t(FM::EV_STATE::MAX)));;
}
template void FM::Operator<std::uint8_t>::Start(void);
template void FM::Operator<std::int16_t>::Start(void);

template<typename T>
void FM::Operator<T>::Stop(void)
{
	if (flag == 1) {
		if (ev.state != FM::EV_STATE::release) {
			flag = ev.SetState(FM::EV_STATE::release);
		}
	}
}
template void FM::Operator<std::uint8_t>::Stop(void);
template void FM::Operator<std::int16_t>::Stop(void);

template<typename T>
std::int32_t FM::Operator<T>::CreateSignalSimple(void)
{
	if (flag == 0) {
		return 0;
	}

	if (ev.cnt == 0 && ev.state != FM::EV_STATE::sustain) {
		flag = ev.SetState(FM::EV_STATE((std::uint32_t(ev.state) + 1) % std::uint32_t(FM::EV_STATE::MAX)));
	}

	std::int32_t gain   = (ev.UpDate() >> (sizeof(T) * 8));
	std::int32_t signal = sinTbl[(pos >> 20)] * gain;
	pos += speed;

	return signal;
}
template std::int32_t FM::Operator<std::uint8_t>::CreateSignalSimple(void);
template std::int32_t FM::Operator<std::int16_t>::CreateSignalSimple(void);

template<typename T>
std::int32_t FM::Operator<T>::CreateSignalFB(void)
{
	if (flag == 0) {
		return 0;
	}

	if (ev.cnt == 0 && ev.state != FM::EV_STATE::sustain) {
		flag = ev.SetState(FM::EV_STATE((std::uint32_t(ev.state) + 1) % std::uint32_t(FM::EV_STATE::MAX)));
	}

	std::int32_t gain   = (ev.UpDate() >> (sizeof(T) * 8));
	std::int32_t signal = sinTbl[((pos + (fb.data * fb.gain)) >> 20)] * gain;
	fb.data             = ((sinTbl[(pos >> 20)] * gain) >> 12);
	pos += speed;

	return signal;
}
template std::int32_t FM::Operator<std::uint8_t>::CreateSignalFB(void);
template std::int32_t FM::Operator<std::int16_t>::CreateSignalFB(void);

template<typename T>
std::int32_t FM::Operator<T>::CreateSignalModulation(const std::int32_t& mod)
{
	if (flag == 0) {
		return 0;
	}

	if (ev.cnt == 0 && ev.state != FM::EV_STATE::sustain) {
		flag = ev.SetState(FM::EV_STATE((std::uint32_t(ev.state) + 1) % std::uint32_t(FM::EV_STATE::MAX)));
	}

	std::int32_t gain   = (ev.UpDate() >> (sizeof(T) * 8));
	std::int32_t signal = sinTbl[((pos + mod) >> 20)] * gain;
	pos += speed;

	return signal;
}
template std::int32_t FM::Operator<std::uint8_t>::CreateSignalModulation(const std::int32_t&);
template std::int32_t FM::Operator<std::int16_t>::CreateSignalModulation(const std::int32_t&);

template<typename T>
void FM::Operator<T>::SetSpeed(const std::uint32_t& sample)
{
	speed = ((freq / sample) << 16);
}
template void FM::Operator<std::uint8_t>::SetSpeed(const std::uint32_t&);
template void FM::Operator<std::int16_t>::SetSpeed(const std::uint32_t&);

template<typename T>
void FM::Operator<T>::SetSpeed(const std::uint32_t& freq, const std::uint32_t& sample)
{
	speed = ((((freq >> 8) * (this->freq >> 8)) / sample) << 16);
}
template void FM::Operator<std::uint8_t>::SetSpeed(const std::uint32_t&, const std::uint32_t&);
template void FM::Operator<std::int16_t>::SetSpeed(const std::uint32_t&, const std::uint32_t&);

template<typename T>
void FM::Operator<T>::SetFreq(const float& freq)
{
	this->freq = std::uint32_t(freq * float(0x10000));
}
template void FM::Operator<std::uint8_t>::SetFreq(const float&);
template void FM::Operator<std::int16_t>::SetFreq(const float&);

template<typename T>
void FM::Operator<T>::SetFreq(const std::uint32_t& freq)
{
	this->freq = freq;
}
template void FM::Operator<std::uint8_t>::SetFreq(const std::uint32_t&);
template void FM::Operator<std::int16_t>::SetFreq(const std::uint32_t&);
