#ifndef FM_ENVELOPE
#define FM_ENVELOPE

#include "ADSR/Attack.h"
#include "ADSR/Decay.h"
#include "ADSR/Release.h"
#include "ADSR/Sustain.h"

/*�G���x���[�v�̓�����*/
typedef enum {
	/*��~*/
	EV_STATE_STOP,
	/*�A�^�b�N*/
	EV_STATE_ATTACK,
	/*�f�B�P�C*/
	EV_STATE_DECAY,
	/*�T�X�e�B��*/
	EV_STATE_SUSTAIN,
	/*�m�[�g�I�t*/
	EV_STATE_NOTEOFF,
	/*�����[�X*/
	EV_STATE_RELEASE,
	/*�G���x���[�v�̓����ԍő吔*/
	EV_STATE_MAX
} EV_STATE;

typedef struct {
	/*�A�^�b�N*/
	Attack attack;
	/*�f�B�P�C*/
	Decay decay;
	/*�T�X�e�B��*/
	Sustain sustain;
	/*�����[�X*/
	Release release;
	/*�Q�C��*/
	uint32_t gain;
	/*�Q�C���ω���*/
	int32_t gain_delta;
	/*��Ԏ����J�E���g*/
	uint32_t state_count;
	/*������*/
	EV_STATE state;
} Envelope;

/*�R���X�g���N�^
.Envelope�̃|�C���^
.�T���v�����O���g��*/
void Envelope_Constructor(Envelope* envelope, const uint32_t sample_freq);
/*�����Ԃ̐ݒ�
.Envelope�̃|�C���^
.�G���x���[�v�̓�����*/
void Envelope_SetState(Envelope* envelope, const EV_STATE envelope_state);
/*�G���x���[�v�̍X�V
.Envelope�̃|�C���^
.���W�����[�^�����Ԋi�[�o�b�t�@
return �Q�C��*/
uint32_t Envelope_UpDate(Envelope* envelope, uint8_t* modulator_state);

#endif
