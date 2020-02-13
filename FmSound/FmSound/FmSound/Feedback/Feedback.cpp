#include "Feedback.h"
#include "../SinTbl.h"

FM::Feedback::Feedback()
{
	data = 0;
	SetGain(1.0f);
}

void FM::Feedback::SetGain(const float& gain)
{
	//this->gain = std::uint32_t(gain * float(0x10000));
	this->gain = std::uint32_t(gain * float(sinTbl.size() * 4));
}

void FM::Feedback::SetGain(const std::uint32_t& gain)
{
	this->gain = gain;
}
