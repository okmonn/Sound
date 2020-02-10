#pragma once
#include "../Envelope/Envelope.h"
#include "../Feedback/Feedback.h"

struct FmSound;

struct Operator {
	friend FmSound;
public:
	/*�R���X�g���N�^*/
	Operator();
	/*�M���̐���(���W�����[�V�����Ȃ��A�t�B�[�h�o�b�N�Ȃ�)
	return �M��*/
	std::int32_t CreateSignalSimple(void);
	/*�M���̐���(���W�����[�V�����Ȃ��A�t�B�[�h�o�b�N����)
	return �M��*/
	std::int32_t CreateSignalFB(void);
	/*�M���̐���(���W�����[�V��������A�t�B�[�h�o�b�N�Ȃ�)
	.���W�����[�V�����M��
	return �M��*/
	std::int32_t CreateSignalModulation(const std::int32_t& mod);

private:
	/*�M�������̊J�n*/
	void Start(void);
	/*�M�������̒�~*/
	void Stop(void);
	/*�ǂݏo�����x�̐ݒ�
	.�������g��
	.�T���v�����O���g��*/
	void SetSpeed(const std::uint32_t& freq, const std::uint32_t& sample);
	/*�������g���̐ݒ�
	.�䗦*/
	void SetRatio(const float& ratio);
	void SetRatio(const std::uint32_t& ratio);

private:
	/*�G���x���[�v*/
	Envelope ev;
	/*�t�B�[�h�o�b�N*/
	Feedback fb;
	/*����t���O*/
	std::uint8_t play;
	/*�ǂݏo���ʒu*/
	std::uint32_t pos;
	/*�ǂݏo�����x*/
	std::uint32_t speed;
	/*�������g���䗦*/
	std::uint32_t ratio;
};
