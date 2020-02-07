#pragma once

typedef struct {
	/*アタック時の最大入力レベル比率*/
	float attackLevel;
	/*アタック時の持続サンプル数比率*/
	float attack;
	/*ディケイ時の持続サンプル数比率*/
	float decay;
	/*サスティン時の最大入力レベル比率*/
	float sustainLevel;
	/*リリース時の持続サンプル数比率*/
	float release;
	/*生成周波数比率*/
	float freq_ratio;
	/*入力レベル比率*/
	float gain_ratio;
	/*フィードバック用入力レベル比率*/
	float fb_gain;
}Parameter;

/*コンストラクタ
.Parameterのポインタ*/
void Parameter_Constructor(Parameter* parameter);
