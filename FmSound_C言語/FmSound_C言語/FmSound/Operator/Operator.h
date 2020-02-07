#pragma once
#include "../Envelope/Envelope.h"
#include "../Feedback/Feedback.h"

typedef struct {
	/*�G���x���[�v*/
	Envelope ev;
	/*ADSR*/
	ADSR adsr;
	/*�t�B�[�h�o�b�N*/
	Feedback fb;
	/*�ǂݏo���ʒu*/
	uint32_t pos;
	/*�ǂݏo�����x*/
	uint32_t speed;
	/*�������g���䗦*/
	uint32_t ratio;
	/*����t���O*/
	uint8_t flag;
}Operator;

/*�R���X�g���N�^
.Operator�̃|�C���^*/
void Operator_Constructor(Operator* op);
/*�M�������̊J�n
.Operator�̃|�C���^*/
void Operator_Start(Operator* op);
/*�M�������̒�~
.Operator�̃|�C���^*/
void Operator_Stop(Operator* op);
/*�M���̐���(���W�����[�V�����Ȃ��A�t�B�[�h�o�b�N�Ȃ�)
.Operator�̃|�C���^
return �M��*/
int32_t CreateSignalSimple(Operator* op);
/*�M���̐���(���W�����[�V�����Ȃ��A�t�B�[�h�o�b�N����)
.Operator�̃|�C���^
return �M��*/
int32_t CreateSignalFB(Operator* op);
/*�M���̐���(���W�����[�V��������A�t�B�[�h�o�b�N�Ȃ�)
.Operator�̃|�C���^
.���W�����[�V�����M��
return �M��*/
int32_t CreateSignalModulation(Operator* op, const int32_t mod);
/*�ǂݏo�����x�̐ݒ�
.Operator�̃|�C���^
.�������g��
.�T���v�����O���g��*/
void Operator_SetSpeed(Operator* op, const uint32_t freq, const uint32_t sample);
/*�������g���䗦�̐ݒ�
.Operator�̃|�C���^
.�������g���䗦*/
void Operator_SetRatio(Operator* op, const float ratio);
