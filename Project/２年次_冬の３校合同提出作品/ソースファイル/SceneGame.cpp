// ===================================================================
// SceneGame.cpp
// リザルトシーン実装 - カメラ方向に合わせた移動
// ===================================================================
#include "SceneGame.h"
#include "SceneManager.h"
#include "IOManager.h"
#include "ResourceManager.h"
#include "ScoreManager.h"
#include "RhythmManager.h"
#include "Game.h"

// コンポーネント
#include "CameraRelativeMoverComponent.h"      // カメラ相対移動用
#include "MeshRendererComponent.h"

#include "ShooterComponent.h"
#include "HPComponent.h"
#include "HitColliderComponent.h"

#include "Enemy.h"
#include "WaveManager.h"
#include "EnemyMoverComponent.h"
#include "EnemyAIComponent.h"
// リズム
#include "RhythmUIComponent.h"

#include <SimpleCubeRendererComponent.h>

#include <iostream>
#include <memory>
#include <ProjectileComponent.h>
#include <EnemyAttackComponent.h>
#include <SoundManager.h>
#include "GameObject.h"


void SceneGame::Init()
{
    std::cout << "========================================" << std::endl;
    std::cout << "[SceneResult] Init START" << std::endl;


    // Manager関係
    IO_MANAGER.EnableFPSMouse();
    

    // スコア初期化
    SCORE_MANAGER.CleanScore();

    // 既存オブジェクトを削除
    DeleteObjectList();

    walk_a = 0;

    m_PlayerMinBounds = Vector3(-100.0f, -20.0f, -100.0f);
    m_PlayerMaxBounds = Vector3(100.0f, 20.0f, 100.0f);

    // 表示時間初期化
    m_DisplayTime = 0.0f;
    m_pCamera = nullptr; // カメラはDraw()で受け取る

    using namespace DirectX::SimpleMath;

    // オブジェクトリスト作成
    MakeObjectList(SCENE_MANAGER.GetSceneName(SCENE_RESULT).c_str());

    /*
    // ==========================
    // Enemy Pool 作成（安全版）
    // ==========================
    int xx = 7;
    const int ENEMY_POOL_SIZE = 20;

    for (int i = 0; i < ENEMY_POOL_SIZE; i++)
    {
        // アニメーション情報
        std::vector<AnimationData> animations = {
            // AnimationData{ std::string("Run"), std::string("asset/model/Bot_SlowRun.fbx") }
        };

        // オブジェクトデータ作成
        ObjectData enemyData
        {
            xx,
            "Enemy",
            "Model",
            "Enemy",
            "asset/model/Bot.fbx",
            "asset/texture",
            animations,
            {0,0,0}, {0,0,0}, {0.01f,0.01f,0.01f}, {1,1,1,1}
        };

        // GameObject生成
        auto obj = std::make_unique<GameObject>(
            Vector3(enemyData.pos),
            Vector3(enemyData.rot),
            Vector3(enemyData.scl)
        );
        obj->SetID(xx);
        obj->SetName(enemyData.objectName);
        obj->SetTag(enemyData.objectTag);

        // ポインタ確保
        GameObject* objP = obj.get();

        // まず m_GameObjects に所有権を移す
        m_GameObjects.push_back(std::move(obj));

        // Enemy Pool に追加
        m_EnemyPool.push_back(objP);

        // ==========================
        // MeshRendererComponent 作成
        // ==========================
        auto* meshRenderer = objP->AddComponent<MeshRendererComponent>(
            std::string(enemyData.fileName),
            std::string(enemyData.texture)
        );
        if (!meshRenderer)
        {
            std::cerr << "[Enemy Pool] Failed to create MeshRendererComponent" << std::endl;
            continue;
        }

        // ==========================
        // メッシュ読み込み（ResourceManager経由）
        // ==========================
        auto meshHandle = M_RESOURCE.LoadMesh(enemyData.fileName, enemyData.texture);
        if (!meshHandle)
        {
            std::cerr << "[Enemy Pool] Failed to load mesh: " << enemyData.fileName << std::endl;
            // フォールバックCubeにする
            auto* cubeRenderer = objP->AddComponent<SimpleCubeRendererComponent>(Color(1, 1, 0, 1));
            cubeRenderer->SetRenderLayer(RenderLayer::WORLD);
            continue;
        }

        // 安全に ResourceHandle 作成
        meshRenderer->SetMesh(meshHandle.GetShared());

        // ==========================
        // シェーダー読み込み
        // ==========================
        ResourceHandle<Shader> shaderHandle;
        if (!enemyData.animations.empty())
        {
            shaderHandle = M_RESOURCE.LoadShader("shader/litTextureAnimationVS.hlsl", "shader/litTexturePS.hlsl");
        }
        else
        {
            shaderHandle = M_RESOURCE.LoadShader("shader/litTextureVS.hlsl", "shader/litTexturePS.hlsl");
        }

        if (shaderHandle)
        {
            meshRenderer->SetShader(shaderHandle.GetShared());
        }
        else
        {
            std::cerr << "[Enemy Pool] Failed to load shader" << std::endl;
        }

        xx++;
    }
    */

    // リズム関係UIを非表示
    auto ui__a = FindGameObjectWithTag("PERFECT");
    auto ui__b = FindGameObjectWithTag("GREAT");
    auto ui__c = FindGameObjectWithTag("GOOD");
    auto ui__d = FindGameObjectWithTag("MISS");
    ui__a->SetActive(false);
    ui__b->SetActive(false);
    ui__c->SetActive(false);
    ui__d->SetActive(false);

    auto* ui_hit = FindGameObjectWithTag("UI_HIT");
    ui_hit->SetActive(false);
    cnt_hit = 0;
    cn_hit = false;

    // 追加コンポーネント
    {
        // ===== バレット =====
        auto bullets = FindGameObjectsWithTag("Bullet");
        for (auto* bullet : bullets)
        {
            if (!bullet) continue;

            // 必要なComponentを追加
            bullet->GetTransform().SetScale({ 0.1f,0.1f,0.1f });

            // 見えるようにするためのSimpleCubeRenderer
            bullet->AddMeshComponent<SimpleCubeRendererComponent>(DirectX::SimpleMath::Color(0, 0, 1, 1));

            // 弾移動用コンポーネント
            auto* proj = bullet->AddComponent<ProjectileComponent>();
            proj->SetSpeed(30.0f);
            proj->SetLifeTime(2.0f); // 3秒で非アクティブ化
            proj->SetIgnoreTag("Player"); // Player は当たらないように設定

            auto* b_hit = bullet->AddComponent<HitColliderComponent>();

            // Scale設定
            bullet->GetTransform().SetScale(Vector3(0.05f, 0.05f, 0.05f));
        }

        // ===== エネミー =====
        auto enemies = FindGameObjectsWithTag("Enemy");
        for (auto* enemy : enemies)
        {
            if (!enemy) continue;

            // 必要なコンポーネントを追加
            enemy->AddComponent<Enemy>();
            enemy->AddComponent<HPComponent>(100);

            float colliderRadius = 3.0f;
            enemy->AddComponent<HitColliderComponent>(colliderRadius);

            enemy->AddComponent<EnemyMoverComponent>(9.0f);
            enemy->AddComponent<EnemyAIComponent>();
            enemy->AddComponent<EnemyAttackComponent>(1.0f, 10);
            
            enemy->GetTransform().SetScale(Vector3(0.8f,0.8f,0.8f));
            // Enemy Pool に追加

            m_EnemyPool.push_back(enemy);
            enemy->SetActive(FALSE);
        }

        // ===== プレイヤー =====
        {
            // ===================================================================
            // カメラ相対移動コンポーネントを追加
            // ※ カメラはまだnullptrだが、Update()で使用する前にDraw()が呼ばれてセットされる
            // ===================================================================
            // プレイヤー移動コンポーネント
            auto* player = FindGameObjectWithTag("Player")->AddComponent<CameraRelativeMoverComponent>(
                nullptr,    // カメラは後でセット
                8.0f,       // 移動速度
                3.0f        // 回転速度
            );
            player->SetCamera(&m_Camera);
            // shooer
            auto* shooter = FindGameObjectWithTag("Player")->AddComponent<ShooterComponent>(&m_Camera);

            // Hit
            float colliderRadius = 1.0f;
            auto* hit = FindGameObjectWithTag("Player")->AddComponent<HitColliderComponent>(colliderRadius);
            // HP
            auto* hp = FindGameObjectWithTag("Player")->AddComponent<HPComponent>();
        }
        
        // ===== リズム =====
        auto* rhythm_ui = FindGameObjectWithTag("Rhythm")->AddComponent<RhythmUIComponent>();
        
    }

    // ==========================
    // WaveManager 作成
    // ==========================
    m_WaveManager = new WaveManager();
    GameObject* p_player = FindGameObjectWithTag("Player");
    m_WaveManager->Init(&m_EnemyPool, p_player);


    // 仮ウェーブ
    m_WaveManager->AddWave(5, 5);
    m_WaveManager->AddWave(8, 10);
    m_WaveManager->AddWave(12, 15);
    m_WaveManager->AddWave(18, 20);

    m_WaveManager->StartNextWave();

    // アニメーションの初期化
    FindGameObjectWithTag("Player")->GetMeshComponent<MeshRendererComponent>()->ChangeAnimation("Idle");

    // カメラ初期化
    m_Camera.Init();

    m_nextScene = SCENE_NONE;

    // 初期化完了
    m_isInitialized = true;

    std::cout << "[SceneResult] Initialized successfully" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "=== RESULT SCENE ===" << std::endl;
    std::cout << "OBJ Model Display with Camera-Relative Movement" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  W/A/S/D      - Move (Camera-Relative)" << std::endl;
    std::cout << "  Q/E          - Rotate Model" << std::endl;
    std::cout << "  LEFT/RIGHT   - Rotate Camera" << std::endl;
    std::cout << "  UP/DOWN      - Zoom Camera" << std::endl;
    std::cout << "  ENTER        - Back to Title" << std::endl;
    std::cout << "  ESC          - Retry Game" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "NOTE: W moves toward camera direction!" << std::endl;
    std::cout << "" << std::endl;

    SOUND_MANAGER.StopBGM();

    // BGM再生
    SOUND_MANAGER.PlayBGM(SOUND_LABEL::BGM_GAME);

    // BPM設定
    RHYTHM_MANAGER.Init(68.0f);
}

