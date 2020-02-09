#include "ADSR.h"

ADSR::ADSR()
{
	attack  = 0;
	decay   = 0;
	release = 0;
	SetAttackLevel(1.0f);
	SetSustainLevel(1.0f);
}

void ADSR::SetAttackLevel(const float& gain)
{
	attackLevel = std::uint32_t(double(0xffffffff) * gain);
}

void ADSR::SetSustainLevel(const float& gain)
{
	sustainLevel = std::uint32_t(double(0xffffffff) * gain);
}
