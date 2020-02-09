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
		/*�����Ԑ�*/
		MAX
	};
}

struct Envelope {
public:
	/*�R���X�g���N�^*/
	Envelope();
	/*�����o�̍X�V
	return �Q�C��*/
	std::uint32_t UpDate(void);
	/*�����Ԃ̎擾
	.�G���x���[�v�̓�����
	return ���쒆�Ftrue�@�񓮍�Ffalse*/
	bool SetState(const FM::EV_STATE& state);
	/*������Z�q�I�[�o�[���[�h
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
	/*�����ԑJ�ڃJ�E���^*/
	std::uint32_t cnt;
};
