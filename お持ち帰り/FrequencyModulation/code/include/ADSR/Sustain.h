#ifndef ADSR_SUSTAIN
#define ADSR_SUSTAIN

#include <stdint.h>

typedef struct {
	/*�ő�Q�C��(0x00�`0xFFFFFFFF)*/
	uint32_t max_gain;
} Sustain;

/*�R���X�g���N�^
.Sustain�̃|�C���^*/
void Sustain_Constructor(Sustain* sustain);
/*�ő�Q�C���̐ݒ�
.Sustain�̃|�C���^
.�Q�C���䗦(0.0f�`1.0f)
.���ʒ���*/
void Sustain_SetMaxGain(Sustain* sustain, const float gain_ratio, const float valume_ratio);

#endif