void SceneGame::UnInit()
{
    std::cout << "[SceneResult] UnInit" << std::endl;
    DeleteObjectList();
    m_pCamera = nullptr;

    // カメラ終了処理
    m_Camera.Uninit();

    SOUND_MANAGER.StopBGM();

    m_isInitialized = false;
}

void SceneGame::Update()
{
    // リズム更新
    RHYTHM_MANAGER.Update();

    float volume = RHYTHM_MANAGER.GetVolumePulse();
    SOUND_MANAGER.SetVolumeBGM(volume);

    // リズムUI表示判定
    {
        // UIをあらかじめ取得
        auto ui__a = FindGameObjectWithTag("PERFECT");
        auto ui__b = FindGameObjectWithTag("GREAT");
        auto ui__c = FindGameObjectWithTag("GOOD");
        auto ui__d = FindGameObjectWithTag("MISS");

        // 全てのBulletをチェック
        auto bullets = FindGameObjectsWithTag("Bullet");
        bool ts = true;
        for (auto* bullet : bullets )
        {
            if (!bullet) continue;

            ui__a->SetActive(false);
            ui__b->SetActive(false);
            ui__c->SetActive(false);
            ui__d->SetActive(false);

            auto* pro = bullet->GetComponent<ProjectileComponent>();
            if (pro->Getfirst() == TRUE)
            {
                // 判定に合わせてアクティブ化
                switch (pro->Getjudge()) {
                case RhythmJudge::Perfect:
                    d_rhythm = 0;
                    ui__a->SetActive(true);
                    break;
                case RhythmJudge::Great:
                    d_rhythm = 1;
                    ui__b->SetActive(true);
                    break;
                case RhythmJudge::Good:
                    d_rhythm = 2;
                    ui__c->SetActive(true);
                    break;
                case RhythmJudge::Miss:
                    d_rhythm = 3;
                    ui__d->SetActive(true);
                    break;
                }

                // Hit表示
                if (cn_hit == false) {
                    auto* hit = FindGameObjectWithTag("UI_HIT");
                    hit->SetActive(TRUE);
                }
                cnt_hit = 0;
                cn_hit = true;

                // 表示時間関係初期化
                d_delta = Game::GetDeltaTime();
                d_on = true;

                ts = false;
            }

            if (ts == false) { break; }
        }

        // 表示時間チェック
        if (d_on == true && 3.00f <= Game::GetDeltaTime()-d_delta) {
            d_on = false;
            ui__a->SetActive(false);
            ui__b->SetActive(false);
            ui__c->SetActive(false);
            ui__d->SetActive(false);
        }
    }

    if (cn_hit == true && cnt_hit >= 5)
    {
        // Hit表示
        auto* hit = FindGameObjectWithTag("UI_HIT");
        hit->SetActive(0);
        cn_hit = false;
        cnt_hit = 0;
    }

    cnt_hit += 1;


    // 表示時間更新
    m_DisplayTime += Game::GetDeltaTime();

    if (m_WaveManager)
    {
        m_WaveManager->Update();
        if (m_WaveManager->IsAllWavesCleared())
        {
            SCENE_MANAGER.ChangeSceneWithLoading(SCENE_RESULT);
            return;
        }
    }

    // 残弾数表示
    {
        // UI_BULLET取得
        auto* ui_bullt_1 = FindGameObjectWithTag("UI_BULLET_1");
        auto* ui_bullt_2 = FindGameObjectWithTag("UI_BULLET_2");
        auto* ui_bullt_3 = FindGameObjectWithTag("UI_BULLET_3");
        auto* ui_bullt_4 = FindGameObjectWithTag("UI_BULLET_4");
        auto* ui_bullt_5 = FindGameObjectWithTag("UI_BULLET_5");
        auto* ui_bullt_6 = FindGameObjectWithTag("UI_BULLET_6");

        // Shooter取得
        auto* shooter = FindGameObjectWithTag("Player")->GetComponent<ShooterComponent>();

        ui_bullt_1->SetActive(FALSE);
        ui_bullt_2->SetActive(FALSE);
        ui_bullt_3->SetActive(FALSE);
        ui_bullt_4->SetActive(FALSE);
        ui_bullt_5->SetActive(FALSE);
        ui_bullt_6->SetActive(FALSE);

        switch (shooter->GetAmmo()) {
        case 1:
            ui_bullt_6->SetActive(TRUE);
            break;
        case 2:
            ui_bullt_5->SetActive(TRUE);
            ui_bullt_6->SetActive(TRUE);
            break;
        case 3:
            ui_bullt_4->SetActive(TRUE);
            ui_bullt_5->SetActive(TRUE);
            ui_bullt_6->SetActive(TRUE);
            break;
        case 4:
            ui_bullt_3->SetActive(TRUE);
            ui_bullt_4->SetActive(TRUE);
            ui_bullt_5->SetActive(TRUE);
            ui_bullt_6->SetActive(TRUE);
            break;
        case 5:
            ui_bullt_2->SetActive(TRUE);
            ui_bullt_3->SetActive(TRUE);
            ui_bullt_4->SetActive(TRUE);
            ui_bullt_5->SetActive(TRUE);
            ui_bullt_6->SetActive(TRUE);
            break;
        case 6:
            ui_bullt_1->SetActive(TRUE);
            ui_bullt_2->SetActive(TRUE);
            ui_bullt_3->SetActive(TRUE);
            ui_bullt_4->SetActive(TRUE);
            ui_bullt_5->SetActive(TRUE);
            ui_bullt_6->SetActive(TRUE);
            break;
        }


    }

    // カメラ更新
    m_Camera.Update();

    // ===================================================================
    // CameraRelativeMoverComponentにカメラをセット
    // ===================================================================
    if (m_pCamera)
    {
        auto* modelObject = FindGameObjectWithTag("ModelObject");
        if (modelObject)
        {
            auto* mover = modelObject->GetComponent<CameraRelativeMoverComponent>();
            if (mover)
            {
                mover->SetCamera(m_pCamera);
            }
        }
    }

    // ===================================================================
    // アニメーション変更
    // ===================================================================
    auto* mesh = FindGameObjectWithTag("Player")->GetMeshComponent<MeshRendererComponent>();
    
    if (IO_MANAGER.GetKeyDownKeyBord(VK_W) ||
        IO_MANAGER.GetKeyDownKeyBord(VK_S) ||
        IO_MANAGER.GetKeyDownKeyBord(VK_A) ||
        IO_MANAGER.GetKeyDownKeyBord(VK_D))
    {
        mesh->ChangeAnimation("Run");
    }
    if (IO_MANAGER.GetKeyPressKeyBord(VK_W) ||
        IO_MANAGER.GetKeyPressKeyBord(VK_S) ||
        IO_MANAGER.GetKeyPressKeyBord(VK_A) ||
        IO_MANAGER.GetKeyPressKeyBord(VK_D))
    {
        walk_a++;
        SOUND_MANAGER.SetVolumeSE(0.6f);
        if (walk_a % 10 == 1&& IO_MANAGER.GetKeyPressKeyBord(VK_SHIFT)) {
                SOUND_MANAGER.PlaySE(SOUND_LABEL::SE_RUN);
        }
        else if (walk_a % 20 == 1) {
            SOUND_MANAGER.PlaySE(SOUND_LABEL::SE_WALK);
        }
        SOUND_MANAGER.SetVolumeSE(1.0f);
    }
    if (IO_MANAGER.GetKeyUpKeyBord(VK_W) ||
        IO_MANAGER.GetKeyUpKeyBord(VK_S) ||
        IO_MANAGER.GetKeyUpKeyBord(VK_A) ||
        IO_MANAGER.GetKeyUpKeyBord(VK_D))
    {
        // キーが押されていないか
        if (!IO_MANAGER.GetKeyPressKeyBord(VK_W) &&
            !IO_MANAGER.GetKeyPressKeyBord(VK_S) &&
            !IO_MANAGER.GetKeyPressKeyBord(VK_A) &&
            !IO_MANAGER.GetKeyPressKeyBord(VK_D))
        {
            mesh->ChangeAnimation("Idle");
        }
    }

    // 簡単モード
    if (IO_MANAGER.GetKeyDownKeyBord(VK_Q))
    {
        switch (RHYTHM_MANAGER.IsEasyMode())
        {
        case true:
            RHYTHM_MANAGER.SetEasyMode(false);
            break;
        case false:
            RHYTHM_MANAGER.SetEasyMode(true);
            break;
        }
    }


    // GameObjectリストを更新（カメラ相対移動など）
    UpdateObjectList();

    // ==========================
    // Player 死亡チェック
    // ==========================
    auto* player = FindGameObjectWithTag("Player");
    if (player)
    {
        auto* hp = player->GetComponent<HPComponent>();
        if (hp && hp->IsDead())
        {
            // GameOver → Result へ
            SCENE_MANAGER.ChangeSceneWithLoading(SCENE_RESULT);
            return;
        }
    }

    // ==========================
    // Player 範囲チェック
    // ==========================
    if (player)
    {
        Vector3 posi = player->GetTransform().GetPosition();

        bool outOfBounds = false;

        // X方向
        if (posi.x < m_PlayerMinBounds.x) { posi.x = m_PlayerMinBounds.x; outOfBounds = true; }
        if (posi.x > m_PlayerMaxBounds.x) { posi.x = m_PlayerMaxBounds.x; outOfBounds = true; }

        // Z方向
        if (posi.z < m_PlayerMinBounds.z) { posi.z = m_PlayerMinBounds.z; outOfBounds = true; }
        if (posi.z > m_PlayerMaxBounds.z) { posi.z = m_PlayerMaxBounds.z; outOfBounds = true; }

        if (outOfBounds)
        {
            player->GetTransform().SetPosition(posi);
            // 必要なら効果音やエフェクトも追加
        }
    }

    // HPバー動かすシステム
    auto* HP_bar = FindGameObjectWithTag("UI_HP_3");
    auto* now_Hp = player->GetComponent<HPComponent>();

    float ratio = static_cast<float>(now_Hp->GetHP()) /
        static_cast<float>(now_Hp->GetMaxHP());

    float minX = -500.0f;        // HP 0%
    float maxX = -150.0f;        // HP 100%
    float x = minX + (maxX - minX) * ratio;

    Vector3 pos = HP_bar->GetTransform().GetPosition();
    pos.x = x;
    HP_bar->GetTransform().SetPosition(pos);
    
}

