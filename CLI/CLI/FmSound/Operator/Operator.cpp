#include "Operator.h"
#include "../SinTbl.h"

Operator::Operator()
{
	play  = false;
	pos   = 0;
	speed = 0;
	SetFreqRatio(1.0f);
}

void Operator::Start(void)
{
	fb.data = 0;
	ev      = Envelope();
	play    = ev.SetState(FM::EV_STATE((std::uint32_t(ev.state) + 1) % std::uint32_t(FM::EV_STATE::MAX)));
}

void Operator::Stop(void)
{
	if (play == true) {
		if (ev.state != FM::EV_STATE::release) {
			play = ev.SetState(FM::EV_STATE::release);
		}
	}
}

std::int32_t Operator::CreateSignalSimple(void)
{
	if (ev.cnt == 0 && ev.state != FM::EV_STATE::sustain) {
		play = ev.SetState(FM::EV_STATE((std::uint32_t(ev.state) + 1) % std::uint32_t(FM::EV_STATE::MAX)));
	}

	if (play == true) {
		std::int32_t signal = sinTbl[(pos >> 20)] * ev.UpDate();
		pos += speed;

		return signal;
	}

	return 0;
}

std::int32_t Operator::CreateSignalFB(void)
{
	if (ev.cnt == 0 && ev.state != FM::EV_STATE::sustain) {
		play = ev.SetState(FM::EV_STATE((std::uint32_t(ev.state) + 1) % std::uint32_t(FM::EV_STATE::MAX)));
	}

	if (play == true) {
		std::int32_t gain = ev.UpDate();
		std::int32_t signal = sinTbl[((pos + (fb.data * fb.gain)) >> 20)] * gain;
		fb.data = ((sinTbl[(pos >> 20)] * gain) >> 12);
		pos += speed;

		return signal;
	}

	return 0;
}

std::int32_t Operator::CreateSignalModulation(const std::int32_t& mod)
{
	if (ev.cnt == 0 && ev.state != FM::EV_STATE::sustain) {
		play = ev.SetState(FM::EV_STATE((std::uint32_t(ev.state) + 1) % std::uint32_t(FM::EV_STATE::MAX)));
	}

	if (play == true) {
		std::int32_t signal = sinTbl[((pos + mod) >> 20)] * ev.UpDate();
		pos += speed;

		return signal;
	}

	return 0;
}

void Operator::SetSpeed(const std::uint32_t& freq, const std::uint32_t& sample)
{
	std::uint32_t tmp = (freq << 16);
	speed = ((((tmp >> 8) * (ratio >> 8)) / sample) << 16);
}

void Operator::SetFreqRatio(const float& ratio)
{
	this->ratio = std::uint32_t(ratio * 0x10000);
}
