#pragma once
#include <cstdint>

struct Feedback {
public:
	/*�R���X�g���N�^*/
	Feedback();
	/*�t�B�[�h�o�b�N�p�Q�C���̐ݒ�
	.�Q�C���䗦(0.0f�`1.0f)*/
	void SetGain(const float& gain);
	/*�t�B�[�h�o�b�N�p�Q�C���̐ݒ�
	.�Q�C���䗦(0.0f�`1.0f)*/
	void SetGainFix(const float& gain);
	
public:
	/*�t�B�[�h�o�b�N�p�Q�C��*/
	std::uint32_t gain;
	/*�O��̏o�̓f�[�^*/
	std::int32_t data;
};
