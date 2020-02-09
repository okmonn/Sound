#pragma once
#include <vector>

struct Param {
public:
	/*コンストラクタ*/
	Param();
	/*コンストラクタ
	.アタック時のゲイン(0.0f～1.0f)
	.サスティン時のゲイン(0.0f～1.0f)
	.アタック時のサンプル数比率(0.0f～1.0f)
	.ディケイ時のサンプル数比率(0.0f～1.0f)
	.リリース時のサンプル数比率(0.0f～1.0f)
	.生成周波数比率(0.0f～1.0f)
	.ゲイン(0.0f～1.0f)
	.フィードバック用ゲイン(0.0f～1.0f)*/
	Param(const float& attackLevel, const float& sustainLevel, const float& attack, const float& decay, const float& release,
		const float& freq_ratio, const float& gain_ratio, const float& fb_gain);

public:
	/*アタック時のゲイン*/
	float attackLevel;
	/*サスティン時のゲイン*/
	float sustainLevel;
	/*アタック時のサンプル数比率*/
	float attack;
	/*ディケイ時のサンプル数比率*/
	float decay;
	/*リリース時のサンプル数比率*/
	float release;
	/*生成周波数比率*/
	float freq_ratio;
	/*ゲイン比率*/
	float gain_ratio;
	/*フィードバックゲイン*/
	float fb_gain;
};

struct Parameter {
public:
	/*コンストラクタ
	.Paramリスト*/
	Parameter(const std::initializer_list<Param>& param);

public:
	/*パラメータ*/
	std::vector<Param>param;
};
