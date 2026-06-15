#pragma once

// リズム判定結果
enum class RhythmJudge
{
	Perfect,
	Great,
	Good,
	Miss
};

class RhythmManager
{
private:
	// BPM
	float m_BPM = 67.0f;
	
	// 経過時間
	float m_ElapsedTime = 0.0f;

	// 現在の拍
	int   m_CurrentBeat = 0;

	// 拍内の進捗（0.0 ～ 1.0）
	float m_BeatProgress = 0.0f;

	// 判定幅（割合）
	float m_PerfectRange = 0.05f; // ±5%
	float m_GreatRange = 0.10f;
	float m_GoodRange = 0.20f;

	//=======================================
	// 音量揺れ用
	//=======================================

	// 音量の揺れ倍率（1.0が通常）
	float m_VolumePulse = 1.0f;

	// 元に戻る速度
	float m_VolumeReturnSpeed = 6.0f;

	// 簡単モード
	bool easy = false;

public:
	//=======================================
	// ライフサイクル
	//=======================================
	void Init(float bpm);
	void Update();
	void Reset();

	//=======================================
	// 判定取得
	//=======================================
	
	// 今この瞬間の判定結果
	RhythmJudge JudgeTiming() const;

	// 現在の拍情報取得
	float GetBeatProgress() const;	// 0.0f ~ 1.0f
	int GetCurrentBeat() const;

	//=======================================
	// 音の揺れ
	//=======================================
	
	// 判定結果を反映（Perfect等で音量を揺らす）
	void OnJudge(RhythmJudge judge);

	// 現在のBGM音量倍率取得
	float GetVolumePulse() const;


	//=======================================
	// 設定
	//=======================================
	void SetBPM(float bpm);
	float GetBPM() const { return m_BPM; }

	// ===============================
	// Perfect中心検出
	// ===============================
	bool IsPerfectCenter() const;

	bool IsEasyMode() { return easy; };
	void SetEasyMode(bool mode) { easy = mode; };

private:
	//=======================================
	// 内部処理
	//=======================================
	float GetBeatInterval() const;

};

#define RHYTHM_MANAGER Singleton<RhythmManager>::GetInstance()