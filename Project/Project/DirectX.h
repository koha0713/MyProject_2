/*
	概要:DirectX11の描画環境を初期化・管理するラッパー
	InitDirectX();
	SetBlendMode();
	SetDepthTest();
	SwapDirectX();
*/
#ifndef __DIRECTX_H__
#define __DIRECTX_H__

#include <d3d11.h>

// ライブラリリンク
#pragma comment (lib,"d3d11.lib")

#define SAFE_RELEASE(p) do{if(p){p->Release(); p = nullptr;}}while(0)

// 前方宣言
class RenderTarget;
class DepthStencil;

// 列挙型

/// 色の合成法
enum BlendMode
{
	BLEND_NONE,		// 不透明
	BLEND_ALPHA,	// 半透明
	BLEND_ADD,		// 加算発光
	BLEND_ADDALPHA,
	BLEND_SUB,
	BLEND_SCREEN,	// 明るく合成
	BLEND_MAX
};

/// テクスチャの拡大法
enum SamplerState
{
	SAMPLER_LINEAR,	// なめらか
	SAMPLER_POINT,	// ドット絵
	SAMPLER_MAX
};

/// Zバッファ設定
enum DepthState
{
	DEPTH_ENABLE_WRITE_TEST,	// 深度書き込み
	DEPTH_ENABLE_TEST,			// テストのみ
	DEPTH_DISABLE,				// 無効
	DEPTH_MAX
};

// グローバル変数
ID3D11Device* GetDevice();			// GPU
ID3D11DeviceContext* GetContext();	// 命令キュー
IDXGISwapChain* GetSwapChain();		// 画面表示

HRESULT InitDirectX(HWND hWnd, UINT width, UINT height, bool fullscreen);
void UninitDirectX();
void SwapDirectX();

void SetRenderTargets(UINT num, RenderTarget** ppViews, DepthStencil* pView);
void SetCullingMode(D3D11_CULL_MODE cull);
void SetDepthTest(DepthState state);
void SetBlendMode(BlendMode blend);
void SetSamplerState(SamplerState state);


#endif // !__DIRECTX_H__
