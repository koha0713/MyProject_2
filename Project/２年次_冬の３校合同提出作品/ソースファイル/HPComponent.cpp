#include "HPComponent.h"
#include "GameObject.h"
#include <Game.h>
#include "ScoreManager.h"
#include <SoundManager.h>

void HPComponent::Update()
{
    if (m_InvincibleTime > 0.0f)
    {
        m_InvincibleTime -= Game::GetDeltaTime();
        if (m_InvincibleTime < 0.0f)
            m_InvincibleTime = 0.0f;
    }
}

void HPComponent::ApplyDamage(int damage)
{
    if (m_IsDead) return;
    if (damage <= 0) return;

    // =========================
    // 無敵時間チェック
    // =========================
    if (m_InvincibleTime > 0.0f)
        return;

    SCORE_MANAGER.ApplyScore(ScoreType::DamageTaken);
    SOUND_MANAGER.PlaySE(SOUND_LABEL::SE_DAMAGE);

    std::cout << "damage!";
    m_CurrentHP -= damage;

    // 無敵時間開始
    m_InvincibleTime = m_InvincibleDuration;

    if (m_CurrentHP <= 0)
    {
        m_CurrentHP = 0;
        m_IsDead = true;
        std::cout << "die!";
        // ★ ここでは「死んだ」ことだけ決める
        // 表示・演出・シーン遷移は他が担当
    }
}

void HPComponent::Heal(int value)
{
    if (m_IsDead) return;
    if (value <= 0) return;

    m_CurrentHP += value;
    if (m_CurrentHP > m_MaxHP)
    {
        m_CurrentHP = m_MaxHP;
    }
}
