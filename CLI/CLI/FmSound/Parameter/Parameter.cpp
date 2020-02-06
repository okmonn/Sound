#include "Parameter.h"

Param::Param()
{
	attackLevel  = 0.0f;
	sustainLevel = 1.0f;
	attack       = 0.0f;
	decay        = 0.0f;
	release      = 0.0f;
	freq_ratio   = 1.0f;
	fb_gain      = 0.0f;
	gain         = 1.0f;
}

Param::Param(const float& attackLevel, const float& sustainLevel, const float& attack, const float& decay, const float& release,
	const float& freq_ratio, const float& fb_gain, const float& gain) : 
	attackLevel(attackLevel), sustainLevel(sustainLevel), attack(attack), decay(decay), release(release),
	freq_ratio(freq_ratio), fb_gain(fb_gain), gain(gain)
{
}

Parameter::Parameter(const std::initializer_list<Param>& param)
{
	this->param.resize(param.size());
	std::uint32_t index = 0;
	for (const Param& i : param) {
		this->param[index++] = i;
	}
}
