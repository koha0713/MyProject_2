// ===================================================================
// HitColliderComponent.h
// Ray当たり判定用コライダ（Sphere）
// ===================================================================
#pragma once

#include "Component.h"
#include <SimpleMath.h>

class HitColliderComponent : public Component
{
private:
    float m_Radius = 2.0f;

public:
    HitColliderComponent(float radius = 2.0f)
        : m_Radius(radius) {}

    float GetRadius() const { return m_Radius; }

    DirectX::SimpleMath::Vector3 GetWorldPosition() const
    {
        if (!m_pOwner) return Vector3::Zero;
        return m_pOwner->GetTransform().GetPosition();
    }
};
