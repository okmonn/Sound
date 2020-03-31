#ifndef SOUND_API_XAUDIO2
#define SOUND_API_XAUDIO2

#include <stdint.h>
#include <xaudio2.h>

/*XAudio2�̒�~���*/
#define XAUDIO2_STATE_STOP      0x00
/*XAudio2�̓��쒆���*/
#define XAUDIO2_STATE_EXECUTION 0x01

typedef struct {
	/*�T���v�����O���g��*/
	uint32_t sample_freq;
	/*�ʎq���r�b�g��*/
	uint16_t quantization_bits;
	/*�`�����l����*/
	uint16_t channel;
	/*�\�[�X�{�C�X*/
	IXAudio2SourceVoice* rsc_voice;
	/*������*/
	uint8_t state;
} XAudio2;

/*�R���X�g���N�^
.XAudio2�̃|�C���^
.�T���v�����O���g��
.�ʎq���r�b�g��
.�`���l����*/
void XAudio2_Constructor(XAudio2* xaudio2, const uint32_t sample_freq,
	const uint16_t quantization_bits, const uint16_t channel);
/*�f�X�g���N�^
.XAudio2�̃|�C���^
.XAudio2��*/
void XAudio2_Destructor(XAudio2* xaudio2, const uint32_t xaudio2_num);
/*�g�`�̍Đ�
.XAudio2�̃|�C���^
.�g�`�o�b�t�@
.�o�b�t�@�T�C�Y*/
#ifndef SOUND_8BIT
void XAudio2_Play(XAudio2* xaudio2, const int16_t* wave_buffer, const uint32_t buffer_size);
#else
void XAudio2_Play(XAudio2* xaudio2, const uint8_t* wave_buffer, const uint32_t buffer_size);
#endif
/*��~
.XAudio2�̃|�C���^*/
void XAudio2_Stop(XAudio2* xaudio2);

#endif
