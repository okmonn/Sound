#pragma once
#include <cstdint>

struct Feedback {
public:
	/*コンストラクタ*/
	Feedback();
	/*フィードバック用ゲインの設定
	.ゲイン*/
	void SetGain(const float& gain);
	void SetGain(const std::uint32_t& gain);
	/*フィードバック用ゲインの設定
	.ゲイン*/
	void SetGainFix(const float& gain);

public:
	/*フィードバック用ゲイン*/
	std::uint32_t gain;
	/*前回の出力データ*/
	std::int32_t data;
};
