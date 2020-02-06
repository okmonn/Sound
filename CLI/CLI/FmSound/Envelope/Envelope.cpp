#include "Envelope.h"

Envelope::Envelope()
{
	state = FM::EV_STATE::done;
	gain  = 0;
	delta = 0;
	cnt   = 0;
}

std::int32_t Envelope::UpDate(void)
{
	std::int32_t gain = (this->gain >> 16);
	this->gain += delta;
	--cnt;

	return gain;
}

bool Envelope::SetState(const FM::EV_STATE& state)
{
	switch (state)
	{
	case FM::EV_STATE::attack:
		this->state = FM::EV_STATE::attack;
		if (adsr.attack > 0) {
			gain  = 0;
			delta = (adsr.attackLevel / adsr.attack);
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
				delta = std::int32_t((adsr.sustainLevel - gain) / adsr.decay);
			}
			cnt = adsr.decay;
			break;
		}
	case FM::EV_STATE::sustain:
		gain  = adsr.sustainLevel;
		delta = 0;
		cnt   = 0;
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
		return false;
	}

	return true;
}