void SceneGame::Draw()
{
    // World
    Draw(&m_Camera);

    // UI描画前に深度を無効化
    Renderer::SetDepthEnable(false);

    DrawLayer(&m_Camera, RenderLayer::UI);

    // 念のため戻す
    Renderer::SetDepthEnable(true);
}

void SceneGame::Draw(Camera* camera)
{
    // カメラを保存（Update()で使用）
    m_pCamera = camera;

    // ===================================================================
    // カメラ制御処理
    // ===================================================================
    if (camera)
    {
        auto* player = FindGameObjectWithTag("Player");
        if (!player) return;

        using namespace DirectX::SimpleMath;

        // プレイヤー位置（頭の高さ）
        Vector3 playerPos = player->GetTransform().GetPosition();
        float cameraHeight = 1.8f;
        Vector3 cameraPos = playerPos + Vector3(0, cameraHeight, 0);

        // マウス移動量取得
        Vector2 mouseDelta = IO_MANAGER.GetMouseDelta();

        static float yaw = 0.0f;
        static float pitch = 0.0f;
        float sensitivity = 0.002f;

        yaw += mouseDelta.x * sensitivity;
        pitch += -mouseDelta.y * sensitivity; // 上下反転は好みに応じて

        // 垂直角度制限
        if (pitch > 1.5f) pitch = 1.5f;
        if (pitch < -1.5f) pitch = -1.5f;

        // 前方向ベクトル計算
        Vector3 forward;
        forward.x = cos(pitch) * sin(yaw);
        forward.y = sin(pitch);
        forward.z = cos(pitch) * cos(yaw);
        forward.Normalize();

        // カメラセット
        camera->SetPosition(cameraPos);
        camera->SetTarget(cameraPos + forward);

        // Player モデルは横回転だけ yaw に追従
        auto* playerMover = player->GetComponent<CameraRelativeMoverComponent>();
        if (playerMover)
        {
            playerMover->SetYaw(yaw);
        }
    }

    // WORLD層を描画（カメラ使用）
    DrawLayer(camera, RenderLayer::WORLD);
}

void SceneGame::ActivateEnemy(
    GameObject* enemy,
    const DirectX::SimpleMath::Vector3& pos,
    int hp,
    GameObject* target)
{
    enemy->SetActive(true);
    enemy->GetTransform().SetPosition(pos);

    // HP 初期化
    auto* hpComp = enemy->GetComponent<HPComponent>();
    hpComp->Init();

    // AI にターゲットをセット
    auto* ai = enemy->GetComponent<EnemyAIComponent>();
    ai->SetTarget(target);
}
