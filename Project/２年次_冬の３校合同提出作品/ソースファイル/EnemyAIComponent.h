// ===================================================================
// EnemyAIComponent.h
// Enemy‚ÌŠÈˆÕAIi’ÇÕEUŒ‚”»’èj
// ===================================================================
#pragma once
#include "Component.h"
#include <SimpleMath.h>

class EnemyMoverComponent;
class GameObject;

class EnemyAIComponent : public Component
{
private:
    GameObject* m_pTarget = nullptr;

    float m_DetectRange = 30.0f;   // ”­Œ©‹——£
    float m_AttackRange = 5.0f;    // UŒ‚‹——£

public:
    EnemyAIComponent(float detect = 100.0f, float attack = 2.0f)
        : m_DetectRange(detect)
        , m_AttackRange(attack)
    {}

    void Update() override;

    void SetTarget(GameObject* target) { m_pTarget = target; }
};
