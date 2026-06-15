// ===================================================================
// HPComponent.h
// HP管理コンポーネント（Player / Enemy 共通）
// ===================================================================
#pragma once
#include "Component.h"

class HPComponent : public Component
{
private:
    int m_MaxHP = 100;
    int m_CurrentHP = 100;
    bool m_IsDead = false;

    float m_InvincibleTime = 0.0f;     // 残り無敵時間
    float m_InvincibleDuration = 0.5f; // 被弾後の無敵時間（秒）

public:
    HPComponent(int maxHP = 100)
        : m_MaxHP(maxHP)
        , m_CurrentHP(maxHP)
    {}

    void Init() override
    {
        m_CurrentHP = m_MaxHP;
        m_IsDead = false;
        m_InvincibleTime = 0.0f;
    }

    void Update() override;   // ← 追加


    // ダメージを受ける
    void ApplyDamage(int damage);

    // 回復（必要なら）
    void Heal(int value);

    void SetMaxHP(int s_maxHP) { m_MaxHP = s_maxHP; m_CurrentHP = m_MaxHP; }
    
    // 状態取得
    int GetHP() const { return m_CurrentHP; }
    int GetMaxHP() const { return m_MaxHP; }
    bool IsDead() const { return m_IsDead; }
};
