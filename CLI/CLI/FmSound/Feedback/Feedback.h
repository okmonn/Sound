#pragma once
#include <cstdint>

struct Feedback {
public:
	/*コンストラクタ*/
	Feedback();
	/*ゲインの設定
	.ゲイン(0.0f～1.0f)*/
	void SetGain(const float& gain);

public:
	/*ゲイン*/
	std::uint32_t gain;
	/*フィードバック用出力データ*/
	std::int32_t data;
};
