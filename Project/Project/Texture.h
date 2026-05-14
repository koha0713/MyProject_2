/*
	概要:画像・描画先・Zバッファの管理
*/
#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include "DirectX.h"

/// テクスチャクラス
class Texture
{
public:
	// コンストラクタ・デストラクタ
	Texture();
	virtual ~Texture();

	/// テクスチャ作成
	HRESULT Create(const char* fileName);
	/// 空テクスチャ作成
	HRESULT Create(DXGI_FORMAT format, UINT width, UINT height, const void* pData = nullptr);

	UINT GetWidth() const;
	UINT GetHeight() const;
	ID3D11ShaderResourceView* GetResource() const;

protected:
	// GPUテクスチャ設計
	D3D11_TEXTURE2D_DESC MakeTexDesc(DXGI_FORMAT format, UINT width, UINT height);
	// GPU生成
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData);

protected:
	// 変数
	UINT m_width;	///<- 横幅
	UINT m_height;	///<- 縦幅
	ID3D11ShaderResourceView* m_pSRV;	// シェーダから読む画像
	ID3D11Texture2D* m_pTex;	// VRAM上の画像

};

/// レンダーターゲット
class RenderTarget : public Texture
{
public:
	RenderTarget();
	~RenderTarget();

	// 画面クリア
	void Clear();
	// 画面塗りつぶし
	void Clear(const float* color);

	HRESULT Create(DXGI_FORMAT format, UINT width, UINT height);
	HRESULT CreateFromScreen();
	ID3D11RenderTargetView* GetView() const;

protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

private:
	ID3D11RenderTargetView* m_pRTV;	// 書き込みビュー
};

/// 深度テクスチャ
class DepthStencil : public Texture
{
public:
	DepthStencil();
	~DepthStencil();
	void Clear();
	HRESULT Create(UINT width, UINT height, bool useStencil);
	ID3D11DepthStencilView* GetView() const;

protected:
	virtual HRESULT CreateResource(D3D11_TEXTURE2D_DESC& desc, const void* pData = nullptr);

private:
	ID3D11DepthStencilView* m_pDSV;
};

#endif // !__TEXTURE_H__
