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
	/*�R���X�g���N�^
	.�G���W��
	.�T���v�����O���g��
	.�ʎq���r�b�g��
	.�`�����l����*/
	Voice(XAudio2* engine, const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel);
	/*�f�X�g���N�^*/
	~Voice();
	/*�Đ�*/
	void Play(void);
	/*��~*/
	void Stop(void);
	/*�T�E���h�f�[�^�̒ǉ�
	.�T�E���h�o�b�t�@
	.�o�b�t�@��*/
	void AddSoundQueue(const std::uint8_t* buf, const std::uint32_t& num);
	
private:
	/*�t�H�[�}�b�g�̐ݒ�
	.�T���v�����O���g��
	.�ʎq���r�b�g��
	.�`�����l����
	.float�t���O*/
	void* GetFmt(const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel, const std::uint8_t& flag = 0);
	/*�\�[�X�{�C�X�̐���*/
	void CreateVoice(void* fmt);
	/*�T�u�~�b�g*/
	void Submit(void);
	/*�I��*/
	void Finish(void);

private:
	/*�G���W��*/
	XAudio2* engine;
	/*�{�C�X�R�[���o�b�N*/
	std::unique_ptr<VoiceCallback>callback;
	/*�\�[�X�{�C�X*/
	IXAudio2SourceVoice* voice;
	/*�T�E���h�f�[�^*/
	std::array<std::vector<std::uint8_t>, 2>wave;
	int index = 0;
	int read = 0;
};
