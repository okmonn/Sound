#ifndef FM_PARAMETER
#define FM_PARAMETER

typedef struct {
	/*アタック時の最大ゲインの比率*/
	float attack_gain_ratio;
	/*サスティン時の最大ゲインの比率*/
	float sustain_gain_ratio;
	/*アタック時の持続期間の比率*/
	float attack_duration_ratio;
	/*ディケイ時の持続期間の比率*/
	float decay_duration_ratio;
	/*リリース時の持続期間の比率*/
	float release_duration_ratio;
	/*変調周波数の比率*/
	float mod_freq_ratio;
	/*フィードバック用ゲインの比率*/
	float feedback_gain_ratio;
	/*音量調節*/
	float volume_ratio;
} Parameter;

#endif
