#include "Operator.h"
#include "../SinWave/SinWave.h"
Operator::Operator()
{
	play  = 0;
	pos   = 0;
	speed = 0;
	SetRatio(1.0f);
}

void Operator::Start(void)
{
	ev      = Envelope();
	fb.data = 0;
	play    = ev.SetState(FM::EV_STATE((std::uint32_t(ev.state) + 1) % std::uint32_t(FM::EV_STATE::MAX)));
}

void Operator::Stop(void)
{
	if (play == 1) {
		if (ev.state != FM::EV_STATE::release) {
			play = ev.SetState(FM::EV_STATE::release);
		}
	}
}

std::int32_t Operator::CreateSignalSimple(void)
{
	if (play == 0) {
		return 0;
	}

	if (ev.cnt == 0 && ev.state != FM::EV_STATE::sustain) {
		play = ev.SetState(FM::EV_STATE((std::uint32_t(ev.state) + 1) % std::uint32_t(FM::EV_STATE::MAX)));
	}

	std::int32_t signal = SinWave::Get().SinTbl()[(pos >> 20)] * ev.UpDate();
	pos += speed;

	return signal;
}

std::int32_t Operator::CreateSignalFB(void)
{
	if (play == 0) {
		return 0;
	}

	if (ev.cnt == 0 && ev.state != FM::EV_STATE::sustain) {
		play = ev.SetState(FM::EV_STATE((std::uint32_t(ev.state) + 1) % std::uint32_t(FM::EV_STATE::MAX)));
	}

	std::int32_t gain   = ev.UpDate();
	std::int32_t signal = SinWave::Get().SinTbl()[((pos + fb.data * fb.gain) >> 20)] * gain;
	fb.data = (SinWave::Get().SinTbl()[(pos >> 20)] * gain) >> 12;
	pos += speed;
	return signal;
}

std::int32_t Operator::CreateSignalModulation(const std::int32_t& mod)
{
	if (play == 0) {
		return 0;
	}

	if (ev.cnt == 0 && ev.state != FM::EV_STATE::sustain) {
		play = ev.SetState(FM::EV_STATE((std::uint32_t(ev.state) + 1) % std::uint32_t(FM::EV_STATE::MAX)));
	}

	std::int32_t signal = SinWave::Get().SinTbl()[((pos + mod) >> 20)] * ev.UpDate();
	pos += speed;

	return signal;
}

void Operator::SetSpeed(const std::uint32_t& freq, const std::uint32_t& sample)
{
	speed = ((((freq >> 8)* (ratio >> 8)) / sample) << 16);
}

void Operator::SetRatio(const float& ratio)
{
	this->ratio = std::uint32_t(ratio * float(0x10000));
}

void Operator::SetRatio(const std::uint32_t& ratio)
{
	this->ratio = ratio;
}
