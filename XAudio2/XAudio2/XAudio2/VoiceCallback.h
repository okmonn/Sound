#pragma once
#include "Voice/Voice.h"
#include <xaudio2.h>

template <typename T>
struct VoiceCallback :
	public IXAudio2VoiceCallback {
public:
	/*コンストラクタ
	.Voiceのポインタ*/
	VoiceCallback(Voice<T>* obj) : voice(obj) {}
	/*現在のバッファの最初のバイトが消費される前に呼ばれる
	.XAUDIO2_BUFFER.pContext*/
	void __stdcall OnBufferStart(void* pBufferContext) {}
	/*現在のバッファの最後のバイトが消費された際に呼ばれる
	.XAUDIO2_BUFFER.pContext*/
	void __stdcall OnBufferEnd(void* pBufferContext) {
		voice->Reading();
	}
	/*ループの終了位置に達した際に呼ばれる
	.XAUDIO2_BUFFER.pContext*/
	void __stdcall OnLoopEnd(void* pBufferContext) {}
	/*最終バッファの使用が完了した際に呼ばれる*/
	void __stdcall OnStreamEnd(void) {}
	/*エラーが発生した際に呼ばれる
	.XAUDIO2_BUFFER.pContext*/
	void __stdcall OnVoiceError(void* pBufferContext, long error) {}
	/*音声の処理パスが終了した際に呼ばれる*/
	void __stdcall OnVoiceProcessingPassEnd() {}
	/*キューからデータを読み取る前に呼ばれる
	.必要データバイトサイズ*/
	void __stdcall OnVoiceProcessingPassStart(std::uint32_t BytesRequired) {}

private:
	/*Voiceのポインタ*/
	Voice<T>* voice;
};
