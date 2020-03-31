#include "../../include/ADSR/Attack.h"
#include <math.h>

void Attack_Constructor(Attack* attack)
{
	Attack_SetMaxGain(attack, 1.0f, 1.0f);
	Attack_SetDuration(attack, 0);
}

void Attack_SetMaxGain(Attack* attack, const float gain_ratio, const float valume_ratio)
{
	attack->max_gain = (uint32_t)((float)0xFFFFFFFF * (powf(gain_ratio, 2.0f) * valume_ratio));
}

void Attack_SetDuration(Attack* attack, const uint32_t duration)
{
	attack->duration = duration;
}
