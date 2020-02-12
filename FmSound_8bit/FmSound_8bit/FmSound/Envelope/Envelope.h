#pragma once
#include "../ADSR/ADSR.h"

namespace FM {
	/*�G���x���[�v�̓�����*/
	enum class EV_STATE {
		/*����*/
		done,
		/*�A�^�b�N*/
		attack,
		/*�f�B�P�C*/
		decay,
		/*�T�X�e�B��*/
		sustain,
		/*�����[�X*/
		release,
		/*�����ԍő吔*/
		MAX
	};
}

struct Envelope {
public:
	/*�R���X�g���N�^*/
	Envelope();
	/*�����Ԃ̐ݒ�
	return ���쒆�F1�@�񓮍�F0*/
	std::uint8_t SetState(const FM::EV_STATE& state);
	/*�����o�̍X�V
	return �Q�C��*/
	std::int32_t UpDate(void);
	/*������Z�I�[�o�[���[�h
	.Envelope�̎Q��*/
	void operator=(const Envelope& ev);

public:
	/*ADSR*/
	ADSR adsr;
	/*������*/
	FM::EV_STATE state;
	/*���݂̃Q�C��*/
	std::uint32_t gain;
	/*�Q�C���ω���*/
	std::int32_t delta;
	/*�����Ԉێ��J�E���^*/
	std::uint32_t cnt;
};
