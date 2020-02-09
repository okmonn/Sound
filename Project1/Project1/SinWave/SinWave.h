#pragma once
#include <vector>

class SinWave {
public:
	/*サイン波の取得(8ビット)
	return サイン波*/
	std::vector<std::uint8_t>Sin8(void);
	/*サイン波の取得(16ビット)
	return サイン波*/
	std::vector<std::int16_t>Sin16(void);
	/*サイン波の数の取得
	return サイン波の数*/
	std::uint32_t GetNum(void) const;
	/*インスタンス変数の取得
	return インスタンス変数*/
	static SinWave& Get(void);

private:
	SinWave(const SinWave&)         = delete;
	SinWave(const SinWave&&)        = delete;
	void operator=(const SinWave&)  = delete;
	void operator=(const SinWave&&) = delete;

private:
	/*コンストラクタ*/
	SinWave();

private:
	/*サイン波(8ビット)*/
	std::vector<std::uint8_t>sinWave8;
	/*サイン波(16ビット)*/
	std::vector<std::int16_t>sinWave16;
};
