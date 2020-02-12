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
	/*�R���X�g���N�^
	.XAudio2�����|�C���^
	.�T���v�����O���g��
	.�`�����l����
	.���������_�t���O*/
	Voice(XAudio2* obj, const std::uint32_t& sample, const std::uint8_t& channel, const std::uint8_t& flag);
	/*�f�X�g���N�^*/
	~Voice();
	/*�Đ��J�n*/
	void Play(void);
	/*�Đ���~*/
	void Stop(void);
	/*�󂫃T�E���h�o�b�t�@�ɃT�E���h�f�[�^��K�p
	.�T�E���h�o�b�t�@
	.�o�b�t�@��*/
	void AddSoundBuffer(const T* buf, const std::uint32_t& num);

private:
	/*�t�H�[�}�b�g�̎擾
	.�T���v�����O���g��
	.�ʎq���r�b�g��
	.�`�����l����
	.���������_�t���O
	return WAVEFORMATEXTENSIBLE*/
	void* GetFmt(const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel, const std::uint8_t& flag);
	/*�\�[�X�{�C�X�̐���
	.WAVEFORMATEXTENSIBLE�̃|�C���^*/
	void CreateSourceVoice(const void* fmt);
	/*�ǂݍ��݃C���f�b�N�X�̍X�V*/
	void Reading(void);

private:
	/*XAudio2�̃|�C���^*/
	XAudio2* engine;
	/*�R�[���o�b�N�N���X*/
	std::unique_ptr<VoiceCallback<T>>callback;
	/*�\�[�X�{�C�X*/
	IXAudio2SourceVoice* voice;
	/*�o�b�t�@�C���f�b�N�X*/
	std::uint32_t index;
	/*�ǂݍ��݃C���f�b�N�X*/
	std::uint32_t read;
	/*�T�E���h�o�b�t�@*/
	std::array<std::vector<T>, 2>wave;
};
