#include "Feedback.h"
#include "../SinWave/SinWave.h"

Feedback::Feedback()
{
	data = 0;
	SetGain(1.0f);
}

void Feedback::SetGain(const float& gain)
{
	this->gain = std::uint32_t(gain * float(0x10000));
}

void Feedback::SetGainFix(const float& gain)
{
	this->gain = std::uint32_t(float(SinWave::Get().GetNum() * 4) * gain);
}
