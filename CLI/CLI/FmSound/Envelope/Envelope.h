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
		/*動作状態の総数*/
		MAX
	};
}

struct Envelope {
public:
	/*コンストラクタ*/
	Envelope();
	/*パラメータの更新
	return ゲイン*/
	std::int32_t UpDate(void);
	/*動作状態の設定
	.動作状態
	return 動作中：true　停止中：false*/
	bool SetState(const FM::EV_STATE& state);

public:
	/*ADSR*/
	ADSR adsr;
	/*動作状態*/
	FM::EV_STATE state;
	/*現在のゲイン*/
	std::uint32_t gain;
	/*ゲイン変化量*/
	std::int32_t delta;
	/*ゲイン変化カウンタ*/
	std::uint32_t cnt;
};
