#ifndef ADSR_ATTACK
#define ADSR_ATTACK

#include <stdint.h>

typedef struct {
	/*�ő�Q�C��(0x00�`0xFFFFFFFF)*/
	uint32_t max_gain;
	/*��������(�T���v����)*/
	uint32_t duration;
} Attack;

/*�R���X�g���N�^
.Attack�̃|�C���^*/
void Attack_Constructor(Attack* attack);
/*�ő�Q�C���̐ݒ�
.Attack�̃|�C���^
.�Q�C���䗦(0.0f�`1.0f)
.���ʔ䗦*/
void Attack_SetMaxGain(Attack* attack, const float gain_ratio, const float valume_ratio);
/*�������Ԃ̐ݒ�
.Attack�̃|�C���^
��������(�T���v����)*/
void Attack_SetDuration(Attack* attack, const uint32_t duration);

#endif
