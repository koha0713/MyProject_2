#pragma once
#include <vector>
#include <DirectXMath.h>

class GameObject;

struct WaveData
{
    int enemyCount;
    int enemyHP;
};

class WaveManager
{
public:
    void Init(std::vector<GameObject*>* enemyPool, GameObject* player);

    void AddWave(int enemyCount, int hp);
    void StartNextWave();
    void Update();

    bool IsAllWavesCleared() const;

    void OnEnemyDead();

private:
    std::vector<WaveData> m_Waves;
    int m_CurrentWaveIndex = -1;

    std::vector<GameObject*>* m_EnemyPool = nullptr;
    GameObject* m_Player = nullptr;

    int m_AliveEnemyCount = 0;

private:
    GameObject* GetInactiveEnemy();
};
