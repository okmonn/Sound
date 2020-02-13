#pragma once
#include "Parameter.h"
#include "Operator/Operator.h"
#include <functional>

namespace FM {
	template <typename T>
	struct FmSound {
	public:
		/*�R���X�g���N�^*/
		FmSound();
		/*�R���X�g���N�^
		.�T���v�����O���g��
		.�������g��*/
		FmSound(const std::uint32_t& sample, const std::uint32_t& freq = 440);
		/*�p�����[�^�̓K�p
		.Parameter�̎Q��*/
		void ApplyParameter(const Parameter<float>& parameter);
		/*�p�����[�^�̓K�p(Parameter.param.gain�͖�������܂�)
		.Parameter�̎Q��*/
		void ApplyParameterFix(const Parameter<std::uint32_t>& parameter);
		/*�A���S���Y�������֐��̓K�p
		.�֐��|�C���^*/
		void ApplyAlgorithmFunction(const std::function<std::int32_t(FmSound*)>& func);
		/*�M�������̊J�n*/
		void Start(void);
		/*�M�������̒�~*/
		void Stop(void);
		/*�M���̐���
		.�i�[�o�b�t�@
		.�o�b�t�@��*/
		void CreateSignal(T* buf, const std::uint32_t& num);

	public:
		/*�T���v�����O���g���̐ݒ�
		.�T���v�����O���g��*/
		void SetSample(const std::uint32_t& sample);
		/*�������g���̐ݒ�
		.�������g��*/
		void SetFreq(const float& freq);
		void SetFreq(const std::uint32_t& freq);

	public:
		/*�I�y���[�^*/
		std::vector<Operator<T>>op;

	private:
		/*�T���v�����O���g��*/
		std::uint32_t sample;
		/*�������g��*/
		std::uint32_t freq;
		/*�֐��|�C���^*/
		std::function<std::int32_t(FmSound*)>function;
	};

	using Fm_8  = FmSound<std::uint8_t>;
	using Fm_16 = FmSound<std::int16_t>;
}
