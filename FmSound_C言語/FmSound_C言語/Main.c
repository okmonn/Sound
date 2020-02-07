#include "FmSound/FmSound.h"
#include <stdio.h>

/*�T���v�����O���g��*/
#define SAMPLE 48000
/*�������g��*/
#define FREQ 440

/*�p�����[�^*/
Parameter parameter[] = {
	{0.25f, 0.2f, 1.3f, 0.7f , 0.3f, 2.0f, 2.0f, 0.0f},
	{0.9f , 0.0f, 0.6f, 0.2f , 0.5f, 0.5f, 2.0f, 0.57f},
};

/*�t�@�C�������o��
.�����o���t�@�C����
.�T���v�����O���g��
.�ʎq���r�b�g��
.�`�����l����
.�g�`�o�b�t�@
.�o�b�t�@��*/
void WaveWriter_int16(const char* fileName, const uint32_t sample, const uint8_t bit, const uint8_t channel, const int16_t* wave, const uint32_t num);
void WaveWriter_int16(const char* fileName, const uint32_t sample, const uint8_t bit, const uint8_t channel, const int16_t* wave, const uint32_t num){
	typedef struct {
		/*ID*/
		char id[4];
		/*�t�@�C�����v�T�C�Y - 8*/
		uint32_t size;
		/*�^�C�v*/
		char type[4];
	}RIFF;
	typedef struct {
		/*ID*/
		char id[4];
		/*�t�H�[�}�b�g�T�C�Y(16)*/
		uint32_t size;
		/*�t�H�[�}�b�g�^�C�v(1)*/
		uint16_t type;
		/*�`�����l����*/
		uint16_t channel;
		/*�T���v�����O���g��*/
		uint32_t sample;
		/*Byte/Sec*/
		uint32_t byte;
		/*�u���b�N�T�C�Y*/
		uint16_t block;
		/*�ʎq���r�b�g��*/
		uint16_t bit;
	}FMT;
	typedef struct {
		/*ID*/
		char id[4];
		/*�t�@�C�����v�T�C�Y - 126*/
		uint32_t size;
	}DATA;

	RIFF riff;
	riff.id[0]   = 'R';
	riff.id[1]   = 'I';
	riff.id[2]   = 'F';
	riff.id[3]   = 'F';
	riff.size    = sizeof(RIFF) + sizeof(FMT) + sizeof(DATA) + sizeof(int16_t) * num;
	riff.type[0] = 'W';
	riff.type[1] = 'A';
	riff.type[2] = 'V';
	riff.type[3] = 'E';

	FMT fmt;
	fmt.id[0]   = 'f';
	fmt.id[1]   = 'm';
	fmt.id[2]   = 't';
	fmt.id[3]   = ' ';
	fmt.size    = sizeof(FMT) - sizeof(fmt.id) - sizeof(fmt.size);
	fmt.type    = 1;
	fmt.channel = channel;
	fmt.sample  = sample;
	fmt.bit     = bit;
	fmt.block   = (fmt.bit / 8) * fmt.channel;
	fmt.byte    = fmt.sample * fmt.block;

	DATA data;
	data.id[0] = 'd';
	data.id[1] = 'a';
	data.id[2] = 't';
	data.id[3] = 'a';
	data.size  = sizeof(int16_t) * num;

	FILE* file;
	fopen_s(&file, fileName, "wb");
	fwrite(&riff, sizeof(riff), 1, file);
	fwrite(&fmt, sizeof(fmt), 1, file);
	fwrite(&data, sizeof(data), 1, file);
	fwrite(wave, sizeof(int16_t)* num, 1, file);

	fclose(file);
}
/*�t�@�C�������o��
.�����o���t�@�C����
.�T���v�����O���g��
.�ʎq���r�b�g��
.�`�����l����
.�g�`�o�b�t�@
.�o�b�t�@��*/
void WaveWriter_int8(const char* fileName, const uint32_t sample, const uint8_t bit, const uint8_t channel, const uint8_t* wave, const uint32_t num);
void WaveWriter_int8(const char* fileName, const uint32_t sample, const uint8_t bit, const uint8_t channel, const uint8_t* wave, const uint32_t num) {
	typedef struct {
		/*ID*/
		char id[4];
		/*�t�@�C�����v�T�C�Y - 8*/
		uint32_t size;
		/*�^�C�v*/
		char type[4];
	}RIFF;
	typedef struct {
		/*ID*/
		char id[4];
		/*�t�H�[�}�b�g�T�C�Y(16)*/
		uint32_t size;
		/*�t�H�[�}�b�g�^�C�v(1)*/
		uint16_t type;
		/*�`�����l����*/
		uint16_t channel;
		/*�T���v�����O���g��*/
		uint32_t sample;
		/*Byte/Sec*/
		uint32_t byte;
		/*�u���b�N�T�C�Y*/
		uint16_t block;
		/*�ʎq���r�b�g��*/
		uint16_t bit;
	}FMT;
	typedef struct {
		/*ID*/
		char id[4];
		/*�t�@�C�����v�T�C�Y - 126*/
		uint32_t size;
	}DATA;

	RIFF riff;
	riff.id[0]   = 'R';
	riff.id[1]   = 'I';
	riff.id[2]   = 'F';
	riff.id[3]   = 'F';
	riff.size    = sizeof(RIFF) + sizeof(FMT) + sizeof(DATA) + sizeof(wave[0]) * num;
	riff.type[0] = 'W';
	riff.type[1] = 'A';
	riff.type[2] = 'V';
	riff.type[3] = 'E';

	FMT fmt;
	fmt.id[0]   = 'f';
	fmt.id[1]   = 'm';
	fmt.id[2]   = 't';
	fmt.id[3]   = ' ';
	fmt.size    = sizeof(FMT) - sizeof(fmt.id) - sizeof(fmt.size);
	fmt.type    = 1;
	fmt.channel = channel;
	fmt.sample  = sample;
	fmt.bit     = bit;
	fmt.block   = (fmt.bit / 8) * fmt.channel;
	fmt.byte    = fmt.sample * fmt.block;

	DATA data;
	data.id[0] = 'd';
	data.id[1] = 'a';
	data.id[2] = 't';
	data.id[3] = 'a';
	data.size  = sizeof(wave[0]) * num;

	FILE* file;
	fopen_s(&file, fileName, "wb");
	fwrite(&riff, sizeof(riff), 1, file);
	fwrite(&fmt, sizeof(fmt), 1, file);
	fwrite(&data, sizeof(data), 1, file);
	fwrite(wave, sizeof(wave[0]) * num, 1, file);

	fclose(file);
}

/*�A���S���Y������
.Modulator�̃|�C���^
return �M��*/
int32_t Algorithm(Modulator* mod);
int32_t Algorithm(Modulator* mod) {
	int32_t pcm = CreateSignalFB(&mod->op[1]);
	int32_t signal = CreateSignalModulation(&mod->op[0], pcm);

	return signal;
}

int main() {
	FmSound fm;
	FmSound_Constructor(&fm, SAMPLE);
	SetFreq(&fm, FREQ);
	ApplyParameter(&fm, parameter, 2U);
	ApplyAlgorithmFunction(&fm, &Algorithm);
	Start(&fm);

	int cnt = 0;
	int16_t buf[SAMPLE];
	auto begin = clock();
	CreateSignal(&fm, buf, SAMPLE);
	auto end = clock();
	auto result = end - begin;
	WaveWriter_int16("Test.wav", SAMPLE, 16, 1, buf, SAMPLE);

	return 0;
}