#include "ProjectileComponent.h"
#include "GameObject.h"
#include "HitColliderComponent.h"
#include "HPComponent.h"
#include "SceneBase.h"
#include <SceneManager.h>
#include "Game.h"
#include <Enemy.h>
#include "ScoreManager.h"

using namespace DirectX::SimpleMath;

void ProjectileComponent::Fire(const Vector3& dir, int damage)
{
    m_Direction = dir;
    m_Direction.Normalize();
    m_Damage = damage;
    m_Timer = 0.0f;
}

void ProjectileComponent::Update()
{
    if (!m_pOwner || !m_pOwner->IsActive()) return;

    first = FALSE;

    float dt = Game::GetDeltaTime();

    // 前進
    m_pOwner->GetTransform().Translate(m_Direction * m_Speed * dt);

    // 寿命チェック
    m_Timer += dt;
    if (m_Timer >= m_LifeTime)
    {
        m_pOwner->SetActive(false);
        return;
    }

    // 衝突判定
    auto* myCol = m_pOwner->GetComponent<HitColliderComponent>();
    if (!myCol) return;

    SceneBase* scene = SCENE_MANAGER.GetCurrentScene();
    if (!scene) return;

    auto targets = scene->FindGameObjectsWithTag("Enemy"); // Enemyのみ
    for (auto* target : targets)
    {
        if (!target->IsActive()) continue;
        if (target->GetTag() == m_IgnoreTag) continue; // Player などは無視

        auto* col = target->GetComponent<HitColliderComponent>();
        if (!col) continue;

        // 簡易球衝突判定
        Vector3 diff = target->GetTransform().GetPosition() - m_pOwner->GetTransform().GetPosition();
        float dist2 = diff.LengthSquared();
        float radiusSum = 0.5f + 0.5f; // 弾半径 + 相手半径（HitColliderComponentで取得可能）
        if (dist2 <= radiusSum * radiusSum)
        {
            if (auto* enemy = target->GetComponent<Enemy>())
            {
                switch (s_rhythm)
                {
                case RhythmJudge::Perfect:
                    m_Damage = D_Damage * 2 ;
                    SCORE_MANAGER.ApplyScore(ScoreType::Lhythm);
                    break;
                case RhythmJudge::Great:
                    m_Damage = D_Damage * 1.5;
                    break;
                case RhythmJudge::Good:
                    m_Damage = D_Damage * 1;
                    break;
                case RhythmJudge::Miss:
                    m_Damage = D_Damage * 0.5;
                    break;
                }

                first = TRUE;

                enemy->Damage(m_Damage);
                std::cout << "Hit!\n";
            }

            m_pOwner->SetActive(false);
            return;
        }
    }
}
