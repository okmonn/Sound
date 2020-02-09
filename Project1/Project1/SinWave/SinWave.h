#pragma once
#include <vector>

class SinWave {
public:
	/*�T�C���g�̎擾(8�r�b�g)
	return �T�C���g*/
	std::vector<std::uint8_t>Sin8(void);
	/*�T�C���g�̎擾(16�r�b�g)
	return �T�C���g*/
	std::vector<std::int16_t>Sin16(void);
	/*�T�C���g�̐��̎擾
	return �T�C���g�̐�*/
	std::uint32_t GetNum(void) const;
	/*�C���X�^���X�ϐ��̎擾
	return �C���X�^���X�ϐ�*/
	static SinWave& Get(void);

private:
	SinWave(const SinWave&)         = delete;
	SinWave(const SinWave&&)        = delete;
	void operator=(const SinWave&)  = delete;
	void operator=(const SinWave&&) = delete;

private:
	/*�R���X�g���N�^*/
	SinWave();

private:
	/*�T�C���g(8�r�b�g)*/
	std::vector<std::uint8_t>sinWave8;
	/*�T�C���g(16�r�b�g)*/
	std::vector<std::int16_t>sinWave16;
};
