#include "EnemyAIComponent.h"
#include "GameObject.h"
#include "EnemyMoverComponent.h"
#include "Transform.h"
#include <EnemyAttackComponent.h>
#include <HitColliderComponent.h>

using namespace DirectX::SimpleMath;

void EnemyAIComponent::Update()
{
    if (!m_pOwner || !m_pTarget) return;

    Transform& myTf = m_pOwner->GetTransform();
    Transform& targetTf = m_pTarget->GetTransform();

    Vector3 toTarget = targetTf.GetPosition() - myTf.GetPosition();
    float distance = toTarget.Length();

    auto* mover = m_pOwner->GetComponent<EnemyMoverComponent>();
    if (!mover) return;

    // ★ ノックバック中はAI停止
    if (mover->IsKnockbacking())
    {
        mover->SetMoveDirection(Vector3::Zero);
        return;
    }

    // ===============================
    // コライダー半径取得
    // ===============================
    float myRadius = 0.0f;
    float targetRadius = 0.0f;

    if (auto* myCol = m_pOwner->GetComponent<HitColliderComponent>())
        myRadius = myCol->GetRadius();

    if (auto* targetCol = m_pTarget->GetComponent<HitColliderComponent>())
        targetRadius = targetCol->GetRadius();

    float hitDistance = myRadius + targetRadius;

    // ===============================
    // Idle（未発見）
    // ===============================
    if (distance > m_DetectRange)
    {
        mover->SetMoveDirection(Vector3::Zero);
        return;
    }

    // ===============================
    // Chase（追跡）
    // ===============================
    if (distance > hitDistance)
    {
        mover->SetMoveDirection(toTarget);
        return;
    }

    // ===============================
    // Attack（攻撃範囲）
    // ===============================
    mover->SetMoveDirection(Vector3::Zero);

    auto* attack = m_pOwner->GetComponent<EnemyAttackComponent>();
    if (attack)
    {
        attack->TryAttack(m_pTarget);
    }
}
