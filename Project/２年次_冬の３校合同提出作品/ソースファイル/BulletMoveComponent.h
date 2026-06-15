#pragma once
#include <SystemCommon.h>
#include "Component.h"
#include "GameObject.h"

class BulletMoveComponent : public Component
{
    Vector3 m_Velocity;
    float m_Life = 2.0f;

public:
    BulletMoveComponent(const Vector3& dir, float speed)
        : m_Velocity(dir* speed) {}

    void Update() override
    {
        auto& t = m_pOwner->GetTransform();
        t.SetPosition(t.GetPosition() + m_Velocity);

        m_Life -= 0.1f;
        if (m_Life <= 0.0f)
        {
            m_pOwner->SetActive(false);
        }
    }
};
