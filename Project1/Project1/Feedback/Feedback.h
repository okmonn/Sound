#pragma once
#include <cstdint>

struct Feedback {
public:
	/*�R���X�g���N�^*/
	Feedback();
	/*�t�B�[�h�o�b�N�p�Q�C���̐ݒ�
	.�Q�C��*/
	void SetGain(const float& gain);
	void SetGain(const std::uint32_t& gain);
	/*�t�B�[�h�o�b�N�p�Q�C���̐ݒ�
	.�Q�C��*/
	void SetGainFix(const float& gain);

public:
	/*�t�B�[�h�o�b�N�p�Q�C��*/
	std::uint32_t gain;
	/*�O��̏o�̓f�[�^*/
	std::int32_t data;
};
