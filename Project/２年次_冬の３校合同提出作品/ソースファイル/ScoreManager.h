//=======================================
// ScoreManager.h
// Scoreの一括管理
//=======================================
#pragma once
#include <unordered_map>
#include "singleton.h"

// 加算・減算のパターンを列挙
enum class ScoreType
{
    EnemyKill,
    Lhythm,
    DamageTaken,
    PlayerDie
};

class ScoreManager
{
private:
    int m_Score = 0;

    // 各ScoreTypeに対応するスコア値
    std::unordered_map<ScoreType, int> m_ScoreValues;

public:
    void Init()
    {
        // スコア値の初期設定（後で調整も容易）
        m_ScoreValues[ScoreType::EnemyKill] = 100;
        m_ScoreValues[ScoreType::Lhythm] = 50;
        m_ScoreValues[ScoreType::DamageTaken] = -50;
        m_ScoreValues[ScoreType::PlayerDie] = -300;

        m_Score = 0;
    }
    void Update() {};
    void UnInit() {};

    void CleanScore() { m_Score = 0; }

    int GetScore() const { return m_Score; }

    // Scoreを増減する
    void ApplyScore(ScoreType type)
    {
        m_Score += m_ScoreValues[type];

        std::cout << "現在のスコア：" << m_Score << "\n";
    }

    // 現在のスコアを各桁に切り分けて返す
    std::vector<int> SpriteScore()
    {
        std::vector<int> digits(5, 0); // 最初から5桁分0で確保

        int score = m_Score; // 元のスコアを壊さない

        for (int i = 4; i >= 0; --i)
        {
            digits[i] = score % 10;
            score /= 10;
        }

        return digits;
    }



};

#define SCORE_MANAGER Singleton<ScoreManager>::GetInstance()