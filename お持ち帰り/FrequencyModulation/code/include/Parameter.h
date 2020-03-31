#ifndef FM_PARAMETER
#define FM_PARAMETER

typedef struct {
	/*�A�^�b�N���̍ő�Q�C���̔䗦*/
	float attack_gain_ratio;
	/*�T�X�e�B�����̍ő�Q�C���̔䗦*/
	float sustain_gain_ratio;
	/*�A�^�b�N���̎������Ԃ̔䗦*/
	float attack_duration_ratio;
	/*�f�B�P�C���̎������Ԃ̔䗦*/
	float decay_duration_ratio;
	/*�����[�X���̎������Ԃ̔䗦*/
	float release_duration_ratio;
	/*�ϒ����g���̔䗦*/
	float mod_freq_ratio;
	/*�t�B�[�h�o�b�N�p�Q�C���̔䗦*/
	float feedback_gain_ratio;
	/*���ʒ���*/
	float volume_ratio;
} Parameter;

#endif
