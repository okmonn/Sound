#include "SinWave.h"
#include <cmath>

SinWave::SinWave()
{
}

SinWave::~SinWave()
{
}

std::vector<std::uint8_t> SinWave::SinTbl(void)
{
	if (sinTbl.size() == 0) {
		sinTbl.resize(0x1000);
		for (std::uint32_t i = 0; i < sinTbl.size(); ++i) {
			sinTbl[i] = (0x7f * std::sin(2.0f * std::acos(-1.0f) * i / sinTbl.size())) + 0x7f;
		}
	}

	return sinTbl;
}

SinWave& SinWave::Get(void)
{
	static SinWave instance;
	return instance;
}
