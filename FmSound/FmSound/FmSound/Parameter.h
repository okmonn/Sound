#pragma once
#include <vector>

namespace FM {
	template <typename T>
	struct Param {
	public:
		/*コンストラクタ*/
		Param() {
			attackLevel  = T(0);
			sustainLevel = T(1);
			attack       = T(0);
			decay        = T(0);
			release      = T(0);
			freq         = T(1);
			gain         = T(1);
			fb_gain      = T(1);
		}
		/*コンストラクタ
		.アタック時の最大ゲイン
		.サスティン時の最大ゲイン
		.アタック時の持続サンプル数
		.ディケイ時の持続サンプル数
		.リリース時の持続サンプル数
		.生成周波数
		.ゲイン
		.フィードバック用ゲイン*/
		Param(const T& attackLevel, const T& sustainLevel, const T& attack, const T& decay, const T& release,
			const T& freq, const T& gain, const T& fb_gain) :
			attackLevel(attackLevel), sustainLevel(sustainLevel), attack(attack), decay(decay), release(release),
			freq(freq), gain(gain), fb_gain(fb_gain) {}

	public:
		/*アタック時の最大ゲイン*/
		T attackLevel;
		/*サスティン時の最大ゲイン*/
		T sustainLevel;
		/*アタック時の持続サンプル数*/
		T attack;
		/*ディケイ時の持続サンプル数*/
		T decay;
		/*リリース時の持続宇サンプル数*/
		T release;
		/*生成周波数*/
		T freq;
		/*ゲイン*/
		T gain;
		/*フィードバック用ゲイン*/
		T fb_gain;
	};

	template <typename T>
	struct Parameter {
	public:
		/*コンストラクタ
		.Paramリスト*/
		Parameter(const std::initializer_list<Param<T>>& param) {
			this->param.assign(param.begin(), param.end());
		}

	public:
		/*パラメータ*/
		std::vector<Param<T>>param;
	};

	using ParamRatio = Parameter<float>;
	using ParamFix   = Parameter<std::uint32_t>;
}
