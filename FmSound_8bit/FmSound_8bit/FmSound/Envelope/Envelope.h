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
		/*動作状態最大数*/
		MAX
	};
}

struct Envelope {
public:
	/*コンストラクタ*/
	Envelope();
	/*動作状態の設定
	return 動作中：1　非動作：0*/
	std::uint8_t SetState(const FM::EV_STATE& state);
	/*メンバの更新
	return ゲイン*/
	std::int32_t UpDate(void);
	/*代入演算オーバーロード
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
	/*動作状態維持カウンタ*/
	std::uint32_t cnt;
};
