#pragma once
#include "SourceVoice/SourceVoice.h"
#include <list>

struct IXAudio2;
struct IXAudio2MasteringVoice;

class XAudio {
	friend SourceVoice;
public:
	/*コンストラクタ*/
	XAudio();
	/*デストラクタ*/
	~XAudio();
	
private:
	/*オーディオの生成*/
	void CreateAudio(void);
	/*マスタリングソースの生成*/
	void CreateMastering(void);
	/*メンバの初期化*/
	void Initialize(void);
	/*ソースボイスのリストに追加
	.SourceVoiceのポインタ*/
	void AddList(SourceVoice* voice);
	/*ソースボイスのリストから削除
	.SourceVoiceのポインタ*/
	void DeleteList(SourceVoice* voice);

	/*オーディオ*/
	IXAudio2* audio;
	/*マスタリングボイス*/
	IXAudio2MasteringVoice* mastering;
	/*ソースボイスリスト*/
	std::list<SourceVoice*>voice;
};

/*XAudioの生成
.XAudio*/
long CreateXAudio(XAudio** engine);
/*XAudioの破棄
.XAudio*/
long Release(XAudio** engine);
