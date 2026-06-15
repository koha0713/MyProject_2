#include "Enemy.h"
#include "GameObject.h"
#include "HPComponent.h"
#include "WaveManager.h"
#include "HitColliderComponent.h"
#include <SceneManager.h>
#include "ScoreManager.h"
#include <MeshRendererComponent.h>

void Enemy::Init()
{
    // 最初は非アクティブ前提
    m_HP = 0;
    m_MaxHP = 0;
}

void Enemy::Update()
{
    if (!GetOwner()->IsActive()) return;

    // 死亡処理（既に実装済み）
    if (m_HP <= 0 && !m_IsDeadNotified)
    {
        m_IsDeadNotified = true;

        SCORE_MANAGER.ApplyScore(ScoreType::EnemyKill);

        if (m_pWaveManager)
            m_pWaveManager->OnEnemyDead();

        GetOwner()->SetActive(false);
        return;
    }

    // ===== Playerとの衝突 =====
    auto* myCol = GetOwner()->GetComponent<HitColliderComponent>();
    if (!myCol) return;

    SceneBase* scene = SCENE_MANAGER.GetCurrentScene();
    if (!scene) return;

    auto players = scene->FindGameObjectsWithTag("Player");
    for (auto* player : players)
    {
        if (!player->IsActive()) continue;

        auto* playerCol = player->GetComponent<HitColliderComponent>();
        if (!playerCol) continue;

        Vector3 diff =
            player->GetTransform().GetPosition() -
            GetOwner()->GetTransform().GetPosition();

        float dist2 = diff.LengthSquared();
        float r = myCol->GetRadius() + playerCol->GetRadius();

        if (dist2 <= r * r)
        {
            if (auto* hp = player->GetComponent<HPComponent>())
            {
                hp->ApplyDamage(10); // 仮ダメージ
            }
        }
    }
}

void Enemy::Spawn(const DirectX::SimpleMath::Vector3& pos, int hp, WaveManager* wm)
{
    m_MaxHP = hp;
    m_HP = hp;
    m_pWaveManager = wm;
    m_IsDeadNotified = false;

    GetOwner()->GetTransform().SetPosition(pos);
    GetOwner()->SetActive(true);
}

void Enemy::Damage(int damage)
{
    m_HP -= damage;
    
}
