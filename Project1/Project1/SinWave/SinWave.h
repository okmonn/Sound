#pragma once
#include <vector>
#include <cstdint>

class SinWave {
public:
	/*デストラクタ*/
	~SinWave();
	/*サイン波の取得
	return サイン波*/
	std::vector<std::uint8_t>SinTbl(void);
	/*インスタンス変数の取得
	return インスタンス変数*/
	static SinWave& Get(void);

private:
	/*コンストラクタ*/
	SinWave();
	/*サイン波*/
	std::vector<std::uint8_t>sinTbl;
};
