#pragma once
#include <vector>
#include <memory>
#include <cstdint>

struct IXAudio2SourceVoice;
struct VoiceCallback;
class XAudio;

class SourceVoice {
	friend XAudio;
public:
	/*コンストラクタ
	.エンジンのポインタ
	.サンプリング周波数
	.量子化ビット数
	.チャンネル数
	.浮動小数点フラグ*/
	SourceVoice(XAudio* engine, const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel, const bool& flag = false);
	/*デストラクタ*/
	~SourceVoice();
	/*再生
	.サウンドバッファ
	.バッファ数*/
	void Play(const std::int16_t* buf, const std::uint32_t& num);
	/*再生
	.サウンドバッファ
	.バッファ数*/
	void Play(const std::uint8_t* buf, const std::uint32_t& num);
	/*停止*/
	void Stop(void);

private:
	/*フォーマットの設定
	.サンプリング周波数
	.量子化ビット数
	.チャンネル数
	.浮動小数点フラグ
	return フォーマットのポインタ*/
	void* SetFormat(const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel, const bool& flag);
	/*ソースボイスの生成
	.フォーマットのポインタ*/
	void CreateVoice(void* fmt);
	/*終了*/
	void End(void);

	/*エンジンのポイント*/
	XAudio* engine;
	/*ボイスコールバック*/
	std::unique_ptr<VoiceCallback>callback;
	/*ソースボイス*/
	IXAudio2SourceVoice* voice;
	/*再生フラグ*/
	bool flag;
	/*波形データ*/
	std::vector<std::int16_t>wave;
};
