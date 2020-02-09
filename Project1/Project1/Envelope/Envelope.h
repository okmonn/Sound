#pragma once
#include "../ADSR/ADSR.h"

namespace FM {
	/*エンベロープの動作状態*/
	enum class EV_STATE {
		/*完了*/
		done,
		/*アタック*/
		attack,
		/*ディケイ*/
		decay,
		/*サスティン*/
		sustain,
		/*リリース*/
		release,
		/*動作状態数*/
		MAX
	};
}

struct Envelope {
public:
	/*コンストラクタ*/
	Envelope();
	/*メンバの更新
	return ゲイン*/
	std::uint32_t UpDate(void);
	/*動作状態の取得
	.エンベロープの動作状態
	return 動作中：true　非動作：false*/
	bool SetState(const FM::EV_STATE& state);
	/*代入演算子オーバーロード
	.Envelopeの参照*/
	void operator=(const Envelope& ev);

public:
	/*ADSR*/
	ADSR adsr;
	/*動作状態*/
	FM::EV_STATE state;
	/*現在のゲイン*/
	std::uint32_t gain;
	/*ゲイン変化量*/
	std::int32_t delta;
	/*動作状態遷移カウンタ*/
	std::uint32_t cnt;
};
