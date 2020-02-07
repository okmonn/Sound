#pragma once

typedef struct {
	/*�A�^�b�N���̍ő���̓��x���䗦*/
	float attackLevel;
	/*�A�^�b�N���̎����T���v�����䗦*/
	float attack;
	/*�f�B�P�C���̎����T���v�����䗦*/
	float decay;
	/*�T�X�e�B�����̍ő���̓��x���䗦*/
	float sustainLevel;
	/*�����[�X���̎����T���v�����䗦*/
	float release;
	/*�������g���䗦*/
	float freq_ratio;
	/*���̓��x���䗦*/
	float gain_ratio;
	/*�t�B�[�h�o�b�N�p���̓��x���䗦*/
	float fb_gain;
}Parameter;

/*�R���X�g���N�^
.Parameter�̃|�C���^*/
void Parameter_Constructor(Parameter* parameter);
