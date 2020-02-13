#include "ADSR.h"

FM::ADSR::ADSR()
{
	attack  = 0;
	decay   = 0;
	release = 0;
	SetAttackLevel(1.0f);
	SetSustainLevel(1.0f);
}

void FM::ADSR::SetAttackLevel(const float& gain)
{
	attackLevel = std::uint32_t(double(0xffffffff) * gain);
}

void FM::ADSR::SetAttackLevel(const std::uint32_t& gain)
{
	attackLevel = gain;
}

void FM::ADSR::SetSustainLevel(const float& gain)
{
	sustainLevel = std::uint32_t(double(0xffffffff) * gain);
}

void FM::ADSR::SetSustainLevel(const std::uint32_t& gain)
{
	sustainLevel = gain;
}
