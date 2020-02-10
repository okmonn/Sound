#pragma once
#include <vector>
#include <cstdint>

class SinWave {
public:
	/*�f�X�g���N�^*/
	~SinWave();
	/*�T�C���g�̎擾
	return �T�C���g*/
	std::vector<std::uint8_t>SinTbl(void);
	/*�C���X�^���X�ϐ��̎擾
	return �C���X�^���X�ϐ�*/
	static SinWave& Get(void);

private:
	/*�R���X�g���N�^*/
	SinWave();
	/*�T�C���g*/
	std::vector<std::uint8_t>sinTbl;
};
