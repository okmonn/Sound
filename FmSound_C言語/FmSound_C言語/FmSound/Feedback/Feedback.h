#pragma once
#include <stdint.h>

typedef struct {
	/*�t�B�[�h�o�b�N�p���̓��x��*/
	uint32_t gain;
	/*�O��̏o�̓f�[�^*/
	int32_t data;
}Feedback;

/*�R���X�g���N�^
.Feedback�̃|�C���^*/
void Feedback_Constructor(Feedback* fb);
/*�t�B�[�h�o�b�N�p���̓��x���̐ݒ�
.Feedback�̃|�C���^
.���̓��x���䗦*/
void Feedback_SetGain(Feedback* fb, const float gain);
