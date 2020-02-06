#pragma once
#include "Operator/Operator.h"
#include "Parameter/Parameter.h"
#include <functional>

struct FmSound {
public:
	/*�R���X�g���N�^*/
	FmSound();
	/*�R���X�g���N�^
	.�T���v�����O���g��
	.�������g��*/
	FmSound(const std::uint32_t& sample, const std::uint32_t& freq = 440);
	/*�M�������̊J�n*/
	void Start(void);
	/*�M�������̒�~*/
	void Stop(void);
	/*�M���̐���
	.�i�[�o�b�t�@
	.�o�b�t�@��*/
	void CreateSignal(std::int16_t* buf, const std::uint32_t& num);
	/*�T���v�����O���g���̐ݒ�(SetCreateFreq���s���O�ɌĂяo��)
	.�T���v�����O���g��*/
	void SetSample(const std::uint32_t& sample);
	/*�������g���̐ݒ�
	.�������g��*/
	void SetCreateFreq(const std::uint32_t& freq);
	/*�p�����[�^�̓K�p
	.�p�����[�^*/
	void ApplyParameter(const Parameter& parameter);
	/*����֐��̓K�p
	.�֐��|�C���^*/
	void ApplyFunction(const std::function<std::int32_t(FmSound*)>& func);

public:
	/*�I�y���[�^*/
	std::vector<Operator>op;

private:
	/*�T���v�����O���g��*/
	std::uint32_t sample;
	/*�������g��*/
	std::uint32_t freq;
	/*�֐��|�C���^*/
	std::function<std::int32_t(FmSound*)>function;
};
