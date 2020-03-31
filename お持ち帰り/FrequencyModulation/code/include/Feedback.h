#ifndef FM_FEEDBACK
#define FM_FEEDBACK

#include <stdint.h>

typedef struct {
	/*�t�B�[�h�o�b�N�p�Q�C���䗦*/
	uint32_t gain;
	/*1�O�̐M��*/
	int32_t old_signal;
} Feedback;

/*�R���X�g���N�^
.Feedback�̃|�C���^*/
void Feedback_Constructor(Feedback* feedback);
/*�t�B�[�g�o�b�N�p�Q�C���䗦�̐ݒ�
.Feedback�̃|�C���^
.�Q�C���䗦(0.0f�`1.0f)*/
void Feedback_SetGain(Feedback* feedback, const float gain_ratio);

#endif
