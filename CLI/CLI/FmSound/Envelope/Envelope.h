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
		/*�����Ԃ̑���*/
		MAX
	};
}

struct Envelope {
public:
	/*�R���X�g���N�^*/
	Envelope();
	/*�p�����[�^�̍X�V
	return �Q�C��*/
	std::int32_t UpDate(void);
	/*�����Ԃ̐ݒ�
	.������
	return ���쒆�Ftrue�@��~���Ffalse*/
	bool SetState(const FM::EV_STATE& state);

public:
	/*ADSR*/
	ADSR adsr;
	/*������*/
	FM::EV_STATE state;
	/*���݂̃Q�C��*/
	std::uint32_t gain;
	/*�Q�C���ω���*/
	std::int32_t delta;
	/*�Q�C���ω��J�E���^*/
	std::uint32_t cnt;
};
