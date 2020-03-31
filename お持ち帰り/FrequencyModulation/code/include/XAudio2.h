#ifndef SOUND_API_XAUDIO2
#define SOUND_API_XAUDIO2

#include <stdint.h>
#include <xaudio2.h>

/*XAudio2の停止状態*/
#define XAUDIO2_STATE_STOP      0x00
/*XAudio2の動作中状態*/
#define XAUDIO2_STATE_EXECUTION 0x01

typedef struct {
	/*サンプリング周波数*/
	uint32_t sample_freq;
	/*量子化ビット数*/
	uint16_t quantization_bits;
	/*チャンネル数*/
	uint16_t channel;
	/*ソースボイス*/
	IXAudio2SourceVoice* rsc_voice;
	/*動作状態*/
	uint8_t state;
} XAudio2;

/*コンストラクタ
.XAudio2のポインタ
.サンプリング周波数
.量子化ビット数
.チャネル数*/
void XAudio2_Constructor(XAudio2* xaudio2, const uint32_t sample_freq,
	const uint16_t quantization_bits, const uint16_t channel);
/*デストラクタ
.XAudio2のポインタ
.XAudio2数*/
void XAudio2_Destructor(XAudio2* xaudio2, const uint32_t xaudio2_num);
/*波形の再生
.XAudio2のポインタ
.波形バッファ
.バッファサイズ*/
#ifndef SOUND_8BIT
void XAudio2_Play(XAudio2* xaudio2, const int16_t* wave_buffer, const uint32_t buffer_size);
#else
void XAudio2_Play(XAudio2* xaudio2, const uint8_t* wave_buffer, const uint32_t buffer_size);
#endif
/*停止
.XAudio2のポインタ*/
void XAudio2_Stop(XAudio2* xaudio2);

#endif
