#pragma once
#include "Voice/Voice.h"
#include <xaudio2.h>

template <typename T>
struct VoiceCallback :
	public IXAudio2VoiceCallback {
public:
	/*�R���X�g���N�^
	.Voice�̃|�C���^*/
	VoiceCallback(Voice<T>* obj) : voice(obj) {}
	/*���݂̃o�b�t�@�̍ŏ��̃o�C�g��������O�ɌĂ΂��
	.XAUDIO2_BUFFER.pContext*/
	void __stdcall OnBufferStart(void* pBufferContext) {}
	/*���݂̃o�b�t�@�̍Ō�̃o�C�g������ꂽ�ۂɌĂ΂��
	.XAUDIO2_BUFFER.pContext*/
	void __stdcall OnBufferEnd(void* pBufferContext) {
		voice->Reading();
	}
	/*���[�v�̏I���ʒu�ɒB�����ۂɌĂ΂��
	.XAUDIO2_BUFFER.pContext*/
	void __stdcall OnLoopEnd(void* pBufferContext) {}
	/*�ŏI�o�b�t�@�̎g�p�����������ۂɌĂ΂��*/
	void __stdcall OnStreamEnd(void) {}
	/*�G���[�����������ۂɌĂ΂��
	.XAUDIO2_BUFFER.pContext*/
	void __stdcall OnVoiceError(void* pBufferContext, long error) {}
	/*�����̏����p�X���I�������ۂɌĂ΂��*/
	void __stdcall OnVoiceProcessingPassEnd() {}
	/*�L���[����f�[�^��ǂݎ��O�ɌĂ΂��
	.�K�v�f�[�^�o�C�g�T�C�Y*/
	void __stdcall OnVoiceProcessingPassStart(std::uint32_t BytesRequired) {}

private:
	/*Voice�̃|�C���^*/
	Voice<T>* voice;
};
