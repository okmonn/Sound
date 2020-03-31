#include "../../include/ADSR/Sustain.h"
#include <math.h>

void Sustain_Constructor(Sustain* sustain)
{
	Sustain_SetMaxGain(sustain, 1.0f, 1.0f);
}

void Sustain_SetMaxGain(Sustain* sustain, const float gain_ratio, const float valume_ratio)
{
	sustain->max_gain = (uint32_t)((float)0xFFFFFFFF * (powf(gain_ratio, 2.0f) * valume_ratio));
}
