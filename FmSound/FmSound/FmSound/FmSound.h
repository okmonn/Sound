#pragma once
#include "Parameter.h"
#include "Operator/Operator.h"
#include <functional>

namespace FM {
	template <typename T>
	struct FmSound {
	public:
		/*コンストラクタ*/
		FmSound();
		/*コンストラクタ
		.サンプリング周波数
		.生成周波数*/
		FmSound(const std::uint32_t& sample, const std::uint32_t& freq = 440);
		/*パラメータの適用
		.Parameterの参照*/
		void ApplyParameter(const Parameter<float>& parameter);
		/*パラメータの適用(Parameter.param.gainは無視されます)
		.Parameterの参照*/
		void ApplyParameterFix(const Parameter<std::uint32_t>& parameter);
		/*アルゴリズム処理関数の適用
		.関数ポインタ*/
		void ApplyAlgorithmFunction(const std::function<std::int32_t(FmSound*)>& func);
		/*信号生成の開始*/
		void Start(void);
		/*信号生成の停止*/
		void Stop(void);
		/*信号の生成
		.格納バッファ
		.バッファ数*/
		void CreateSignal(T* buf, const std::uint32_t& num);

	public:
		/*サンプリング周波数の設定
		.サンプリング周波数*/
		void SetSample(const std::uint32_t& sample);
		/*生成周波数の設定
		.生成周波数*/
		void SetFreq(const float& freq);
		void SetFreq(const std::uint32_t& freq);

	public:
		/*オペレータ*/
		std::vector<Operator<T>>op;

	private:
		/*サンプリング周波数*/
		std::uint32_t sample;
		/*生成周波数*/
		std::uint32_t freq;
		/*関数ポインタ*/
		std::function<std::int32_t(FmSound*)>function;
	};

	using Fm_8  = FmSound<std::uint8_t>;
	using Fm_16 = FmSound<std::int16_t>;
}
