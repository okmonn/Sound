#ifndef ADSR_DECAY
#define ADSR_DECAY

#include <stdint.h>

typedef struct {
	/*持続期間(サンプル数)*/
	uint32_t duration;
} Decay;

/*コンストラクタ
.Decayのポインタ*/
void Decay_Constructor(Decay* decay);
/*持続期間の設定
.Decayのポインタ
.持続期間(サンプル数)*/
void Decay_SetDuration(Decay* decay, const uint32_t duration);

#endif
