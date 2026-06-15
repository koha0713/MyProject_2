// ===================================================================
// EnemyAttackComponent.h
// Enemy ‚Ì‹ßÚUŒ‚ˆ—
// ===================================================================
#pragma once
#include "Component.h"

class GameObject;

class EnemyAttackComponent : public Component
{
private:
    float m_AttackInterval = 3.0f; // UŒ‚ŠÔŠui•bj
    float m_Timer = 0.0f;
    int   m_Damage = 5;

public:
    EnemyAttackComponent(float interval = 3.0f, int damage = 5)
        : m_AttackInterval(interval)
        , m_Damage(damage)
    {}

    void Update() override;

    // AI ‚©‚çŒÄ‚Î‚ê‚é
    void TryAttack(GameObject* target);
};
