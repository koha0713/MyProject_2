#include "DebugUI.h"

std::vector<std::function<void(void)>> DebugUI::m_debugfunction;

void DebugUI::Init(ID3D11Device* device, ID3D11DeviceContext* context) 
{
    // バージョンの確認
    IMGUI_CHECKVERSION();

    // コンテキストの作成
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    // io = ImGui::GetIO();
    // キーボードによるナビゲーションの有効化
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    // コントローラーによるナビゲーションの有効化
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // imguiのスタイル
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    io.Fonts->Clear();

    ImFontConfig cfg;
    cfg.OversampleH = 2;
    cfg.OversampleV = 1;
    cfg.MergeMode = false;

    // メイリオ or Yu Gothic を推奨（Windows 11 標準搭載）
    io.Fonts->AddFontFromFileTTF(
        "C:\\Windows\\Fonts\\meiryo.ttc",
        18.0f,
        &cfg,
        io.Fonts->GetGlyphRangesJapanese()
    );
    io.Fonts->Build();

    // Win32用の初期化
    ImGui_ImplWin32_Init(device);
    // DirectX11用の初期化
    ImGui_ImplDX11_Init(device, context);
}
