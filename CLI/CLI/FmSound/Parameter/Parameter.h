#pragma once
#include <vector>

struct Param {
public:
	/*�R���X�g���N�^*/
	Param();
	/*�R���X�g���N�^
	.�A�^�b�N���̍ő�Q�C��(0.0f�`1.0f)
	.�T�X�e�B�����̍ő�Q�C��(0.0f�`1.0f)
	.�A�^�b�N���̎����T���v�����䗦(0.0f�`1.0f)
	.�f�B�P�C���̎����T���v�����䗦(0.0f�`1.0f)
	.�����[�X���̎����T���v�����䗦(0.0f�`1.0f)
	.�������g���䗦(0.0f�`1.0f)
	.�t�B�[�h�o�b�N�p�Q�C��(0.0f�`1.0f)
	.�Q�C��(0.0f�`1.0f)*/
	Param(const float& attackLevel, const float& sustainLevel, const float& attack, const float& decay, const float& release,
		const float& freq_ratio, const float& fb_gain, const float& gain = 1.0f);

public:
	/*�A�^�b�N���̍ő�Q�C��*/
	float attackLevel;
	/*�T�X�e�B�����̍ő�Q�C��*/
	float sustainLevel;
	/*�A�^�b�N���̎����T���v�����䗦*/
	float attack;
	/*�f�B�P�C���̎����T���v�����䗦*/
	float decay;
	/*�����[�X���̎����T���v�����䗦*/
	float release;
	/*�������g���䗦*/
	float freq_ratio;
	/*�t�B�[�h�o�b�N�p�Q�C��*/
	float fb_gain;
	/*�Q�C��*/
	float gain;
};

struct Parameter {
public:
	/*�R���X�g���N�^
	.�p�����[�^���X�g*/
	Parameter(const std::initializer_list<Param>& param);

public:
	/*�p�����[�^*/
	std::vector<Param>param;
};
