#include "EnemyAttackComponent.h"
#include "GameObject.h"
#include "HPComponent.h"
#include "Game.h"

void EnemyAttackComponent::Update()
{
    m_Timer += Game::GetDeltaTime();
}

void EnemyAttackComponent::TryAttack(GameObject* target)
{
    if (!target) return;
    if (m_Timer < m_AttackInterval) return;

    auto* hp = target->GetComponent<HPComponent>();
    if (!hp) return;

    hp->ApplyDamage(m_Damage);
    m_Timer = 0.0f;
}
