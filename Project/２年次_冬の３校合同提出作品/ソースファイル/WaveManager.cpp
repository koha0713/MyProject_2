#include "WaveManager.h"
#include "GameObject.h"
#include "HPComponent.h"
#include "EnemyAIComponent.h"

#include <SimpleMath.h>
#include <cassert>
#include <Enemy.h>

using namespace DirectX::SimpleMath;

void WaveManager::Init(std::vector<GameObject*>* enemyPool, GameObject* player)
{
    m_EnemyPool = enemyPool;
    m_Player = player;
}

void WaveManager::AddWave(int enemyCount, int hp)
{
    m_Waves.push_back({ enemyCount, hp });
}

void WaveManager::StartNextWave()
{
    // 次のウェーブへ
    m_CurrentWaveIndex++;

    // 全ウェーブ終了チェック
    if (m_CurrentWaveIndex >= (int)m_Waves.size())
        return;

    const WaveData& wave = m_Waves[m_CurrentWaveIndex];

    // このウェーブで生存している敵数
    m_AliveEnemyCount = wave.enemyCount;

    for (int i = 0; i < wave.enemyCount; i++)
    {
        // 非アクティブな Enemy をプールから取得
        GameObject* enemyObj = GetInactiveEnemy();
        if (!enemyObj)
            break;

        float min_xz = -95.0f;
        float max_xz = 95.0f;

        // 出現位置（仮）
        Vector3 spawnPos(
            min_xz + (float)(rand()) / RAND_MAX * (max_xz - min_xz),
            (float)(rand() % 3),
            min_xz + (float)(rand()) / RAND_MAX * (max_xz - min_xz)
        );

        // ============================
        // Enemy コンポーネント取得
        // ============================
        auto* enemy = enemyObj->GetComponent<Enemy>();
        assert(enemy && "Enemy component missing!");

        // ============================
        // WaveManager を Enemy に教える
        // ============================
        enemy->Spawn(spawnPos, wave.enemyHP, this);

        // ============================
        // AI 設定
        // ============================
        if (auto* ai = enemyObj->GetComponent<EnemyAIComponent>())
        {
            ai->SetTarget(m_Player);
        }
    }
}


void WaveManager::Update()
{
    if (m_AliveEnemyCount > 0)
        return;

    // 次のウェーブへ
    StartNextWave();
}

bool WaveManager::IsAllWavesCleared() const
{
    return m_CurrentWaveIndex >= (int)m_Waves.size();
}

void WaveManager::OnEnemyDead()
{
    m_AliveEnemyCount--;
}

GameObject* WaveManager::GetInactiveEnemy()
{
    for (auto* enemy : *m_EnemyPool)
    {
        if (!enemy->IsActive())
            return enemy;
    }
    return nullptr;
}
