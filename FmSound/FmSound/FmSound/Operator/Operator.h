#pragma once
#include "../Envelope/Envelope.h"
#include "../Feedback/Feedback.h"

namespace FM {
	template <typename T>
	struct FmSound;
}

namespace FM {
	template <typename T>
	struct Operator {
		friend FmSound<T>;
	public:
		/*コンストラクタ*/
		Operator();
		/*信号の生成(モジュレーションなし、フィードバックなし)
		return 信号*/
		std::int32_t CreateSignalSimple(void);
		/*信号の生成(モジュレーションなし、フィードバックあり)
		return 信号*/
		std::int32_t CreateSignalFB(void);
		/*信号の生成(モジュレーションあり、フィードバックなし)
		.モジュレーション信号
		return 信号*/
		std::int32_t CreateSignalModulation(const std::int32_t& mod);

	private:
		/*信号生成の開始*/
		void Start(void);
		/*信号生成の停止*/
		void Stop(void);

	private:
		/*読み出し速度の設定
		.サンプリング周波数*/
		void SetSpeed(const std::uint32_t& sample);
		/*読み出し速度の設定
		.生成周波数
		.サンプリング周波数*/
		void SetSpeed(const std::uint32_t& freq, const std::uint32_t& sample);
		/*生成周波数の設定
		.生成周波数*/
		void SetFreq(const float& freq);
		void SetFreq(const std::uint32_t& freq);

	private:
		/*エンベロープ*/
		Envelope ev;
		/*フィードバック*/
		Feedback fb;
		/*動作フラグ*/
		std::uint8_t flag;
		/*読み出し位置*/
		std::uint32_t pos;
		/*読み出し速度*/
		std::uint32_t speed;
		/*生成周波数*/
		std::uint32_t freq;
	};

	using Op_8  = Operator<std::uint8_t>;
	using Op_16 = Operator<std::int16_t>;
}
