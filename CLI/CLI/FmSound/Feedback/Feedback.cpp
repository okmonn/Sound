#include "Feedback.h"
#include "../SinTbl.h"

Feedback::Feedback()
{
	gain = std::uint32_t(sinTbl.size() * 4);
	data = 0;
}

void Feedback::SetGain(const float& gain)
{
	this->gain = std::uint32_t(float(sinTbl.size() * 4) * gain);
}
