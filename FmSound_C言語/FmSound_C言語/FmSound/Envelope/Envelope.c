#include "Envelope.h"

void Envelope_Constructor(Envelope* ev)
{
	ev->state = done;
	ev->gain  = 0;
	ev->delta = 0;
	ev->cnt   = 0;
}

uint8_t Envelope_SetState(Envelope* ev, const ADSR* adsr, const EV_STATE state)
{
	switch (state)
	{
	case attack:
		ev->state = attack;
		if (adsr->attack > 0) {
			ev->gain  = 0;
			ev->delta = adsr->attackLevel / adsr->attack;
			ev->cnt   = adsr->attack;
			break;
		}
	case decay:
		ev->state = decay;
		if (adsr->decay > 0) {
			ev->gain = adsr->attackLevel;
			if (ev->gain > adsr->sustainLevel) {
				ev->delta = -(int32_t)((ev->gain - adsr->sustainLevel) / adsr->decay);
			}
			else {
				ev->delta = (int32_t)((adsr->sustainLevel - ev->gain) / adsr->decay);
			}
			ev->cnt = adsr->decay;
			break;
		}
	case sustain:
		ev->state = sustain;
		ev->gain  = adsr->sustainLevel;
		ev->delta = 0;
		break;
	case release:
		ev->state = release;
		if (adsr->release > 0) {
			ev->delta = -(int32_t)(ev->gain / adsr->release);
			ev->cnt   = adsr->release;
			break;
		}
	case done:
	default:
		Envelope_Constructor(ev);
		return 0;
	}

	return 1;
}
