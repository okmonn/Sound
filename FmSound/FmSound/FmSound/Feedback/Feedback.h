#pragma once
#include <cstdint>

namespace FM {
	struct Feedback {
	public:
		/*コンストラクタ*/
		Feedback();

	public:
		/*フィードバック用ゲインの設定
		.ゲイン*/
		void SetGain(const float& gain);
		void SetGain(const std::uint32_t& gain);

	public:
		/*前回の出力データ*/
		std::int32_t data;
		/*フィードバック用ゲイン*/
		std::uint32_t gain;
	};
}
