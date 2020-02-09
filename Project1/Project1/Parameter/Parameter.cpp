#include "Parameter.h"

Param::Param()
{
	attackLevel  = 0.9f;
	sustainLevel = 1.0f;
	attack       = 1.0f;
	decay        = 0.0f;
	release      = 0.0f;
	freq_ratio   = 1.0f;
	gain_ratio   = 1.0f;
	fb_gain      = 2.0f;
}

Param::Param(const float& attackLevel, const float& sustainLevel, const float& attack, const float& decay, const float& release, 
	const float& freq_ratio, const float& gain_ratio, const float& fb_gain) : 
	attackLevel(attackLevel), sustainLevel(sustainLevel), attack(attack), decay(decay), release(release), 
	freq_ratio(freq_ratio), gain_ratio(gain_ratio), fb_gain(fb_gain)
{
}

Parameter::Parameter(const std::initializer_list<Param>& param)
{
	this->param.assign(param.begin(), param.end());
}
