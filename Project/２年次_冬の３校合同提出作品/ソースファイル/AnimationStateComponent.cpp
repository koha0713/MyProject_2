#include "AnimationStateComponent.h"
#include "MeshRendererComponent.h"
#include "GameObject.h"

void AnimationStateComponent::Update()
{
    if (!m_pOwner) return;

    auto* mesh = m_pOwner->GetMeshComponent<MeshRendererComponent>();
    if (!mesh) return;

    if (m_IsMoving)
    {
        mesh->ChangeAnimation(m_RunAnim);
    }
    else
    {
        mesh->ChangeAnimation(m_IdleAnim);
    }
}
