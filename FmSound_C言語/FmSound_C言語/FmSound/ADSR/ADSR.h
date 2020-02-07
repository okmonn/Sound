#pragma once
#include <stdint.h>

typedef struct {
	/*�A�^�b�N���̍ő���̓��x��*/
	uint32_t attackLevel;
	/*�A�^�b�N���̎����T���v����*/
	uint32_t attack;
	/*�f�B�P�C���̎����T���v����*/
	uint32_t decay;
	/*�T�X�e�B�����̍ő���̓��x��*/
	uint32_t sustainLevel;
	/*�����[�X���̎����T���v����*/
	uint32_t release;
}ADSR;

/*�R���X�g���N�^
.ADSR�̃|�C���^*/
void ADSR_Constructor(ADSR* adsr);
/*�A�^�b�N���̍ő���̓��x���̐ݒ�
.ADSR�̃|�C���^
.���̓��x���䗦*/
void ADSR_SetAttackLevel(ADSR* adsr, const float level);
/*�T�X�e�B�����̍ő���̓��x���̐ݒ�
.ADSR�̃|�C���^
.���̓��x���䗦*/
void ADSR_SetSustainLevel(ADSR* adsr, const float level);
