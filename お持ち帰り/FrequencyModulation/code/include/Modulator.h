#ifndef FM_MODULATOR
#define FM_MODULATOR

/*8BIT�����؂�ւ��p*/
#define SOUND_8BIT

#include "Envelope.h"
#include "Feedback.h"

/*���W�����[�^�̓����~���*/
#define MOD_STATE_STOP      0x00
/*���W�����[�^�̓��쒆���*/
#define MOD_STATE_EXECUTION 0x01

typedef struct {
	/*�G���x���[�v*/
	Envelope envelope;
	/*�t�B�[�h�o�b�N*/
	Feedback feedback;
	/*�T���v�����O���g��*/
	uint32_t sample_freq;
	/*���݂̃T�C���g�z��̎Q�Ɣԍ�*/
	uint32_t table_index;
	/*�T�C���g�z��̎Q�ƈʒu�̈ړ���*/
	uint32_t index_move_value;
	/*�ϒ����g���̔䗦(�������F16bit)*/
	uint32_t mod_freq;
	/*�T�C���g�z��*/
#ifndef SOUND_8BIT
	const int16_t* sin_wave;
#else
	const uint8_t* sin_wave;
#endif
	/*������*/
	uint8_t state;
} Modulator;

/*�R���X�g���N�^
.Modulator�̃|�C���^
.�T���v�����O���g��
.�T�C���g�z��̃|�C���^*/
#ifndef SOUND_8BIT
void Modulator_Constructor(Modulator* modulator, const uint32_t sample_freq, const int16_t* sin_wave);
#else
void Modulator_Constructor(Modulator* modulator, const uint32_t sample_freq, const uint8_t* sin_wave);
#endif
/*�ϒ����g���̔䗦�̐ݒ�
.Modulator�̃|�C���^
.�ϒ����g���̔䗦(0.0f�`1.0f)*/
void Modulator_SetModulationFrequencyRatio(Modulator* modulator, const float modulation_freq_ratio);
/*�ϒ����g���̐ݒ�
.Modulator�̃|�C���^
.�������g��*/
void Modulator_SetModulationFrequency(Modulator* modulator, const uint32_t generate_freq);
/*�M�������̊J�n
.Modulator�̃|�C���^*/
void Modulator_Start(Modulator* modulator);
/*�M�������̒�~
.Modulator�̃|�C���^*/
void Modulator_Stop(Modulator* modulator);
/*1�T���v�����̐M���̐���
.Modulator�̃|�C���^
return 1�T���v�����̐M��*/
int32_t Modulator_GenerateSignalSimple(Modulator* modulator);
/*1�T���v�����̐M���̐���
.Modulator�̃|�C���^
return 1�T���v�����̐M��*/
int32_t Modulator_GenerateSignalFB(Modulator* modulator);
/*1�T���v�����̐M���̐���
.Modulator�̃|�C���^
.���W�����[�V�����M��
return 1�T���v�����̐M��*/
int32_t Modulator_GenerateSignalModulation(Modulator* modulator, const int32_t mod_signal);

#endif
