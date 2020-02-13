#pragma once
#include "../Envelope/Envelope.h"
#include "../Feedback/Feedback.h"

namespace FM {
	template <typename T>
	struct FmSound;
}

namespace FM {
	template <typename T>
	struct Operator {
		friend FmSound<T>;
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

	private:
		/*�ǂݏo�����x�̐ݒ�
		.�T���v�����O���g��*/
		void SetSpeed(const std::uint32_t& sample);
		/*�ǂݏo�����x�̐ݒ�
		.�������g��
		.�T���v�����O���g��*/
		void SetSpeed(const std::uint32_t& freq, const std::uint32_t& sample);
		/*�������g���̐ݒ�
		.�������g��*/
		void SetFreq(const float& freq);
		void SetFreq(const std::uint32_t& freq);

	private:
		/*�G���x���[�v*/
		Envelope ev;
		/*�t�B�[�h�o�b�N*/
		Feedback fb;
		/*����t���O*/
		std::uint8_t flag;
		/*�ǂݏo���ʒu*/
		std::uint32_t pos;
		/*�ǂݏo�����x*/
		std::uint32_t speed;
		/*�������g��*/
		std::uint32_t freq;
	};

	using Op_8  = Operator<std::uint8_t>;
	using Op_16 = Operator<std::int16_t>;
}
