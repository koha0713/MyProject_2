// ===================================================================
// SceneTitle.h
// タイトルシーン - GameObjectとコンポーネントシステムを使用
// ===================================================================
#pragma once
#include "SceneBase.h"

class SceneTitle : public SceneBase
{
private:
    // オブジェクト管理用ID
    enum OBJECT_ID
    {
        ID_TITLE_CUBE,

        ID_COUNT,
    };

    int m_selectedIndex = 0; // 選択中のボタンインデックス
    int m_buttonCount = 3;   // ボタンの総数（今回は3つ）

    bool setu= false;

public:
    void Init() override;
    void UnInit() override;
    void Update() override;
    void Draw() override;
    void Draw(Camera*) override;
};