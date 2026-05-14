//========================================
// Include
//========================================
#include "Application.h"
#include "Defines.h"
#include "Game.h"
#include <imgui/imgui.h>
#include <string>


//========================================
// Class Static
//========================================
HINSTANCE  Application::m_hInst;        //!< インスタンスハンドル
HWND       Application::m_hWnd;         //!< ウィンドウハンドル
uint32_t   Application::m_Width;        //!< ウィンドウの横幅
uint32_t   Application::m_Height;       //!< ウィンドウの縦幅

// ImGuiのWin32プロシージャハンドラ(マウス対応)
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);


//========================================
// Application Class
//========================================

//====================
// ライフサイクル
//====================
/**
 * @brief コンストラクタです.
 * @param width ウィンドウの横幅
 * @param height ウィンドウの縦幅
 * @details ウィンドウのサイズを初期化し、タイマー精度を設定する。
 */
Application::Application(uint32_t width, uint32_t height)
{
    m_Height = height;
    m_Width = width;

    timeBeginPeriod(1);
}

/**
 * @brief デストラクタです.
 * @details タイマー精度を元に戻す。
 */
Application::~Application()
{
    timeEndPeriod(1);
}

/**
 * @brief アプリケーションを実行します.
 * @details 初期化に成功した場合、メインループを開始します。
 */
void Application::Run()
{
    // 初期化済みならMainLoopを実行する
    if (InitApp())
    {
        MainLoop();
    }

    TermApp();
}

//====================
// 各種実行関数
//====================
/**
 * @brief アプリケーションの初期化を行う
 * @return 初期化が成功した場合にtrueを返す。
 * @details ウィンドウの初期化が含まれる。
 */
bool Application::InitApp()
{
    // ウィンドウの初期化.
    if (!InitWnd())
    {
        return false;
    }

    // 正常終了.
    return true;
}

/**
 * @brief アプリケーションの終了処理を行う
 * @details ウィンドウの終了処理が含まれる。
 */
void Application::TermApp()
{
    // ウィンドウの終了処理.
    TermWnd();
}

/**
 * @brief ウィンドウを初期化する
 * @return 初期化に成功した場合にtrueを返す。
 * @details ウィンドウクラスの登録とウィンドウの生成を行う。
 */
bool Application::InitWnd()
{
    // インスタンスハンドルを取得.
    auto hInst = GetModuleHandle(nullptr);
    if (hInst == nullptr)
    {
        return false;
    }

    // ウィンドウの設定.
    WNDCLASSEX wc = {};
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
    wc.hCursor = LoadCursor(hInst, IDC_ARROW);
    wc.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
    wc.lpszMenuName = nullptr;
    wc.lpszClassName = APP_TITLE;
    wc.hIconSm = LoadIcon(hInst, IDI_APPLICATION);

    // ウィンドウの登録.
    if (!RegisterClassEx(&wc))
    {
        return false;
    }

    // インスタンスハンドル設定.
    m_hInst = hInst;

    // ウィンドウのサイズを設定.
    RECT rc = {};
    rc.right = static_cast<LONG>(m_Width);
    rc.bottom = static_cast<LONG>(m_Height);

    // ウィンドウサイズを調整.
    auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
    AdjustWindowRect(&rc, style, FALSE);

    // ウィンドウを生成.
    m_hWnd = CreateWindowEx(
        0,
        APP_TITLE,
        APP_TITLE,
        style,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        rc.right - rc.left,
        rc.bottom - rc.top,
        nullptr,
        nullptr,
        m_hInst,
        nullptr);

    if (m_hWnd == nullptr)
    {
        return false;
    }

    // ウィンドウを表示.
    ShowWindow(m_hWnd, SW_SHOWNORMAL);

    // ウィンドウを更新.
    UpdateWindow(m_hWnd);

    // ウィンドウにフォーカスを設定.
    SetFocus(m_hWnd);

    // 正常終了.
    return true;
}

/**
 * @brief ウィンドウの終了処理を行う
 * @details ウィンドウクラスの登録解除を行う。
 */
void Application::TermWnd()
{
    // ウィンドウの登録を解除.
    if (m_hInst != nullptr)
    {
        UnregisterClass(APP_TITLE, m_hInst);
    }

    m_hInst = nullptr;
    m_hWnd = nullptr;
}

/**
 * @brief メインループを実行する
 * @details メッセージを処理する。WM_QUITメッセージを受け取るまで続く。
 */
void Application::MainLoop()
{
    MSG msg = {};

    gameinit();

    while (WM_QUIT != msg.message)
    {
        if (PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE) == TRUE)
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
        else {
            // ゲームループ
            gameloop();
        }
    }

    gamedispose();

}

/**
 * @brief ウィンドウプロシージャ
 * @param hWnd ウィンドウハンドル
 * @param msg メッセージ
 * @param wp WPARAM パラメータ
 * @param lp LPARAM パラメータ
 * @return 処理結果を返す
 * @details ウィンドウのメッセージを処理する。
 */
LRESULT CALLBACK Application::WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{
    if (ImGui_ImplWin32_WndProcHandler(hWnd, msg, wp, lp))
        return true;

    switch (msg)
    {
    case WM_DESTROY:
    {
        PostQuitMessage(0);
    }
    break;

    default:
    { /* DO_NOTHING */ }
    break;
    }

    return DefWindowProc(hWnd, msg, wp, lp);
}

