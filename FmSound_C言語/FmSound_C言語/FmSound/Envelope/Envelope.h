#pragma once
#include "../ADSR/ADSR.h"

/*�G���x���[�v�̓�����*/
typedef enum {
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
	/*�G���x���[�v�̓����Ԃ̍ő吔*/
	max
}EV_STATE;

typedef struct {
	/*������*/
	EV_STATE state;
	/*���݂̓��̓��x��*/
	uint32_t gain;
	/*���̓��x���ω����x*/
	uint32_t delta;
	/*���̓��x���ω��J�E���^*/
	uint32_t cnt;
}Envelope;

/*�R���X�g���N�^
.Envelope�̃|�C���^*/
void Envelope_Constructor(Envelope* ev);
/*�����Ԃ̐ݒ�
.Envelope�̃|�C���^
.ADSR�̃|�C���^
.�G���x���[�v�̓�����
return ����t���O*/
uint8_t Envelope_SetState(Envelope* ev, const ADSR* adsr, const EV_STATE state);
