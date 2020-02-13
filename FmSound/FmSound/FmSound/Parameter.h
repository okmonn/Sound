#pragma once
#include <vector>

namespace FM {
	template <typename T>
	struct Param {
	public:
		/*�R���X�g���N�^*/
		Param() {
			attackLevel  = T(0);
			sustainLevel = T(1);
			attack       = T(0);
			decay        = T(0);
			release      = T(0);
			freq         = T(1);
			gain         = T(1);
			fb_gain      = T(1);
		}
		/*�R���X�g���N�^
		.�A�^�b�N���̍ő�Q�C��
		.�T�X�e�B�����̍ő�Q�C��
		.�A�^�b�N���̎����T���v����
		.�f�B�P�C���̎����T���v����
		.�����[�X���̎����T���v����
		.�������g��
		.�Q�C��
		.�t�B�[�h�o�b�N�p�Q�C��*/
		Param(const T& attackLevel, const T& sustainLevel, const T& attack, const T& decay, const T& release,
			const T& freq, const T& gain, const T& fb_gain) :
			attackLevel(attackLevel), sustainLevel(sustainLevel), attack(attack), decay(decay), release(release),
			freq(freq), gain(gain), fb_gain(fb_gain) {}

	public:
		/*�A�^�b�N���̍ő�Q�C��*/
		T attackLevel;
		/*�T�X�e�B�����̍ő�Q�C��*/
		T sustainLevel;
		/*�A�^�b�N���̎����T���v����*/
		T attack;
		/*�f�B�P�C���̎����T���v����*/
		T decay;
		/*�����[�X���̎����F�T���v����*/
		T release;
		/*�������g��*/
		T freq;
		/*�Q�C��*/
		T gain;
		/*�t�B�[�h�o�b�N�p�Q�C��*/
		T fb_gain;
	};

	template <typename T>
	struct Parameter {
	public:
		/*�R���X�g���N�^
		.Param���X�g*/
		Parameter(const std::initializer_list<Param<T>>& param) {
			this->param.assign(param.begin(), param.end());
		}

	public:
		/*�p�����[�^*/
		std::vector<Param<T>>param;
	};

	using ParamRatio = Parameter<float>;
	using ParamFix   = Parameter<std::uint32_t>;
}
