#include "Feedback.h"
#include "../SinTbl.h"

Feedback::Feedback()
{
	data = 0;
	SetGainFix(1.0f);
}

void Feedback::SetGain(const float& gain)
{
	this->gain = std::uint32_t(gain * float(0x10000));
}

void Feedback::SetGain(const std::uint32_t& gain)
{
	this->gain = gain;
}

void Feedback::SetGainFix(const float& gain)
{
	this->gain = std::uint32_t(float(sinTbl.size() * 4) * gain);
}