#include "../../include/ADSR/Decay.h"

void Decay_Constructor(Decay* decay)
{
	Decay_SetDuration(decay, 0);
}

void Decay_SetDuration(Decay* decay, const uint32_t duration)
{
	decay->duration = duration;
}
