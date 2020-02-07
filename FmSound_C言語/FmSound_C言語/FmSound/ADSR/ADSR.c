#include "ADSR.h"

void ADSR_Constructor(ADSR* adsr)
{
	adsr->attack  = 0;
	adsr->decay   = 0;
	adsr->release = 0;
	ADSR_SetAttackLevel(adsr, 1.0f);
	ADSR_SetSustainLevel(adsr, 1.0f);
}

void ADSR_SetAttackLevel(ADSR* adsr, const float level)
{
	adsr->attackLevel = (uint32_t)((double)(0xffffffff) * level);
}

void ADSR_SetSustainLevel(ADSR* adsr, const float level)
{
	adsr->sustainLevel = (uint32_t)((double)(0xffffffff) * level);
}
