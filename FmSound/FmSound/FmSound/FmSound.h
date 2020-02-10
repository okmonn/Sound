#pragma once
#include "Parameter.h"
#include "Operator/Operator.h"
#include <functional>

struct FmSound {
public:
	/*�R���X�g���N�^*/
	FmSound();
	/*�R���X�g���N�^
	.�T���v�����O���g��
	.�������g��*/
	FmSound(const std::uint32_t& sample, const std::uint32_t& freq = 440);
	/*�A���S���Y�������̓K�p
	.�֐��|�C���^*/
	void ApplyAlgorithmFunction(const std::function<std::int32_t(FmSound*)>& func);
	/*�p�����[�^�̓K�p
	.�p�����[�^*/
	void ApplyParameter(const Parameter<float>& parameter);
	/*�p�����[�^�̓K�p(Parameter.param.gain�͖�������܂�)
	.�p�����[�^*/
	void ApplyParameterFix(const Parameter<std::uint32_t>& parameter);
	/*�M�������̊J�n*/
	void Start(void);
	/*�M�������̒�~*/
	void Stop(void);
	/*�M���̐���
	.�i�[�o�b�t�@
	.�o�b�t�@��*/
	void CreateSignal(std::int16_t* buf, const std::uint32_t& num);
	/*�T���v�����O���g���̐ݒ�
	.�T���v�����O���g��*/
	void SetSample(const std::uint32_t& sample);
	/*�������g���̐ݒ�
	.�������g��*/
	void SetFreq(const float& freq);
	void SetFreq(const std::uint32_t& freq);

public:
	/*�I�y���[�^*/
	std::vector<Operator>op;

private:
	/*�T���v�����O���g��*/
	std::uint32_t sample;
	/*�������g��*/
	std::uint32_t freq;
	/*�֐��|�C���^*/
	std::function<std::int32_t(FmSound*)>func;
};
