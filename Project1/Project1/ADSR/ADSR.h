#pragma once
#include <cstdint>

struct ADSR {
public:
	/*コンストラクタ*/
	ADSR();
	/*アタック時の最大ゲインの設定
	.ゲイン*/
	void SetAttackLevel(const float& gain);
	void SetAttackLevel(const std::uint32_t& gain);
	/*サスティン時の最大ゲインの設定
	.ゲイン*/
	void SetSustainLevel(const float& gain);
	void SetSustainLevel(const std::uint32_t& gain);

public:
	/*アタック時の最大ゲイン*/
	std::uint32_t attackLevel;
	/*サスティン時の最大ゲイン*/
	std::uint32_t sustainLevel;
	/*アタック時の持続サンプル数*/
	std::uint32_t attack;
	/*ディケイ時の持続サンプル数*/
	std::uint32_t decay;
	/*リリース時の持続サンプル数*/
	std::uint32_t release;
};
