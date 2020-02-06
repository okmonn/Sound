#pragma once
#include "Operator/Operator.h"
#include "Parameter/Parameter.h"
#include <functional>

struct FmSound {
public:
	/*コンストラクタ*/
	FmSound();
	/*コンストラクタ
	.サンプリング周波数
	.生成周波数*/
	FmSound(const std::uint32_t& sample, const std::uint32_t& freq = 440);
	/*信号生成の開始*/
	void Start(void);
	/*信号生成の停止*/
	void Stop(void);
	/*信号の生成
	.格納バッファ
	.バッファ数*/
	void CreateSignal(std::int16_t* buf, const std::uint32_t& num);
	/*サンプリング周波数の設定(SetCreateFreqを行う前に呼び出す)
	.サンプリング周波数*/
	void SetSample(const std::uint32_t& sample);
	/*生成周波数の設定
	.生成周波数*/
	void SetCreateFreq(const std::uint32_t& freq);
	/*パラメータの適用
	.パラメータ*/
	void ApplyParameter(const Parameter& parameter);
	/*自作関数の適用
	.関数ポインタ*/
	void ApplyFunction(const std::function<std::int32_t(FmSound*)>& func);

public:
	/*オペレータ*/
	std::vector<Operator>op;

private:
	/*サンプリング周波数*/
	std::uint32_t sample;
	/*生成周波数*/
	std::uint32_t freq;
	/*関数ポインタ*/
	std::function<std::int32_t(FmSound*)>function;
};
