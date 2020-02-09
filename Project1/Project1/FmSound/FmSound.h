#pragma once
#include "../Operator/Operator.h"
#include "../Parameter/Parameter.h"
#include <functional>

struct FmSound {
	/*�R���X�g���N�^*/
	FmSound();
	/*�R���X�g���N�^
	.�T���v�����O���g��
	.�������g��*/
	FmSound(const std::uint32_t& sample, const std::uint32_t& freq = 440);
	/*�p�����[�^�̓K�p
	.Parameter*/
	void ApplyParameter(const Parameter& parameter);
	/*�֐��|�C���^�̓K�p
	.�֐��|�C���^*/
	void ApplyAlgorithmFunction(const std::function<std::int32_t(FmSound*)>& algorithm);
	/*�M�������̊J�n*/
	void Start(void);
	/*�M�������̒�~*/
	void Stop(void);
	/*�M���̐���
	.�i�[�o�b�t�@
	.�o�b�t�@��*/
	void CreateSignal(std::int16_t* buf, const std::uint32_t& num);
	/*�M���̐���
	.�i�[�o�b�t�@
	.�o�b�t�@��*/
	void CreateSignal(std::uint8_t* buf, const std::uint32_t& num);
	/*�M���̐���()*/
	/*�T���v�����O���g���̐ݒ�
	.�T���v�����O���g��*/
	void SetSample(const std::uint32_t& sample);
	/*�������g���̐ݒ�
	.�������g��*/
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
	std::function<std::int32_t(FmSound* fm)>func;
};
