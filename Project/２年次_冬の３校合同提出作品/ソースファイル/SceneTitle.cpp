// ===================================================================
// SceneTitle.cpp
// タイトルシーン実装
// ===================================================================
#include "SceneTitle.h"
#include "SceneManager.h"
#include "IOManager.h"

// コンポーネント
#include "RotatorComponent.h"

#include <iostream>
#include <Texture2D.h>
#include <SoundManager.h>

void SceneTitle::Init()
{
    std::cout << "========================================" << std::endl;
    std::cout << "[SceneTitle] Init START" << std::endl;

    IO_MANAGER.DisableFPSMouse();

    // 既存オブジェクトを削除
    DeleteObjectList();

    using namespace DirectX::SimpleMath;

    // オブジェクトリスト作成
    MakeObjectList(SCENE_MANAGER.GetSceneName(SCENE_TITLE).c_str());


    auto* manual = FindGameObjectWithTag("SETUMEI");
    manual->SetActive(FALSE);
    setu = false;

    // カメラ初期化
    m_Camera.Init();

    m_nextScene = SCENE_NONE;

    SOUND_MANAGER.PlayBGM(SOUND_LABEL::BGM_TITLE);

    // 初期化完了
    m_isInitialized = true;

    std::cout << "[SceneTitle] Initialized successfully" << std::endl;
    std::cout << "========================================" << std::endl;
    std::cout << "" << std::endl;
    std::cout << "=== TITLE SCENE ===" << std::endl;
    std::cout << "Controls:" << std::endl;
    std::cout << "  ENTER - Start Game" << std::endl;
    std::cout << "  SPACE - Go to TestCube" << std::endl;
    std::cout << "" << std::endl;
}

void SceneTitle::UnInit()
{
    std::cout << "[SceneTitle] UnInit" << std::endl;
    DeleteObjectList();

    // カメラ終了処理
    m_Camera.Uninit();

    SOUND_MANAGER.StopBGM();

    m_isInitialized = false;
}

void SceneTitle::Update()
{
    // カメラ更新
    m_Camera.Update();
    // 操作説明非表示中
    if (setu == false) {

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
        int remainder = m_selectedIndex % 3;
        auto* select_1 = FindGameObjectWithTag("UI1");
        auto* select_2 = FindGameObjectWithTag("UI2");
        auto* select_3 = FindGameObjectWithTag("UI3");
        auto* select_4 = FindGameObjectWithTag("UI_1");
        auto* select_5 = FindGameObjectWithTag("UI_2");
        auto* select_6 = FindGameObjectWithTag("UI_3");

        if (remainder == 0) {
            select_1->SetActive(TRUE);
            select_5->SetActive(TRUE);
            select_6->SetActive(TRUE);
            select_2->SetActive(FALSE);
            select_3->SetActive(FALSE);
            select_4->SetActive(FALSE);
        }
        else if (remainder == 1) {
            select_2->SetActive(TRUE);
            select_4->SetActive(TRUE);
            select_6->SetActive(TRUE);
            select_1->SetActive(FALSE);
            select_3->SetActive(FALSE);
            select_5->SetActive(FALSE);
        }
        else {
            select_3->SetActive(TRUE);
            select_4->SetActive(TRUE);
            select_5->SetActive(TRUE);
            select_1->SetActive(FALSE);
            select_2->SetActive(FALSE);
            select_6->SetActive(FALSE);
        }

        // Enterキーで決定
        if (IO_MANAGER.GetKeyDown(TYPE_OK))
        {
            if (remainder == 0) {
                SOUND_MANAGER.PlaySE(SOUND_LABEL::SE_SELECT);
                std::cout << "Button A pressed - Start Game" << std::endl;
                SCENE_MANAGER.ChangeSceneWithLoading(SCENE_GAME);
            }
            else if (remainder == 1) {
                SOUND_MANAGER.PlaySE(SOUND_LABEL::SE_SELECT);
                std::cout << "Button B pressed" << std::endl;
                auto* manual = FindGameObjectWithTag("SETUMEI");
                manual->SetActive(TRUE);
                setu = true;
            }
            else {
                SOUND_MANAGER.PlaySE(SOUND_LABEL::SE_SELECT);
                // ゲーム終了（メインループの while を抜けさせる）
                PostQuitMessage(0);
            }
            return;
        }
    }
    // 操作説明表示中
    else {
        // Enterキーで決定
        if (IO_MANAGER.GetKeyDown(TYPE_OK) || IO_MANAGER.GetMouseDown(VK_LBUTTON))
        {
            SOUND_MANAGER.PlaySE(SOUND_LABEL::SE_SELECT);
            auto* manual_1 = FindGameObjectWithTag("SETUMEI");
            manual_1->SetActive(FALSE);
            setu = false;
        }
    }

    // GameObjectリストを更新
    UpdateObjectList();
}

void SceneTitle::Draw()
{
    // 3D描画
    Draw(&m_Camera);

    // UI層のみ描画（カメラ不使用）
    DrawLayer(&m_Camera, RenderLayer::UI);
}

void SceneTitle::Draw(Camera* camera)
{
    // WORLD層を描画（カメラ使用）
    DrawLayer(camera, RenderLayer::WORLD);
}