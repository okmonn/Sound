#pragma once
#include <cstdint>

namespace FM {
	struct Feedback {
	public:
		/*�R���X�g���N�^*/
		Feedback();

	public:
		/*�t�B�[�h�o�b�N�p�Q�C���̐ݒ�
		.�Q�C��*/
		void SetGain(const float& gain);
		void SetGain(const std::uint32_t& gain);

	public:
		/*�O��̏o�̓f�[�^*/
		std::int32_t data;
		/*�t�B�[�h�o�b�N�p�Q�C��*/
		std::uint32_t gain;
	};
}
