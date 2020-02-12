#pragma once
#include <fstream>

struct WaveWriter {
private:
	/*RIFFチャンク*/
	struct RIFF {
	public:
		/*コンストラクタ*/
		RIFF() : size(0) {
			std::string tmp = "RIFF";
			std::memcpy(id, tmp.data(), sizeof(id));
			tmp = "WAVE";
			std::memcpy(type, tmp.data(), sizeof(type));
		}

	public:
		/*ID(RIFF)*/
		std::uint8_t id[4];
		/*ファイル合計サイズ-8*/
		std::uint32_t size;
		/*タイプ(WAVE)*/
		std::uint8_t type[4];
	};
	/*fmtチャンク*/
	struct FMT {
	public:
		/*コンストラクタ*/
		FMT() : channel(0), sample(0), byte(0), block(0), bit(0) {
			std::string tmp = "fmt ";
			std::memcpy(id, tmp.data(), sizeof(id));
			size = sizeof(FMT) - (sizeof(FMT::id) + sizeof(FMT::size));
			type = 1;
		}

	public:
		/*ID(fmt )*/
		std::uint8_t id[4];
		/*フォーマットサイズ(16)*/
		std::uint32_t size;
		/*フォーマットタイプ(PCM = 1)*/
		std::uint16_t type;
		/*チャンネル数*/
		std::uint16_t channel;
		/*サンプリング周波数*/
		std::uint32_t sample;
		/*Byte/Sec*/
		std::uint32_t byte;
		/*ブロックサイズ*/
		std::uint16_t block;
		/*量子化ビット数*/
		std::uint16_t bit;
	};
	/*dataチャンク*/
	struct DATA {
	public:
		/*コンストラクタ*/
		DATA() : size(0) {
			std::string tmp = "data";
			std::memcpy(id, tmp.data(), sizeof(id));
		}

	public:
		/*ID(data)*/
		std::uint8_t id[4];
		/*ファイル合計サイズ-126*/
		std::uint32_t size;
	};

public:
	/*コンストラクタ*/
	WaveWriter();
	/*コンストラクタ
	.書き込みファイル名
	.サンプリング周波数
	.量子化ビット数
	.チャンネル数*/
	WaveWriter(const std::string& fileName, const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel);
	/*ファイルオープン
	.書き込みファイル名
	.サンプリング周波数
	.量子化ビット数
	.チャンネル数
	return 成功：1　失敗：0*/
	std::uint8_t Open(const std::string& fileName, const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel);
	/*書き込み
	.サウンドデータバッファ
	.バッファ数
	return 書き込みバイト数*/
	template <typename T>
	std::uint32_t Write(const T* buf, const std::uint32_t& num);
	/*ファイルクローズ*/
	void Close(void);

private:
	/*書き込みファイルポインタ*/
	std::ofstream file;
	/*RIFFチャンク*/
	RIFF riff;
	/*fmtチャンク*/
	FMT fmt;
	/*dataチャンク*/
	DATA data;
};
