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
	/*�R���X�g���N�^
	.�G���W���̃|�C���^
	.�T���v�����O���g��
	.�ʎq���r�b�g��
	.�`�����l����
	.���������_�t���O*/
	SourceVoice(XAudio* engine, const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel, const bool& flag = false);
	/*�f�X�g���N�^*/
	~SourceVoice();
	/*�Đ�
	.�T�E���h�o�b�t�@
	.�o�b�t�@��*/
	void Play(const std::int16_t* buf, const std::uint32_t& num);
	/*�Đ�
	.�T�E���h�o�b�t�@
	.�o�b�t�@��*/
	void Play(const std::uint8_t* buf, const std::uint32_t& num);
	/*��~*/
	void Stop(void);

private:
	/*�t�H�[�}�b�g�̐ݒ�
	.�T���v�����O���g��
	.�ʎq���r�b�g��
	.�`�����l����
	.���������_�t���O
	return �t�H�[�}�b�g�̃|�C���^*/
	void* SetFormat(const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel, const bool& flag);
	/*�\�[�X�{�C�X�̐���
	.�t�H�[�}�b�g�̃|�C���^*/
	void CreateVoice(void* fmt);
	/*�I��*/
	void End(void);

	/*�G���W���̃|�C���g*/
	XAudio* engine;
	/*�{�C�X�R�[���o�b�N*/
	std::unique_ptr<VoiceCallback>callback;
	/*�\�[�X�{�C�X*/
	IXAudio2SourceVoice* voice;
	/*�Đ��t���O*/
	bool flag;
	/*�g�`�f�[�^*/
	std::vector<std::int16_t>wave;
};
