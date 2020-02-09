#pragma once
#include "SourceVoice/SourceVoice.h"
#include <list>

struct IXAudio2;
struct IXAudio2MasteringVoice;

class XAudio {
	friend SourceVoice;
public:
	/*�R���X�g���N�^*/
	XAudio();
	/*�f�X�g���N�^*/
	~XAudio();
	
private:
	/*�I�[�f�B�I�̐���*/
	void CreateAudio(void);
	/*�}�X�^�����O�\�[�X�̐���*/
	void CreateMastering(void);
	/*�����o�̏�����*/
	void Initialize(void);
	/*�\�[�X�{�C�X�̃��X�g�ɒǉ�
	.SourceVoice�̃|�C���^*/
	void AddList(SourceVoice* voice);
	/*�\�[�X�{�C�X�̃��X�g����폜
	.SourceVoice�̃|�C���^*/
	void DeleteList(SourceVoice* voice);

	/*�I�[�f�B�I*/
	IXAudio2* audio;
	/*�}�X�^�����O�{�C�X*/
	IXAudio2MasteringVoice* mastering;
	/*�\�[�X�{�C�X���X�g*/
	std::list<SourceVoice*>voice;
};

/*XAudio�̐���
.XAudio*/
long CreateXAudio(XAudio** engine);
/*XAudio�̔j��
.XAudio*/
long Release(XAudio** engine);
