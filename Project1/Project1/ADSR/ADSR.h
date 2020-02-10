#pragma once
#include <cstdint>

struct ADSR {
public:
	/*�R���X�g���N�^*/
	ADSR();
	/*�A�^�b�N���̍ő�Q�C���̐ݒ�
	.�Q�C��*/
	void SetAttackLevel(const float& gain);
	void SetAttackLevel(const std::uint32_t& gain);
	/*�T�X�e�B�����̍ő�Q�C���̐ݒ�
	.�Q�C��*/
	void SetSustainLevel(const float& gain);
	void SetSustainLevel(const std::uint32_t& gain);

public:
	/*�A�^�b�N���̍ő�Q�C��*/
	std::uint32_t attackLevel;
	/*�T�X�e�B�����̍ő�Q�C��*/
	std::uint32_t sustainLevel;
	/*�A�^�b�N���̎����T���v����*/
	std::uint32_t attack;
	/*�f�B�P�C���̎����T���v����*/
	std::uint32_t decay;
	/*�����[�X���̎����T���v����*/
	std::uint32_t release;
};
