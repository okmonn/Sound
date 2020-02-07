#include "FmSound/FmSound.h"
#include <stdio.h>

/*サンプリング周波数*/
#define SAMPLE 48000
/*生成周波数*/
#define FREQ 440

/*パラメータ*/
Parameter parameter[] = {
	{0.25f, 0.2f, 1.3f, 0.7f , 0.3f, 2.0f, 2.0f, 0.0f},
	{0.9f , 0.0f, 0.6f, 0.2f , 0.5f, 0.5f, 2.0f, 0.57f},
};

/*ファイル書き出し
.書き出しファイル名
.サンプリング周波数
.量子化ビット数
.チャンネル数
.波形バッファ
.バッファ数*/
void WaveWriter_int16(const char* fileName, const uint32_t sample, const uint8_t bit, const uint8_t channel, const int16_t* wave, const uint32_t num);
void WaveWriter_int16(const char* fileName, const uint32_t sample, const uint8_t bit, const uint8_t channel, const int16_t* wave, const uint32_t num){
	typedef struct {
		/*ID*/
		char id[4];
		/*ファイル合計サイズ - 8*/
		uint32_t size;
		/*タイプ*/
		char type[4];
	}RIFF;
	typedef struct {
		/*ID*/
		char id[4];
		/*フォーマットサイズ(16)*/
		uint32_t size;
		/*フォーマットタイプ(1)*/
		uint16_t type;
		/*チャンネル数*/
		uint16_t channel;
		/*サンプリング周波数*/
		uint32_t sample;
		/*Byte/Sec*/
		uint32_t byte;
		/*ブロックサイズ*/
		uint16_t block;
		/*量子化ビット数*/
		uint16_t bit;
	}FMT;
	typedef struct {
		/*ID*/
		char id[4];
		/*ファイル合計サイズ - 126*/
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
/*ファイル書き出し
.書き出しファイル名
.サンプリング周波数
.量子化ビット数
.チャンネル数
.波形バッファ
.バッファ数*/
void WaveWriter_int8(const char* fileName, const uint32_t sample, const uint8_t bit, const uint8_t channel, const uint8_t* wave, const uint32_t num);
void WaveWriter_int8(const char* fileName, const uint32_t sample, const uint8_t bit, const uint8_t channel, const uint8_t* wave, const uint32_t num) {
	typedef struct {
		/*ID*/
		char id[4];
		/*ファイル合計サイズ - 8*/
		uint32_t size;
		/*タイプ*/
		char type[4];
	}RIFF;
	typedef struct {
		/*ID*/
		char id[4];
		/*フォーマットサイズ(16)*/
		uint32_t size;
		/*フォーマットタイプ(1)*/
		uint16_t type;
		/*チャンネル数*/
		uint16_t channel;
		/*サンプリング周波数*/
		uint32_t sample;
		/*Byte/Sec*/
		uint32_t byte;
		/*ブロックサイズ*/
		uint16_t block;
		/*量子化ビット数*/
		uint16_t bit;
	}FMT;
	typedef struct {
		/*ID*/
		char id[4];
		/*ファイル合計サイズ - 126*/
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

/*アルゴリズム処理
.Modulatorのポインタ
return 信号*/
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