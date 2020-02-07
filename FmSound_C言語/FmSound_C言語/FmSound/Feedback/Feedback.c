#include "Feedback.h"
#include "../SinTbl/SinTbl.h"

void Feedback_Constructor(Feedback* fb)
{
	fb->gain = SIN_NUM * 4;
	fb->data = 0;
}

void Feedback_SetGain(Feedback* fb, const float gain)
{
	fb->gain = (uint32_t)(gain * (float)(SIN_NUM * 4));
}
