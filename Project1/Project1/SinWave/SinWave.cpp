#include "SinWave.h"
#include <cmath>

namespace {
	/*ƒe[ƒuƒ‹”*/
	const std::uint32_t tblNum = 0x1000;
}

SinWave::SinWave()
{
}

std::vector<std::uint8_t> SinWave::Sin8(void)
{
	if (sinWave8.size() == 0) {
		sinWave8.resize(tblNum);
		for (std::uint32_t i = 0; i < tblNum; ++i) {
			sinWave8[i] = std::uint8_t(float(0x7f) * (std::sin(2.0f * std::acos(-1.0f) * i / tblNum))) + 0x7f;
		}
	}

 	return sinWave8;
}

std::vector<std::int16_t> SinWave::Sin16(void)
{
	if (sinWave16.size() == 0) {
		sinWave16.resize(tblNum);
		for (std::uint32_t i = 0; i < tblNum; ++i) {
			sinWave16[i] = std::int16_t(float(0x7fff) * std::sin(2.0f * std::acos(-1.0f) * i / tblNum));
		}
	}

	return sinWave16;
}

std::uint32_t SinWave::GetNum(void) const
{
	return tblNum;
}

SinWave& SinWave::Get(void)
{
	static SinWave instance;
	return instance;
}
