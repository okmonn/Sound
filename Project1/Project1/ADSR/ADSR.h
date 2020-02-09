#pragma once
#include <cstdint>

struct ADSR {
public:
	/*�R���X�g���N�^*/
	ADSR();
	/*�A�^�b�N���̃Q�C���̐ݒ�
	.�Q�C���䗦(0.0f�`1.0f)*/
	void SetAttackLevel(const float& gain);
	/*�T�X�e�B�����̃Q�C���ݒ�
	.�Q�C���䗦(0.0f�`1.0f)*/
	void SetSustainLevel(const float& gain);

public:
	/*�A�^�b�N���̃Q�C��*/
	std::uint32_t attackLevel;
	/*�T�X�e�B�����̃Q�C��*/
	std::uint32_t sustainLevel;
	/*�A�^�b�N���̎����T���v����*/
	std::uint32_t attack;
	/*�f�B�P�C���̎����T���v����*/
	std::uint32_t decay;
	/*�����[�X���̎����T���v����*/
	std::uint32_t release;
};