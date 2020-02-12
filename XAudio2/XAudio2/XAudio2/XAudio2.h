#pragma once
#include "Voice/Voice.h"
#include <unordered_map>

struct IXAudio2;
struct IXAudio2MasteringVoice;

class XAudio2 {
	friend Voice<std::uint8_t>;
	friend Voice<std::int16_t>;
public:
	/*�R���X�g���N�^*/
	XAudio2();
	/*�f�X�g���N�^*/
	~XAudio2();
	/*Voice�N���X�̐���
	.Voice�̃|�C���^�̃|�C���^
	.�T���v�����O���g��
	.�ʎq���r�b�g��
	.�`�����l����
	.���������_�t���O
	return �����F1�@���s�F0*/
	template <typename T>
	std::uint8_t CreateVoice(Voice<T>** obj, const std::uint32_t& sample, const std::uint8_t& channel, const std::uint8_t& flag = 0);

private:
	/*�I�[�f�B�I�̐���*/
	void CreateAudio(void);
	/*�}�X�^�����O�{�C�X�̐���*/
	void CreateMastering(void);
	/*�\�[�X�{�C�X�ێ��N���X�̃|�C���^���X�g�ɒǉ�
	.�\�[�X�{�C�X�ێ��N���X�̃|�C���^
	return �����F1�@���s�F0*/
	std::uint8_t AddList(void* obj);
	/*�\�[�X�{�C�X�ێ��N���X�̃|�C���^���X�g����폜
	.�\�[�X�{�C�X�ێ��N���X�̃|�C���^
	return �����F1�@���s�F0*/
	std::uint8_t DeleteList(void* obj);

private:
	/*�I�[�f�B�I*/
	IXAudio2* audio;
	/*�}�X�^�����O�{�C�X*/
	IXAudio2MasteringVoice* mastering;
	/*�\�[�X�{�C�X�ێ��N���X�̃|�C���^���X�g*/
	std::unordered_map<std::uint32_t, void*>list;
};

/*XAudio2�̐���
.XAudio2�̃|�C���^�̃|�C���^
return �����F1�@���s�F0*/
std::uint8_t CreateXAudio2(XAudio2** obj);
/*XAudio2�̔j��
.XAudio2�̃|�C���^�̃|�C���^*/
void DeleteXAudio2(XAudio2** obj);
