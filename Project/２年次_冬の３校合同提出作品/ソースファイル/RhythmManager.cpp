#include "RhythmManager.h"
#include "Game.h"
#include <cmath>

// ===============================
// Init
// BPMの設定
// ===============================
void RhythmManager::Init(float bpm)
{
    m_BPM = bpm;
    Reset();
}

// ===============================
// Reset
// リズムデータの初期化
// ===============================
void RhythmManager::Reset()
{
    m_ElapsedTime = 0.0f;
    m_CurrentBeat = 0;
    m_BeatProgress = 0.0f;
}

// ===============================
// Update
// リズムデータの更新
// ===============================
void RhythmManager::Update()
{
    float delta = Game::GetDeltaTime();
    m_ElapsedTime += delta;

    float beatInterval = GetBeatInterval();

    // 何拍進んだか
    float totalBeats = m_ElapsedTime / beatInterval;

    m_CurrentBeat = static_cast<int>(totalBeats);

    // 拍内の進捗（0.0 ～ 1.0）
    m_BeatProgress = totalBeats - m_CurrentBeat;

    	// 音量揺れを元に戻す
	const float base = 1.0f;
	m_VolumePulse += (base - m_VolumePulse)
		* m_VolumeReturnSpeed * delta;

}

// ===============================
// JudgeTiming
// ===============================
RhythmJudge RhythmManager::JudgeTiming() const
{
    // 拍の中心（0.0 or 1.0）
    float dist = (std::min)(
        std::abs(m_BeatProgress - 0.0f),
        std::abs(m_BeatProgress - 1.0f)
    );

    if (dist <= m_PerfectRange)
        return RhythmJudge::Perfect;
    else if (dist <= m_GreatRange)
        return RhythmJudge::Great;
    else if (dist <= m_GoodRange)
        return RhythmJudge::Good;
    else
        return RhythmJudge::Miss;
}

// ===============================
// 情報取得
// ===============================
float RhythmManager::GetBeatProgress() const
{
    return m_BeatProgress;
}

int RhythmManager::GetCurrentBeat() const
{
    return m_CurrentBeat;
}

//=======================================
// 音の揺れ
//=======================================
void RhythmManager::OnJudge(RhythmJudge judge)
{
    switch (judge)
    {
    case RhythmJudge::Perfect:
        m_VolumePulse = 1.4f;
        break;

    case RhythmJudge::Great:
        m_VolumePulse = 1.25f;
        break;

    case RhythmJudge::Good:
        m_VolumePulse = 1.1f;
        break;

    case RhythmJudge::Miss:
    default:
        // Missでは何もしない（下げてもいい）
        break;
    }
}

float RhythmManager::GetVolumePulse() const
{
    return m_VolumePulse;
}


// ===============================
// BPM設定
// ===============================
void RhythmManager::SetBPM(float bpm)
{
    m_BPM = bpm;
}

// ===============================
// 拍間隔
// ===============================
float RhythmManager::GetBeatInterval() const
{
    return 60.0f / m_BPM;
}

// ===============================
// Perfectの真ん中か？
// 拍頭を跨いだ瞬間を検出
// ===============================
bool RhythmManager::IsPerfectCenter() const
{
    float beatInterval = GetBeatInterval();

    // 拍内経過時間
    float t = fmod(m_ElapsedTime, beatInterval);

    // 1フレーム以内なら「今まさに拍頭」
    return t < Game::GetDeltaTime();
}

