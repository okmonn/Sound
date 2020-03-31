#include "../include/Envelope.h"
#include "../include/Modulator.h"

/*動作中か確認
.Envelopeのポインタ
return チェック(0：動作中　1：停止中)*/
static uint32_t Envelope_IsBehaviour(Envelope* envelope)
{
	if (envelope->state_count == 0) {
		switch (envelope->state)
		{
		case EV_STATE_STOP:
			envelope->state = EV_STATE_ATTACK;
			if (envelope->attack.duration > 0) {
				envelope->gain_delta  = (int32_t)(envelope->attack.max_gain / envelope->attack.duration);
				envelope->state_count = envelope->attack.duration;
				break;
			}
		case EV_STATE_ATTACK:
			envelope->state = EV_STATE_DECAY;
			if (envelope->decay.duration > 0) {
				envelope->gain        = envelope->attack.max_gain;
				envelope->state_count = envelope->decay.duration;
				if (envelope->attack.max_gain > envelope->sustain.max_gain) {
					envelope->gain_delta = -(int32_t)((envelope->attack.max_gain - envelope->sustain.max_gain) / envelope->decay.duration);
				}
				else {
					envelope->gain_delta = (int32_t)((envelope->sustain.max_gain - envelope->attack.max_gain) / envelope->decay.duration);
				}
				break;
			}
		case EV_STATE_DECAY:
			envelope->state      = EV_STATE_SUSTAIN;
			envelope->gain       = envelope->sustain.max_gain;
			envelope->gain_delta = 0;
			break;
		case EV_STATE_SUSTAIN:
			break;
		case EV_STATE_NOTEOFF:
			envelope->state = EV_STATE_RELEASE;
			if (envelope->release.duration > 0) {
				envelope->gain_delta  = -(int32_t)(envelope->gain / envelope->release.duration);
				envelope->state_count = envelope->release.duration;
				break;
			}
		case EV_STATE_RELEASE:
			envelope->state = EV_STATE_STOP;
			envelope->gain  = 0;
			return 1;
		default:
			break;
		}
	}

	return 0;
}

void Envelope_Constructor(Envelope* envelope, const uint32_t sample_freq)
{
	envelope->gain        = 0;
	envelope->gain_delta  = 0;
	envelope->state       = EV_STATE_STOP;
	envelope->state_count = 0;

	Attack_SetDuration(&envelope->attack, sample_freq);
	Decay_SetDuration(&envelope->decay, sample_freq);
	Release_SetDuration(&envelope->release, sample_freq);
}

void Envelope_SetState(Envelope* envelope, const EV_STATE envelope_state)
{
	envelope->state       = envelope_state;
	envelope->state_count = 0;
}

uint32_t Envelope_UpDate(Envelope* envelope, uint8_t* modulator_state)
{
	if (Envelope_IsBehaviour(envelope) != 0) {
		(*modulator_state) = MOD_STATE_STOP;
		return 0;
	}

	uint32_t gain   = envelope->gain;
	envelope->gain += envelope->gain_delta;
	--envelope->state_count;

	return gain;
}
