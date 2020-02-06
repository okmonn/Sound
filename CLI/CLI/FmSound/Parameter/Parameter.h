#pragma once
#include <vector>

struct Param {
public:
	/*コンストラクタ*/
	Param();
	/*コンストラクタ
	.アタック時の最大ゲイン(0.0f～1.0f)
	.サスティン時の最大ゲイン(0.0f～1.0f)
	.アタック時の持続サンプル数比率(0.0f～1.0f)
	.ディケイ時の持続サンプル数比率(0.0f～1.0f)
	.リリース時の持続サンプル数比率(0.0f～1.0f)
	.生成周波数比率(0.0f～1.0f)
	.フィードバック用ゲイン(0.0f～1.0f)
	.ゲイン(0.0f～1.0f)*/
	Param(const float& attackLevel, const float& sustainLevel, const float& attack, const float& decay, const float& release,
		const float& freq_ratio, const float& fb_gain, const float& gain = 1.0f);

public:
	/*アタック時の最大ゲイン*/
	float attackLevel;
	/*サスティン時の最大ゲイン*/
	float sustainLevel;
	/*アタック時の持続サンプル数比率*/
	float attack;
	/*ディケイ時の持続サンプル数比率*/
	float decay;
	/*リリース時の持続サンプル数比率*/
	float release;
	/*生成周波数比率*/
	float freq_ratio;
	/*フィードバック用ゲイン*/
	float fb_gain;
	/*ゲイン*/
	float gain;
};

struct Parameter {
public:
	/*コンストラクタ
	.パラメータリスト*/
	Parameter(const std::initializer_list<Param>& param);

public:
	/*パラメータ*/
	std::vector<Param>param;
};
