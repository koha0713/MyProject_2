#include "EnemyMoverComponent.h"
#include "GameObject.h"
#include "Transform.h"
#include "AnimationStateComponent.h"
#include "Game.h"

using namespace DirectX::SimpleMath;

void EnemyMoverComponent::SetMoveDirection(const Vector3& dir)
{
    m_MoveDir = dir;
    m_MoveDir.y = 0.0f;

    if (m_MoveDir.LengthSquared() > 0.0001f)
        m_MoveDir.Normalize();
}

void EnemyMoverComponent::Update()
{
    if (!m_pOwner) return;

    Transform& transform = m_pOwner->GetTransform();
    float dt = Game::GetDeltaTime();

    bool isMoving = false;

    // ===============================
    // ノックバック処理（最優先）
    // ===============================
    if (m_KnockbackVelocity.LengthSquared() > 0.0001f)
    {
        transform.Translate(m_KnockbackVelocity * dt);

        m_KnockbackVelocity = Vector3::Lerp(
            m_KnockbackVelocity,
            Vector3::Zero,
            m_KnockbackDecay * dt
        );

        isMoving = true;
    }
    else
    {
        // ===============================
        // 通常移動（AI指示）
        // ===============================
        if (m_MoveDir.LengthSquared() > 0.0001f)
        {
            Vector3 dir = m_MoveDir;
            dir.y = 0.0f;

            if (dir.LengthSquared() > 0.0001f)
            {
                dir.Normalize();
                transform.Translate(dir * m_MoveSpeed * dt);

                // 進行方向を向く
                float angle = atan2f(-dir.x, -dir.z);
                Vector3 rot = transform.GetRotation();
                rot.y = angle;
                transform.SetRotation(rot);

                isMoving = true;
            }
        }
    }

    // アニメ通知
    auto* anim = m_pOwner->GetComponent<AnimationStateComponent>();
    if (anim)
    {
        anim->SetMoving(isMoving);
    }
}

void EnemyMoverComponent::AddKnockback(const Vector3& force)
{
    m_KnockbackVelocity += force;
}

bool EnemyMoverComponent::IsKnockbacking() const
{
    return m_KnockbackVelocity.LengthSquared() > 0.01f;
}
