#include "../include/Feedback.h"
#include "../include/Carrier.h"

void Feedback_Constructor(Feedback* feedback)
{
	feedback->old_signal = 0;

	Feedback_SetGain(feedback, 1.0f);
}

void Feedback_SetGain(Feedback* feedback, const float gain_ratio)
{
	feedback->gain = (uint32_t)(SIN_WAVE_NUM * 4 * gain_ratio);
	/*feedback->gain = (uint32_t)((float)0xFFFFFFFF * gain_ratio);*/
}
