#include "Parameter.h"

void Parameter_Constructor(Parameter* parameter)
{
	parameter->attackLevel  = 0.0f;
	parameter->attack       = 0.0f;
	parameter->decay        = 0.0f;
	parameter->sustainLevel = 0.0f;
	parameter->release      = 0.0f;
	parameter->freq_ratio   = 0.0f;
	parameter->gain_ratio   = 0.0f;
	parameter->fb_gain      = 0.0f;
}
