// ===================================================================
// AnimationStateComponent.h
// 移動状態に応じてアニメーションを切り替える
// ===================================================================
#pragma once
#include "Component.h"
#include <string>

class MeshRendererComponent;

class AnimationStateComponent : public Component
{
private:
    bool m_IsMoving = false;

    std::string m_IdleAnim = "Idle";
    std::string m_RunAnim = "Run";

public:
    AnimationStateComponent(
        const std::string& idle = "Idle",
        const std::string& run = "Run")
        : m_IdleAnim(idle)
        , m_RunAnim(run)
    {}

    void Update() override;

    void SetMoving(bool moving) { m_IsMoving = moving; }
};
