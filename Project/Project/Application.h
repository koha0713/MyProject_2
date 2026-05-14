#pragma once

#include <Windows.h>
#include <cstdint>


/**
 * @brief アプリケーションクラス
 * @details 詳細な説明
 */
class Application
{
public:
    // ライフサイクル

    /**
     * @brief デフォルトコンストラクタ
     */
    Application() = default;

    /**
     * @brief コピーコンストラクタを削除
     * @details このクラスのオブジェクトのコピーは許可されていないため、コピーコンストラクタは削除される。
     */
    Application(const Application&) = delete;

    /**
     * @brief コピー代入演算子を削除
     * @details このクラスのオブジェクトの代入は許可されていないため、コピー代入演算子は削除される。
     */
    Application& operator=(const Application&) = delete;

    /**
     * @brief コンストラクタです.
     * @param width ウィンドウの横幅
     * @param height ウィンドウの縦幅
     * @details ウィンドウのサイズを設定し、アプリケーションを初期化する。
     */
    Application(uint32_t width, uint32_t height);

    /**
     * @brief デストラクタ
     * @details アプリケーションの終了処理を行う。
     */
    ~Application();

    /**
     * @brief アプリケーションを実行する
     * @details メインループを開始し、アプリケーションのメイン処理を実行する。
     */
    void Run();


    // 取得関数

    /**
     * @brief ウィンドウの横幅を取得
     * @return ウィンドウの横幅を返す
     */
    static uint32_t GetWidth() {
        return m_Width;
    }

    /**
     * @brief ウィンドウの縦幅を取得
     * @return ウィンドウの縦幅を返す.
     */
    static uint32_t GetHeight() {
        return m_Height;
    }

    /**
     * @brief ウィンドウハンドルを取得
     * @return ウィンドウハンドルを返す.
     */
    static HWND GetWindow() {
        return m_hWnd;
    }

    /**
     * @brief インスタンスハンドルを取得
     * @return インスタンスハンドルを返す
     */
    static HINSTANCE GetHInstance() {
        return m_hInst;
    }

private:
    static HINSTANCE    m_hInst;    ///< インスタンスハンドル
    static HWND         m_hWnd;     ///< ウィンドウハンドル
    static uint32_t     m_Width;    ///< ウィンドウの横幅
    static uint32_t     m_Height;   ///< ウィンドウの縦幅

    static bool InitApp();
    static void TermApp();
    static bool InitWnd();
    static void TermWnd();
    static void MainLoop();

    /**
         * @brief ウィンドウプロシージャ関数です.
         * @param hWnd ウィンドウハンドル
         * @param msg メッセージ
         * @param wp WPARAM パラメータ
         * @param lp LPARAM パラメータ
         * @return 処理結果を返す。
         * @details ウィンドウに送られたメッセージを処理する。
         */
    static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp);
};
