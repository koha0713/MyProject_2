// ===================================================================
// SceneGame.h
// リザルトシーン - OBJモデル読み込みとカメラ追従
// ===================================================================
#pragma once
#include "SceneBase.h"
#include "Camera.h"

class WaveManager;

class SceneGame : public SceneBase
{
private:
    // オブジェクト管理用ID
    enum OBJECT_ID
    {
        ID_MODEL_OBJECT,    // OBJモデル表示用

        ID_COUNT,
    };

    // プレイヤー移動可能範囲（AABB）
    Vector3 m_PlayerMinBounds; // 最小XYZ
    Vector3 m_PlayerMaxBounds; // 最大XYZ

    std::vector<GameObject*> m_EnemyPool;
    WaveManager* m_WaveManager = nullptr;

    float m_DisplayTime = 0.f;    // 表示時間
    Camera* m_pCamera = nullptr;      // カメラへの参照（Draw()で受け取る）

    void ActivateEnemy(
        GameObject* enemy,
        const DirectX::SimpleMath::Vector3& pos,
        int hp,
        GameObject* target);

    bool IsAllEnemiesDead() const
    {
        for (auto* enemy : m_EnemyPool)
        {
            if (enemy->IsActive())
                return false;
        }
        return true;
    }

    int d_rhythm = 0;
    float d_delta;
    bool d_on = false;

    int cnt_hit;
    bool cn_hit;

    int walk_a;

public:
    void Init() override;
    void UnInit() override;
    void Update() override;
    void Draw() override;
    void Draw(Camera*) override;
};