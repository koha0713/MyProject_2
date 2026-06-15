#pragma once
#include "Component.h"

class BulletLifeComponent : public Component
{
private:
    float m_LifeTime = 0.0f;
    float m_Elapsed = 0.0f;

public:
    BulletLifeComponent(float lifeTime)
        : m_LifeTime(lifeTime) {}

    void Update() override;
};
