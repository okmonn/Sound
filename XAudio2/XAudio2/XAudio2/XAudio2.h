#pragma once
#include "Voice/Voice.h"
#include <cstdint>
#include <unordered_map>

struct IXAudio2;
struct IXAudio2MasteringVoice;

class XAudio2 {
	friend Voice;
public:
	/*�R���X�g���N�^*/
	XAudio2();
	/*�f�X�g���N�^*/
	~XAudio2();

private:
	/*�I�[�f�B�I�̐���*/
	void CreateAudio(void);
	/*�}�X�^�����O�{�C�X�̐���*/
	void CreateMastering(void);

private:
	/*�I�[�f�B�I*/
	IXAudio2* audio;
	/*�}�X�^�����O�{�C�X*/
	IXAudio2MasteringVoice* mastering;
	/*�{�C�X���X�g*/
	std::unordered_map<std::uint32_t, Voice*>voice;
};

/*XAudio2�̐���
.XAudio2�̃|�C���^�̃|�C���^
return �����F1�@���s�F0*/
std::uint8_t CreateXAudio2(XAudio2** engine);
/*XAudio2�̔j��
.XAudio2�̃|�C���^�̃|�C���^*/
void DeleteXAudio2(XAudio2** engine);


