#include "BulletLifeComponent.h"
#include "Game.h"
#include "GameObject.h"

void BulletLifeComponent::Update()
{
    if (!m_pOwner) return;

    m_Elapsed += Game::GetDeltaTime();

    if (m_Elapsed >= m_LifeTime)
    {
        // FW方針：非アクティブ化
        m_pOwner->SetActive(false);
    }
}
