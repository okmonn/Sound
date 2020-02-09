#pragma once
#include "../Operator/Operator.h"
#include "../Parameter/Parameter.h"
#include <functional>

struct FmSound {
	/*コンストラクタ*/
	FmSound();
	/*コンストラクタ
	.サンプリング周波数
	.生成周波数*/
	FmSound(const std::uint32_t& sample, const std::uint32_t& freq = 440);
	/*パラメータの適用
	.Parameter*/
	void ApplyParameter(const Parameter& parameter);
	/*関数ポインタの適用
	.関数ポインタ*/
	void ApplyAlgorithmFunction(const std::function<std::int32_t(FmSound*)>& algorithm);
	/*信号生成の開始*/
	void Start(void);
	/*信号生成の停止*/
	void Stop(void);
	/*信号の生成
	.格納バッファ
	.バッファ数*/
	void CreateSignal(std::int16_t* buf, const std::uint32_t& num);
	/*信号の生成
	.格納バッファ
	.バッファ数*/
	void CreateSignal(std::uint8_t* buf, const std::uint32_t& num);
	/*信号の生成()*/
	/*サンプリング周波数の設定
	.サンプリング周波数*/
	void SetSample(const std::uint32_t& sample);
	/*生成周波数の設定
	.生成周波数*/
	void SetFreq(const std::uint32_t& freq);

public:
	/*オペレータ*/
	std::vector<Operator>op;

private:
	/*サンプリング周波数*/
	std::uint32_t sample;
	/*生成周波数*/
	std::uint32_t freq;
	/*関数ポインタ*/
	std::function<std::int32_t(FmSound* fm)>func;
};
