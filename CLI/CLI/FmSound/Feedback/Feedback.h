#pragma once
#include <cstdint>

struct Feedback {
public:
	/*�R���X�g���N�^*/
	Feedback();
	/*�Q�C���̐ݒ�
	.�Q�C��(0.0f�`1.0f)*/
	void SetGain(const float& gain);

public:
	/*�Q�C��*/
	std::uint32_t gain;
	/*�t�B�[�h�o�b�N�p�o�̓f�[�^*/
	std::int32_t data;
};
