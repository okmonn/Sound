#pragma once
#include "Voice/Voice.h"
#include <cstdint>
#include <unordered_map>

struct IXAudio2;
struct IXAudio2MasteringVoice;

class XAudio2 {
	friend Voice;
public:
	/*コンストラクタ*/
	XAudio2();
	/*デストラクタ*/
	~XAudio2();

private:
	/*オーディオの生成*/
	void CreateAudio(void);
	/*マスタリングボイスの生成*/
	void CreateMastering(void);

private:
	/*オーディオ*/
	IXAudio2* audio;
	/*マスタリングボイス*/
	IXAudio2MasteringVoice* mastering;
	/*ボイスリスト*/
	std::unordered_map<std::uint32_t, Voice*>voice;
};

/*XAudio2の生成
.XAudio2のポインタのポインタ
return 成功：1　失敗：0*/
std::uint8_t CreateXAudio2(XAudio2** engine);
/*XAudio2の破棄
.XAudio2のポインタのポインタ*/
void DeleteXAudio2(XAudio2** engine);


