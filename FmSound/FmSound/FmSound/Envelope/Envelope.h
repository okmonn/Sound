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

	struct Envelope {
	public:
		/*コンストラクタ*/
		Envelope();
		/*メンバの更新
		return ゲイン*/
		std::uint32_t UpDate(void);

	public:
		/*動作状態の設定
		.動作状態
		return 動作中：1　非動作：0*/
		std::uint8_t SetState(const EV_STATE& state);

	public:
		/*代入演算子*/
		void operator=(const Envelope& ev);

	public:
		/*ADSR*/
		ADSR adsr;
		/*動作状態*/
		EV_STATE state;
		/*現在のゲイン*/
		std::uint32_t gain;
		/*ゲイン変化量*/
		std::int32_t delta;
		/*動作状態維持カウンタ*/
		std::uint32_t cnt;
	};
}
