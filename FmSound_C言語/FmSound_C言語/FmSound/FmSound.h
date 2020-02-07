#pragma once
#include "Modulator/Modulator.h"

typedef struct {
	/*���W�����[�^*/
	Modulator mod;
	/*�֐��|�C���^*/
	int32_t(*algorithm)(Modulator*);
}FmSound;

/*�R���X�g���N�^
.FmSound�̃|�C���^
.�T���v�����O���g��*/
void FmSound_Constructor(FmSound* fm, const uint32_t sample);
/*�A���S���Y�������̓K�p
.FmSound�̃|�C���^
.�֐��|�C���^*/
void ApplyAlgorithmFunction(FmSound* fm, int32_t(*func)(Modulator*));
/*�p�����[�^�̓K�p
.FmSound�̃|�C���^
.Parameter�̃|�C���^
.Parameter�̐�*/
void ApplyParameter(FmSound* fm, const Parameter* parameter, const uint32_t num);
/*�M�������̊J�n
.FmSound�̃|�C���^*/
void Start(FmSound* fm);
/*�M�������̒�~
.FmSound�̃|�C���^*/
void Stop(FmSound* fm);
/*�M���̐���
.FmSound�̃|�C���^
.�i�[�o�b�t�@
.�o�b�t�@��*/
void CreateSignal(FmSound* fm, int16_t* buf, const uint32_t num);
/*�������g���̐ݒ�
.FmSound�̃|�C���^
.�������g��*/
void SetFreq(FmSound* fm, const uint32_t freq);