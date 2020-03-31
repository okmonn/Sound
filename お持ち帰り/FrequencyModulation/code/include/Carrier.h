#ifndef FM_CARRIER
#define FM_CARRIER

#include "Modulator.h"
#include "Parameter.h"

/*���W�����[�^��*/
#define MOD_NUM 4
/*�T�C���g�z��̗v�f��*/
#define SIN_WAVE_NUM (4096 >> 4)

typedef struct {
	/*�T���v�����O���g��*/
	uint32_t sample_freq;
	/*�������g��(�������F16bit)*/
	uint32_t generate_freq;
	/*�T�C���g�z��*/
#ifndef SOUND_8BIT
	int16_t sin_wave[SIN_WAVE_NUM];
#else
	uint8_t sin_wave[SIN_WAVE_NUM];
#endif
	/*���W�����[�^*/
	Modulator modulator[MOD_NUM];
	/*�A���S���Y�������p�֐��|�C���^
	.Carrier�̃|�C���^
	return 1�T���v�����̐M��*/
	int32_t(*function)(void* carrier);
} Carrier;

/*�R���X�g���N�^
.Carrier�̃|�C���^
.�T���v�����O���g��*/
void Carrier_Constructor(Carrier* carrier, const uint32_t sample_freq);
/*�������g���̐ݒ�
.Carrier�̃|�C���^
.�������g��*/
void Carrier_SetGenerateFrequency(Carrier* carrier, const float generate_freq);
/*�p�����[�^�̓K��
.Carrier�̃|�C���^
.Parameter�̃|�C���^
.�p�����[�^��(���W�����[�^���ȉ�)*/
void Carrier_ApplyParameter(Carrier* carrier, const Parameter* parameter, const uint32_t parameter_num);
/*�A���S���Y�������֐��̓K��
.Carrier�̃|�C���^
.�֐��|�C���^*/
void Carrier_ApplyAlgorithmFunction(Carrier* carrier, int32_t(*functio)(Carrier*));
/*�M�������̊J�n
.Carrier�̃|�C���^*/
void Carrier_Start(Carrier* carrier);
/*�M�������̒�~
.Carrier�̃|�C���^*/
void Carrier_Stop(Carrier* carrier);
/*1�T���v�����̐M���̐���
.Carrier�̃|�C���^
return 1�T���v�����̐M��*/
#ifndef SOUND_8BIT
int16_t Carrier_GenerateSignal(Carrier* carrier);
#else
uint8_t Carrier_GenerateSignal(Carrier* carrier);
#endif

#endif
