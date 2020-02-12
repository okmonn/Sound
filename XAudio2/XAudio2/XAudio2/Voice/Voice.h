#pragma once
#include <array>
#include <vector>
#include <memory>
#include <cstdint>

struct IXAudio2SourceVoice;
template <typename T>
struct VoiceCallback;
class XAudio2;

template <typename T>
class Voice {
	friend XAudio2;
	friend VoiceCallback<T>;
public:
	/*コンストラクタ
	.XAudio2ｍｐポインタ
	.サンプリング周波数
	.チャンネル数
	.浮動小数点フラグ*/
	Voice(XAudio2* obj, const std::uint32_t& sample, const std::uint8_t& channel, const std::uint8_t& flag);
	/*デストラクタ*/
	~Voice();
	/*再生開始*/
	void Play(void);
	/*再生停止*/
	void Stop(void);
	/*空きサウンドバッファにサウンドデータを適用
	.サウンドバッファ
	.バッファ数*/
	void AddSoundBuffer(const T* buf, const std::uint32_t& num);

private:
	/*フォーマットの取得
	.サンプリング周波数
	.量子化ビット数
	.チャンネル数
	.浮動小数点フラグ
	return WAVEFORMATEXTENSIBLE*/
	void* GetFmt(const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel, const std::uint8_t& flag);
	/*ソースボイスの生成
	.WAVEFORMATEXTENSIBLEのポインタ*/
	void CreateSourceVoice(const void* fmt);
	/*読み込みインデックスの更新*/
	void Reading(void);

private:
	/*XAudio2のポインタ*/
	XAudio2* engine;
	/*コールバッククラス*/
	std::unique_ptr<VoiceCallback<T>>callback;
	/*ソースボイス*/
	IXAudio2SourceVoice* voice;
	/*バッファインデックス*/
	std::uint32_t index;
	/*読み込みインデックス*/
	std::uint32_t read;
	/*サウンドバッファ*/
	std::array<std::vector<T>, 2>wave;
};
