#pragma once
#include "../Envelope/Envelope.h"
#include "../Feedback/Feedback.h"

struct FmSound;

struct Operator {
	friend FmSound;
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
	/*読み出し速度の設定
	.生成周波数
	.サンプリング周波数*/
	void SetSpeed(const std::uint32_t& freq, const std::uint32_t& sample);
	/*生成周波数比率の設定
	.比率(0.0f～1.0f)*/
	void SetRatio(const float& ratio);

private:
	/*エンベロープ*/
	Envelope ev;
	/*フィードバック*/
	Feedback fb;
	/*動作フラグ*/
	bool play;
	/*読み出し位置*/
	std::uint32_t pos;
	/*読み出し速度*/
	std::uint32_t speed;
	/*生成周波数比率*/
	std::uint32_t ratio;
};
