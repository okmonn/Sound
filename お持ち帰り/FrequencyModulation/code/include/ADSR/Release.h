#ifndef ADSR_RELEASE
#define ADSR_RELEASE

#include <stdint.h>

typedef struct {
	/*持続期間(サンプル数)*/
	uint32_t duration;
} Release;

/*コンストラクタ
.Releaseのポインタ*/
void Release_Constructor(Release* release);
/*持続期間の設定
.Releaseのポインタ
.持続期間(サンプル数)*/
void Release_SetDuration(Release* release, const uint32_t duration);

#endif
