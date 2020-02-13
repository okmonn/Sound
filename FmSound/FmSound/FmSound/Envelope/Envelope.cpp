#include "Envelope.h"

FM::Envelope::Envelope()
{
	state = FM::EV_STATE::done;
	gain  = 0;
	delta = 0;
	cnt   = 0;
}

std::uint32_t FM::Envelope::UpDate(void)
{
	std::uint32_t gain = this->gain;
	this->gain += delta;
	--cnt;

	return gain;
}

std::uint8_t FM::Envelope::SetState(const EV_STATE& state)
{
	switch (state)
	{
	case FM::EV_STATE::attack:
		this->state = FM::EV_STATE::attack;
		if (adsr.attack > 0) {
			gain  = 0;
			delta = adsr.attackLevel / adsr.attack;
			cnt   = adsr.attack;
			break;
		}
	case FM::EV_STATE::decay:
		this->state = FM::EV_STATE::decay;
		if (adsr.decay > 0) {
			gain = adsr.attackLevel;
			if (gain > adsr.sustainLevel) {
				delta = -std::int32_t((gain - adsr.sustainLevel) / adsr.decay);
			}
			else {
				delta = (adsr.sustainLevel - gain) / adsr.decay;
			}
			cnt = adsr.decay;
			break;
		}
	case FM::EV_STATE::sustain:
		this->state = FM::EV_STATE::sustain;
		gain        = adsr.sustainLevel;
		delta       = 0;
		cnt         = 0;
		break;
	case FM::EV_STATE::release:
		this->state = FM::EV_STATE::release;
		if (adsr.release > 0) {
			delta = -std::int32_t(gain / adsr.release);
			cnt   = adsr.release;
			break;
		}
	case FM::EV_STATE::done:
	default:
		(*this) = Envelope();
		return 0;
	}

	return 1;
}

void FM::Envelope::operator=(const Envelope& ev)
{
	state = ev.state;
	gain  = ev.gain;
	delta = ev.delta;
	cnt   = ev.cnt;
}
