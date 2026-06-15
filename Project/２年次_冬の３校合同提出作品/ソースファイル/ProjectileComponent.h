#pragma once
#include "Component.h"
#include <SimpleMath.h>
#include <string>
#include "RhythmManager.h"

class ProjectileComponent : public Component
{
private:
    DirectX::SimpleMath::Vector3 m_Direction = DirectX::SimpleMath::Vector3::Zero;
    float m_Speed = 30.0f;
    float m_LifeTime = 3.0f;
    float m_Timer = 0.0f;
    int m_Damage = 0;
    int D_Damage = 10;  // 基本ダメージ
    std::string m_IgnoreTag;

    RhythmJudge s_rhythm;

    // リズムUI表示用
    bool first = FALSE; // UI表示指示用

public:
    void Fire(const DirectX::SimpleMath::Vector3& dir, int damage);
    void Update() override;

    void SetSpeed(float speed) { m_Speed = speed; }
    void SetLifeTime(float t) { m_LifeTime = t; }
    void SetIgnoreTag(const std::string& tag) { m_IgnoreTag = tag; }

    void SetRhythm(RhythmJudge change)
    {
        s_rhythm = change;
    }

    RhythmJudge Getjudge() { return s_rhythm; };
    bool Getfirst() { return first; };

};
