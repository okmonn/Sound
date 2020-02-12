#pragma once
#include <fstream>

struct WaveWriter {
private:
	/*RIFF�`�����N*/
	struct RIFF {
	public:
		/*�R���X�g���N�^*/
		RIFF() : size(0) {
			std::string tmp = "RIFF";
			std::memcpy(id, tmp.data(), sizeof(id));
			tmp = "WAVE";
			std::memcpy(type, tmp.data(), sizeof(type));
		}

	public:
		/*ID(RIFF)*/
		std::uint8_t id[4];
		/*�t�@�C�����v�T�C�Y-8*/
		std::uint32_t size;
		/*�^�C�v(WAVE)*/
		std::uint8_t type[4];
	};
	/*fmt�`�����N*/
	struct FMT {
	public:
		/*�R���X�g���N�^*/
		FMT() : channel(0), sample(0), byte(0), block(0), bit(0) {
			std::string tmp = "fmt ";
			std::memcpy(id, tmp.data(), sizeof(id));
			size = sizeof(FMT) - (sizeof(FMT::id) + sizeof(FMT::size));
			type = 1;
		}

	public:
		/*ID(fmt )*/
		std::uint8_t id[4];
		/*�t�H�[�}�b�g�T�C�Y(16)*/
		std::uint32_t size;
		/*�t�H�[�}�b�g�^�C�v(PCM = 1)*/
		std::uint16_t type;
		/*�`�����l����*/
		std::uint16_t channel;
		/*�T���v�����O���g��*/
		std::uint32_t sample;
		/*Byte/Sec*/
		std::uint32_t byte;
		/*�u���b�N�T�C�Y*/
		std::uint16_t block;
		/*�ʎq���r�b�g��*/
		std::uint16_t bit;
	};
	/*data�`�����N*/
	struct DATA {
	public:
		/*�R���X�g���N�^*/
		DATA() : size(0) {
			std::string tmp = "data";
			std::memcpy(id, tmp.data(), sizeof(id));
		}

	public:
		/*ID(data)*/
		std::uint8_t id[4];
		/*�t�@�C�����v�T�C�Y-126*/
		std::uint32_t size;
	};

public:
	/*�R���X�g���N�^*/
	WaveWriter();
	/*�R���X�g���N�^
	.�������݃t�@�C����
	.�T���v�����O���g��
	.�ʎq���r�b�g��
	.�`�����l����*/
	WaveWriter(const std::string& fileName, const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel);
	/*�t�@�C���I�[�v��
	.�������݃t�@�C����
	.�T���v�����O���g��
	.�ʎq���r�b�g��
	.�`�����l����
	return �����F1�@���s�F0*/
	std::uint8_t Open(const std::string& fileName, const std::uint32_t& sample, const std::uint8_t& bit, const std::uint8_t& channel);
	/*��������
	.�T�E���h�f�[�^�o�b�t�@
	.�o�b�t�@��
	return �������݃o�C�g��*/
	template <typename T>
	std::uint32_t Write(const T* buf, const std::uint32_t& num);
	/*�t�@�C���N���[�Y*/
	void Close(void);

private:
	/*�������݃t�@�C���|�C���^*/
	std::ofstream file;
	/*RIFF�`�����N*/
	RIFF riff;
	/*fmt�`�����N*/
	FMT fmt;
	/*data�`�����N*/
	DATA data;
};
