#pragma once
#include "../Operator/Operator.h"
#include "../Parameter/Parameter.h"

/*�p�����[�^��*/
#define OP_NUM 4

typedef struct {
	/*�I�y���[�^*/
	Operator op[OP_NUM];
	/*�T���v�����O���g��*/
	uint32_t sample;
	/*�������g��*/
	uint32_t freq;
}Modulator; 

/*�R���X�g���N�^
.Modulator�̃|�C���^
.�T���v�����O���g��*/
void Modulator_Constructor(Modulator* mod, const uint32_t sample);
/*�p�����[�^�̓K�p
.Modulator�̃|�C���^
.Parameter�̃|�C���^*/
void Modulator_ApplyParameter(Modulator* mod, const Parameter* parameter, const uint32_t num);
/*�M�������̊J�n
.Modulator�̃|�C���^*/
void Modulator_Start(Modulator* mod);
/*�M�������̒�~
.Modulator�̃|�C���^*/
void Modulator_Stop(Modulator* mod);
/*�������g���̐ݒ�
.Modulator�̃|�C���^
.�������g��*/
void Modulator_SetFreq(Modulator* mod, const uint32_t freq);
