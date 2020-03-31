#ifndef ADSR_RELEASE
#define ADSR_RELEASE

#include <stdint.h>

typedef struct {
	/*��������(�T���v����)*/
	uint32_t duration;
} Release;

/*�R���X�g���N�^
.Release�̃|�C���^*/
void Release_Constructor(Release* release);
/*�������Ԃ̐ݒ�
.Release�̃|�C���^
.��������(�T���v����)*/
void Release_SetDuration(Release* release, const uint32_t duration);

#endif
