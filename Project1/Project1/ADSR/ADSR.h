#pragma once
#include <cstdint>

struct ADSR {
public:
	/*コンストラクタ*/
	ADSR();
	/*アタック時のゲインの設定
	.ゲイン比率(0.0f～1.0f)*/
	void SetAttackLevel(const float& gain);
	/*サスティン時のゲイン設定
	.ゲイン比率(0.0f～1.0f)*/
	void SetSustainLevel(const float& gain);

public:
	/*アタック時のゲイン*/
	std::uint32_t attackLevel;
	/*サスティン時のゲイン*/
	std::uint32_t sustainLevel;
	/*アタック時の持続サンプル数*/
	std::uint32_t attack;
	/*ディケイ時の持続サンプル数*/
	std::uint32_t decay;
	/*リリース時の持続サンプル数*/
	std::uint32_t release;
};