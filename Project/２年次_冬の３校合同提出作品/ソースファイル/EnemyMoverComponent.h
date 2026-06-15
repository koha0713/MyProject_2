// ===================================================================
// EnemyMoverComponent.h
// Enemyの移動処理（AIから指示された方向へ移動）
// ===================================================================
#pragma once
#include "Component.h"
#include <SimpleMath.h>

class AnimationStateComponent;

class EnemyMoverComponent : public Component
{
private:
    DirectX::SimpleMath::Vector3 m_MoveDir = { 0,0,0 };
    float m_MoveSpeed = 5.0f;

    DirectX::SimpleMath::Vector3 m_KnockbackVelocity = { 0,0,0 };
    float m_KnockbackDecay = 3.0f;   // 減衰速度（大きいほど早く止まる）

public:
    EnemyMoverComponent(float speed = 3.0f)
        : m_MoveSpeed(speed)
    {}

    void Update() override;

    // AIから呼ばれる
    void SetMoveDirection(const DirectX::SimpleMath::Vector3& dir);

    void AddKnockback(const DirectX::SimpleMath::Vector3& force);
    bool IsKnockbacking() const;

};
