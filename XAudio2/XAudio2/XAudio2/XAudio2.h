#pragma once
#include "Voice/Voice.h"
#include <unordered_map>

struct IXAudio2;
struct IXAudio2MasteringVoice;

class XAudio2 {
	friend Voice<std::uint8_t>;
	friend Voice<std::int16_t>;
public:
	/*コンストラクタ*/
	XAudio2();
	/*デストラクタ*/
	~XAudio2();
	/*Voiceクラスの生成
	.Voiceのポインタのポインタ
	.サンプリング周波数
	.量子化ビット数
	.チャンネル数
	.浮動小数点フラグ
	return 成功：1　失敗：0*/
	template <typename T>
	std::uint8_t CreateVoice(Voice<T>** obj, const std::uint32_t& sample, const std::uint8_t& channel, const std::uint8_t& flag = 0);

private:
	/*オーディオの生成*/
	void CreateAudio(void);
	/*マスタリングボイスの生成*/
	void CreateMastering(void);
	/*ソースボイス保持クラスのポインタリストに追加
	.ソースボイス保持クラスのポインタ
	return 成功：1　失敗：0*/
	std::uint8_t AddList(void* obj);
	/*ソースボイス保持クラスのポインタリストから削除
	.ソースボイス保持クラスのポインタ
	return 成功：1　失敗：0*/
	std::uint8_t DeleteList(void* obj);

private:
	/*オーディオ*/
	IXAudio2* audio;
	/*マスタリングボイス*/
	IXAudio2MasteringVoice* mastering;
	/*ソースボイス保持クラスのポインタリスト*/
	std::unordered_map<std::uint32_t, void*>list;
};

/*XAudio2の生成
.XAudio2のポインタのポインタ
return 成功：1　失敗：0*/
std::uint8_t CreateXAudio2(XAudio2** obj);
/*XAudio2の破棄
.XAudio2のポインタのポインタ*/
void DeleteXAudio2(XAudio2** obj);
