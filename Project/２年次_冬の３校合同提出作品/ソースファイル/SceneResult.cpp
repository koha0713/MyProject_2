// ===================================================================
// SceneResult.cpp
// ゲームシーン実装
// ===================================================================
#include "SceneGame.h"
#include "SceneManager.h"
#include "IOManager.h"
#include "Game.h"

// コンポーネント
#include "PlayerMoverComponent.h"

#include "ShooterComponent.h"
#include "HPComponent.h"
#include "HitColliderComponent.h"
#include "CameraRelativeMoverComponent.h"

#include <iostream>
#include <SoundManager.h>
#include <ScoreManager.h>

void SceneResult::Init()
{
    std::cout << "========================================" << std::endl;
    std::cout << "[SceneGame] Init START" << std::endl;

    IO_MANAGER.DisableFPSMouse();

    // 既存オブジェクトを削除
    DeleteObjectList();

    // ゲーム時間初期化
    m_GameTime = 0.0f;

    using namespace DirectX::SimpleMath;

    // オブジェクトリスト作成
    MakeObjectList(SCENE_MANAGER.GetSceneName(SCENE_GAME).c_str());

    // 追加コンポーネント
    {

    }

    // スコア表示アクティブ処理
    {
        // [桁][数字]
        GameObject* scoreUI[5][10];

        for (int d = 0; d < 5; ++d)
        {
            for (int n = 0; n < 10; ++n)
            {
                std::string tag = "UI_" + std::to_string(d) + "_" + std::to_string(n);
                scoreUI[d][n] = FindGameObjectWithTag(tag.c_str());
            }
        }
        std::vector<int> digits = SCORE_MANAGER.SpriteScore();

        for (int d = 0; d < 5; ++d)
        {
            // まず全部OFF
            for (int n = 0; n < 10; ++n)
            {
                scoreUI[d][n]->SetActive(FALSE);
            }

            // 表示する数字だけON
            int num = digits[d];
            scoreUI[d][num]->SetActive(TRUE);
        }

    }

    // カメラ初期化
    m_Camera.Init();

    m_nextScene = SCENE_NONE;

    SOUND_MANAGER.PlayBGM(SOUND_LABEL::BGM_RESULT);

    // 初期化完了
    m_isInitialized = true;

    std::cout << "[SceneGame] Initialized successfully" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "=== GAME SCENE ===" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  W/A/S/D - Move Player" << std::endl;
    std::cout << "  Q/E     - Rotate Player" << std::endl;
    std::cout << "  ENTER   - Go to Result" << std::endl;
    std::cout << "  ESC     - Back to Title" << std::endl;
    std::cout << "" << std::endl;
}

void SceneResult::UnInit()
{
    std::cout << "[SceneGame] UnInit" << std::endl;
    DeleteObjectList();

    // カメラ終了処理
    m_Camera.Uninit();

    SOUND_MANAGER.StopBGM();

    m_isInitialized = false;
}

void SceneResult::Update()
{
    // ゲーム時間更新
    m_GameTime += Game::GetDeltaTime();

    // カメラ更新
    m_Camera.Update();

    // W/Sキーで選択変更
    if (IO_MANAGER.GetKeyDownKeyBord(VK_W)) {
        SOUND_MANAGER.PlaySE(SOUND_LABEL::SE_SAMPLE000);
        m_selectedIndex--;
        if (m_selectedIndex < 0) m_selectedIndex = m_buttonCount - 1; // 上端に行ったら下端へループ
    }
    if (IO_MANAGER.GetKeyDownKeyBord(VK_S)) {
        SOUND_MANAGER.PlaySE(SOUND_LABEL::SE_SAMPLE000);
        m_selectedIndex++;
        if (m_selectedIndex >= m_buttonCount) m_selectedIndex = 0; // 下端に行ったら上端へループ
    }

    // 選択状態の判定
    int remainder = m_selectedIndex % 2;
    auto* select_1 = FindGameObjectWithTag("UI_OK_1");
    auto* select_2 = FindGameObjectWithTag("UI_NO_1");
    auto* select_3 = FindGameObjectWithTag("UI_OK_2");
    auto* select_4 = FindGameObjectWithTag("UI_NO_2");

    if (remainder == 0) {
        select_1->SetActive(TRUE);
        select_4->SetActive(TRUE);
        select_2->SetActive(FALSE);
        select_3->SetActive(FALSE);
    }
    else {
        select_2->SetActive(TRUE);
        select_3->SetActive(TRUE);
        select_1->SetActive(FALSE);
        select_4->SetActive(FALSE);
    }

    // Enterキーで決定
    if (IO_MANAGER.GetKeyDown(TYPE_OK) )
    {
        if (remainder == 0) {
            SOUND_MANAGER.PlaySE(SOUND_LABEL::SE_SELECT);
            std::cout << "Button A pressed - Start Game" << std::endl;
            m_nextScene = SCENE_TITLE;
        }
        else {
            std::cout << "Button B pressed" << std::endl;
            // ゲーム終了（メインループの while を抜けさせる）
            PostQuitMessage(0);
        }
        return;
    }

    // GameObjectリストを更新（プレイヤー移動など）
    UpdateObjectList();
}

void SceneResult::Draw()
{
    // 3D描画
    Draw(&m_Camera);

    // UI層のみ描画（カメラ不使用）
    DrawLayer(&m_Camera, RenderLayer::UI);
}

void SceneResult::Draw(Camera* camera)
{
    // WORLD層を描画（カメラ使用）
    DrawLayer(camera, RenderLayer::WORLD);
}