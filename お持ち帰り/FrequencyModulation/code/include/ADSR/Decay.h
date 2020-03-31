#ifndef ADSR_DECAY
#define ADSR_DECAY

#include <stdint.h>

typedef struct {
	/*��������(�T���v����)*/
	uint32_t duration;
} Decay;

/*�R���X�g���N�^
.Decay�̃|�C���^*/
void Decay_Constructor(Decay* decay);
/*�������Ԃ̐ݒ�
.Decay�̃|�C���^
.��������(�T���v����)*/
void Decay_SetDuration(Decay* decay, const uint32_t duration);

#endif
