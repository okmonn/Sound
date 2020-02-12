#pragma once
#include <array>
#include <vector>
#include <memory>

struct IXAudio2SourceVoice;
class XAudio2;
class VoiceCallback;

class Voice {
	friend XAudio2;
	friend VoiceCallback;
public:
	/*コンストラクタ
	.エンジン
	.サンプリング周波数
	.量子化ビット数
	.チャンネル数*/
	Voice(XAudio2* engine, const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel);
	/*デストラクタ*/
	~Voice();
	/*再生*/
	void Play(void);
	/*停止*/
	void Stop(void);
	/*サウンドデータの追加
	.サウンドバッファ
	.バッファ数*/
	void AddSoundQueue(const std::uint8_t* buf, const std::uint32_t& num);
	
private:
	/*フォーマットの設定
	.サンプリング周波数
	.量子化ビット数
	.チャンネル数
	.floatフラグ*/
	void* GetFmt(const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel, const std::uint8_t& flag = 0);
	/*ソースボイスの生成*/
	void CreateVoice(void* fmt);
	/*サブミット*/
	void Submit(void);
	/*終了*/
	void Finish(void);

private:
	/*エンジン*/
	XAudio2* engine;
	/*ボイスコールバック*/
	std::unique_ptr<VoiceCallback>callback;
	/*ソースボイス*/
	IXAudio2SourceVoice* voice;
	/*サウンドデータ*/
	std::array<std::vector<std::uint8_t>, 2>wave;
	int index = 0;
	int read = 0;
};
