#pragma once
#include <cstdint>

struct Feedback {
public:
	/*コンストラクタ*/
	Feedback();
	/*フィードバック用ゲインの設定
	.ゲイン比率(0.0f～1.0f)*/
	void SetGain(const float& gain);
	/*フィードバック用ゲインの設定
	.ゲイン比率(0.0f～1.0f)*/
	void SetGainFix(const float& gain);
	
public:
	/*フィードバック用ゲイン*/
	std::uint32_t gain;
	/*前回の出力データ*/
	std::int32_t data;
};
