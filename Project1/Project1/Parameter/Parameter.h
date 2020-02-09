#pragma once
#include <vector>

struct Param {
public:
	/*�R���X�g���N�^*/
	Param();
	/*�R���X�g���N�^
	.�A�^�b�N���̃Q�C��(0.0f�`1.0f)
	.�T�X�e�B�����̃Q�C��(0.0f�`1.0f)
	.�A�^�b�N���̃T���v�����䗦(0.0f�`1.0f)
	.�f�B�P�C���̃T���v�����䗦(0.0f�`1.0f)
	.�����[�X���̃T���v�����䗦(0.0f�`1.0f)
	.�������g���䗦(0.0f�`1.0f)
	.�Q�C��(0.0f�`1.0f)
	.�t�B�[�h�o�b�N�p�Q�C��(0.0f�`1.0f)*/
	Param(const float& attackLevel, const float& sustainLevel, const float& attack, const float& decay, const float& release,
		const float& freq_ratio, const float& gain_ratio, const float& fb_gain);

public:
	/*�A�^�b�N���̃Q�C��*/
	float attackLevel;
	/*�T�X�e�B�����̃Q�C��*/
	float sustainLevel;
	/*�A�^�b�N���̃T���v�����䗦*/
	float attack;
	/*�f�B�P�C���̃T���v�����䗦*/
	float decay;
	/*�����[�X���̃T���v�����䗦*/
	float release;
	/*�������g���䗦*/
	float freq_ratio;
	/*�Q�C���䗦*/
	float gain_ratio;
	/*�t�B�[�h�o�b�N�Q�C��*/
	float fb_gain;
};

struct Parameter {
public:
	/*�R���X�g���N�^
	.Param���X�g*/
	Parameter(const std::initializer_list<Param>& param);

public:
	/*�p�����[�^*/
	std::vector<Param>param;
};
