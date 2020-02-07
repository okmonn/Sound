#include "FmSound.h"

/*初期アルゴリズム処理
.Modulatorのポインタ*/
int32_t Default(Modulator* mod);
int32_t Default(Modulator* mod)
{
	return CreateSignalSimple(&mod->op[0]);
}

void FmSound_Constructor(FmSound* fm, const uint32_t sample)
{
	fm->algorithm = &Default;
	Modulator_Constructor(&fm->mod, sample);
}

void ApplyAlgorithmFunction(FmSound* fm, int32_t(*func)(Modulator*))
{
	fm->algorithm = func;
}

void ApplyParameter(FmSound* fm, const Parameter* parameter, const uint32_t num)
{
	Modulator_ApplyParameter(&fm->mod, parameter, num);
}

void Start(FmSound* fm)
{
	Modulator_Start(&fm->mod);
}

void Stop(FmSound* fm)
{
	Modulator_Stop(&fm->mod);
}

void CreateSignal(FmSound* fm, int16_t* buf, const uint32_t num)
{
	int32_t signal = 0;
	for (uint32_t i = 0; i < num; ++i) {
		signal = fm->algorithm(&fm->mod);
		signal >>= 16;
		if (signal > 0x7fff) {
			buf[i] = 0x7fff;
		}
		else if (signal < -0x7fff) {
			buf[i] = -0x7fff;
		}
		else {
			buf[i] = (int16_t)(signal);
		}
	}
}

void SetFreq(FmSound* fm, const uint32_t freq)
{
	Modulator_SetFreq(&fm->mod, freq);
}
