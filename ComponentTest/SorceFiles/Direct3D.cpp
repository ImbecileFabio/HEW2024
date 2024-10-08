//==================================================
// [Direct3D.cpp] レンダラーモジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：Direct3Dの出力処理部分をまとめたクラスの定義
//==================================================

/*----- インクルード -----*/
#include <d3dcompiler.h>
#include <D3D11SDKLayers.h>
#pragma comment (lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")
#include <atltypes.h> // CRectを使うためのヘッダーファイル
#include <locale.h>
#include <io.h>
#include <stdio.h>
#include <string.h>

#include "StdAfx.h"
#include "Direct3D.h"
#include "GameObjects/Component/RenderComponent/SpriteComponent.h"

/*----- プロトタイプ宣言 -----*/
// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
HRESULT CreateVertexShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
	D3D11_INPUT_ELEMENT_DESC* layout, unsigned int numElements, ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout);

// ピクセルシェーダーオブジェクトを生成
HRESULT CreatePixelShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3D11PixelShader** ppPixelShader);

/*----- グローバル変数 -----*/
// デバイス＝DirectXの各種機能を作る
ComPtr<ID3D11Device> g_cpDevice;
// コンテキスト＝描画関連を司る機能
ComPtr<ID3D11DeviceContext> g_cpDeviceContext;
// スワップチェイン＝ダブルバッファ機能
ComPtr<IDXGISwapChain> g_cpSwapChain;
// レンダーターゲット＝描画先を表す機能
ComPtr<ID3D11RenderTargetView> g_cpRenderTargetView;
// デプスバッファ
ComPtr<ID3D11DepthStencilView> g_cpDepthStencilView;
// インプットレイアウト
ComPtr<ID3D11InputLayout> g_cpInputLayout;
// 頂点シェーダーオブジェクト
ComPtr<ID3D11VertexShader> g_cpVertexShader;
// ピクセルシェーダーオブジェクト
ComPtr<ID3D11PixelShader> g_cpPixelShader;
// サンプラー用変数
ComPtr<ID3D11SamplerState> g_cpSampler;
// 定数バッファ用変数
ComPtr<ID3D11Buffer> g_cpConstantBuffer;
// ブレンドステート用変数 ( アルファブレンディング)
ComPtr<ID3D11BlendState> g_cpBlendState;



//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Direct3D::Direct3D(GameManager* gameManager)
{
	std::cout << "[Direct3D] -> 生成\n";
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Direct3D::~Direct3D()
{
	std::cout << "[Direct3D] -> 破棄\n";

}

HRESULT Direct3D::WindowCreate(HWND* hWnd)
{
	std::cout << "[Direct3D] -> ウィンドウ作成開始\n";

	HRESULT  hr; // HRESULT型・・・Windowsプログラムで関数実行の成功/失敗を受け取る

	D3D_FEATURE_LEVEL pLevels[] = { D3D_FEATURE_LEVEL_11_0 };
	D3D_FEATURE_LEVEL level;
	CRect              rect;
	::GetClientRect(*hWnd, &rect);

	// デバイス作成時にデバッグフラグを有効にする
	UINT createDeviceFlags = 0;
#if defined(DEBUG) || defined(_DEBUG)
	createDeviceFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif


	// デバイス、スワップチェーン作成
	DXGI_SWAP_CHAIN_DESC swapChainDesc{};
	::ZeroMemory(&swapChainDesc, sizeof(swapChainDesc));
	swapChainDesc.BufferCount = 1;
	swapChainDesc.BufferDesc.Width = SCREEN_WIDTH;
	swapChainDesc.BufferDesc.Height = SCREEN_HEIGHT;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.OutputWindow = *hWnd;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.Windowed = TRUE;

	// デバイスとスワップチェインを同時に作成する関数の呼び出し
	hr = D3D11CreateDeviceAndSwapChain(NULL,
		D3D_DRIVER_TYPE_HARDWARE,
		NULL,
		createDeviceFlags,
		pLevels,
		1,
		D3D11_SDK_VERSION,
		&swapChainDesc,
		g_cpSwapChain.GetAddressOf(),
		g_cpDevice.GetAddressOf(),
		&level,
		g_cpDeviceContext.GetAddressOf());
	if (FAILED(hr)) return hr; // 上の関数呼び出しが失敗してないかifでチェック

	// レンダーターゲットビュー作成
	ID3D11Texture2D* renderTarget;
	hr = g_cpSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&renderTarget);
	if (FAILED(hr)) return hr;
	hr = g_cpDevice->CreateRenderTargetView(renderTarget, NULL, g_cpRenderTargetView.GetAddressOf());
	renderTarget->Release();
	if (FAILED(hr)) return hr;

	// デプスステンシルバッファ作成
	// ※（デプスバッファ = 深度バッファ = Zバッファ）→奥行を判定して前後関係を正しく描画できる
	ID3D11Texture2D* depthStencile;
	D3D11_TEXTURE2D_DESC textureDesc;
	ZeroMemory(&textureDesc, sizeof(textureDesc));
	textureDesc.Width = swapChainDesc.BufferDesc.Width;
	textureDesc.Height = swapChainDesc.BufferDesc.Height;
	textureDesc.MipLevels = 1;
	textureDesc.ArraySize = 1;
	textureDesc.Format = DXGI_FORMAT_D16_UNORM;
	textureDesc.SampleDesc = swapChainDesc.SampleDesc;
	textureDesc.Usage = D3D11_USAGE_DEFAULT;
	textureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	textureDesc.CPUAccessFlags = 0;
	textureDesc.MiscFlags = 0;
	hr = g_cpDevice->CreateTexture2D(&textureDesc, NULL, &depthStencile);
	if (FAILED(hr)) return hr;

	// デプスステンシルビュー作成
	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc;
	ZeroMemory(&depthStencilViewDesc, sizeof(depthStencilViewDesc));
	depthStencilViewDesc.Format = textureDesc.Format;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Flags = 0;
	hr = g_cpDevice->CreateDepthStencilView(depthStencile, &depthStencilViewDesc, g_cpDepthStencilView.GetAddressOf());
	if (FAILED(hr)) return hr;
	depthStencile->Release();

	// ビューポートを作成（→画面分割などに使う、描画領域の指定のこと）
	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = (FLOAT)rect.Width();
	viewport.Height = (FLOAT)rect.Height();
	viewport.MinDepth = 0.0f;
	viewport.MaxDepth = 1.0f;
	g_cpDeviceContext->RSSetViewports(1, &viewport);



	// インプットレイアウト作成
	D3D11_INPUT_ELEMENT_DESC layout[]
	{
		// 位置座標があるということを伝える
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,    0,                            0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// 色情報があるということを伝える
		{ "COLOR",	  0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		// UV座標(uv)
		{ "TEX",	  0, DXGI_FORMAT_R32G32_FLOAT,		 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	unsigned int numElements = ARRAYSIZE(layout);

	// 頂点シェーダーオブジェクトを生成、同時に頂点レイアウトも生成
	hr = CreateVertexShader(g_cpDevice.Get(), "VertexShader.hlsl", "vs_main", "vs_5_0",
		layout, numElements, g_cpVertexShader.GetAddressOf(), g_cpInputLayout.GetAddressOf());
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreateVertexShader error", "error", MB_OK);
		return E_FAIL;
	}

	// ピクセルシェーダーオブジェクトを生成
	hr = CreatePixelShader(g_cpDevice.Get(), "PixelShader.hlsl", "ps_main", "ps_5_0", g_cpPixelShader.GetAddressOf());
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreatePixelShader error", "error", MB_OK);
		return E_FAIL;
	}



	// サンプラー作成 
	// → テクスチャをポリゴンに貼るときに、拡大縮小される際のアルゴリズム
	D3D11_SAMPLER_DESC smpDesc;
	::ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
	hr = g_cpDevice->CreateSamplerState(&smpDesc, g_cpSampler.GetAddressOf());
	if (FAILED(hr)) return hr;

	// 定数バッファ作成
	D3D11_BUFFER_DESC cbDesc;
	cbDesc.ByteWidth = sizeof(ConstBuffer);
	cbDesc.Usage = D3D11_USAGE_DEFAULT;
	cbDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbDesc.CPUAccessFlags = 0;
	cbDesc.MiscFlags = 0;
	cbDesc.StructureByteStride = 0;
	hr = g_cpDevice->CreateBuffer(&cbDesc, NULL, g_cpConstantBuffer.GetAddressOf());
	if (FAILED(hr)) return hr;

	// ブレンドステート作成 → 透過処理や加算合成を可能にする色の合成方法
	D3D11_BLEND_DESC BlendState;
	ZeroMemory(&BlendState, sizeof(D3D11_BLEND_DESC));
	BlendState.AlphaToCoverageEnable = FALSE;
	BlendState.IndependentBlendEnable = FALSE;
	BlendState.RenderTarget[0].BlendEnable = TRUE;
	BlendState.RenderTarget[0].SrcBlend = D3D11_BLEND_SRC_ALPHA;
	BlendState.RenderTarget[0].DestBlend = D3D11_BLEND_INV_SRC_ALPHA;
	BlendState.RenderTarget[0].BlendOp = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].SrcBlendAlpha = D3D11_BLEND_ONE;
	BlendState.RenderTarget[0].DestBlendAlpha = D3D11_BLEND_ZERO;
	BlendState.RenderTarget[0].BlendOpAlpha = D3D11_BLEND_OP_ADD;
	BlendState.RenderTarget[0].RenderTargetWriteMask = D3D11_COLOR_WRITE_ENABLE_ALL;
	hr = g_cpDevice->CreateBlendState(&BlendState, g_cpBlendState.GetAddressOf());
	if (FAILED(hr)) return hr;

	// 深度テストを無効にする（多分Z軸のこと）
	ID3D11DepthStencilState* pDSState;
	D3D11_DEPTH_STENCIL_DESC dsDesc;
	ZeroMemory(&dsDesc, sizeof(dsDesc));
	dsDesc.DepthEnable = FALSE; // 深度テストを無効化する
	dsDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	dsDesc.DepthFunc = D3D11_COMPARISON_LESS;
	hr = g_cpDevice->CreateDepthStencilState(&dsDesc, &pDSState);
	if (FAILED(hr)) return hr;
	g_cpDeviceContext->OMSetDepthStencilState(pDSState, 1);




	std::cout << "[Direct3D] -> ウィンドウ作成終了\n";


	return S_OK;
}

void Direct3D::Release()
{
}

/*-----------------------------------------------------------------------------
/* 描画処理
-----------------------------------------------------------------------------*/
void Direct3D::Draw(void)
{
	std::cout << "\n";
	std::cout << "レンダラーの出力化処理の開始\n";
	
	StartRender();
	//for (auto sprite : sprites_)
	//{
	//	sprite->Draw();
	//}
	FinishRender();

	std::cout << "レンダラーの出力化処理の終了\n";
	std::cout << "\n";
}

void Direct3D::StartRender()
{

	std::cout << "\n";
	std::cout << "[Direct3D] -> 出力化処理の開始\n";

	// 画面塗りつぶし色
	float clearColor[4] = { 0.3f, 0.3f, 0.6f, 1.0f }; //red,green,blue,alpha

	// 描画先のキャンバスと使用する深度バッファを指定する
	g_cpDeviceContext->OMSetRenderTargets(1, g_cpRenderTargetView.GetAddressOf(), g_cpDepthStencilView.Get());
	// 描画先キャンバスを塗りつぶす
	g_cpDeviceContext->ClearRenderTargetView(g_cpRenderTargetView.Get(), clearColor);
	// 深度バッファをリセットする
	g_cpDeviceContext->ClearDepthStencilView(g_cpDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	g_cpDeviceContext->IASetInputLayout(g_cpInputLayout.Get());
	g_cpDeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	g_cpDeviceContext->VSSetShader(g_cpVertexShader.Get(), NULL, 0);
	g_cpDeviceContext->PSSetShader(g_cpPixelShader.Get(), NULL, 0);

	// 定数バッファを頂点シェーダーにセットする
	g_cpDeviceContext->VSSetConstantBuffers(0, 1, g_cpConstantBuffer.GetAddressOf());

	// サンプラーをピクセルシェーダーに渡す
	g_cpDeviceContext->PSSetSamplers(0, 1, g_cpSampler.GetAddressOf());

	// ブレンドステートをセットする
	g_cpDeviceContext->OMSetBlendState(g_cpBlendState.Get(), NULL, 0xffffffff);

	std::cout << "[Direct3D] -> 出力化処理の終了\n";
	std::cout << "\n";

}

void Direct3D::FinishRender()
{
	// ダブルバッファの切り替えを行い画面を更新する
	g_cpSwapChain->Present(0, 0);
}

////--------------------------------------------------
//// 描画処理
////--------------------------------------------------
//void Renderer::Draw(void)
//{
//	std::cout << "\n";
//	std::cout << "[Direct3D] -> 出力化処理の開始\n";
//
//	for (auto sprite : sprites_)
//		sprite->Draw();
//
//	std::cout << "[Direct3D] -> 出力化処理の終了\n";
//	std::cout << "\n";
//}

//--------------------------------------------------
// スプライトの追加処理
//--------------------------------------------------
void Direct3D::AddSprite(SpriteComponent* spriteComponent)
{
	int myDrawOrder = spriteComponent->GetDrawOrder();

	auto iter = sprites_.begin();
	for (; 
		iter != sprites_.end();
		++iter)
	{
		if (myDrawOrder < (*iter)->GetDrawOrder()) { break; }
	}

	// Inserts element before position of iterator
	sprites_.insert(iter, spriteComponent);
}

//--------------------------------------------------
// スプライトの削除処理
//--------------------------------------------------
void Direct3D::RemoveSprite(SpriteComponent* spriteComponent)
{
	auto iter = std::find(sprites_.begin(), sprites_.end(), spriteComponent);
	sprites_.erase(iter);
}


//--------------------------------------------------------------------------------------
// シェーダーをファイル拡張子に合わせてコンパイル
//--------------------------------------------------------------------------------------
HRESULT CompileShader(const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, void** ShaderObject, size_t& ShaderObjectSize, ID3DBlob** ppBlobOut)
{
	*ppBlobOut = nullptr;
	int aaa = strlen(szFileName);
	//拡張子をhlslからcsoに変更したファイル名を作成
	char* csoFileName = new char[strlen(szFileName)];
	const char* dot = strrchr(szFileName, '.'); // 最後の"."を探す
	if (dot != NULL) {
		size_t prefixLength = dot - szFileName;
		strncpy_s(csoFileName, prefixLength + 1, szFileName, _TRUNCATE); // 拡張子以外をコピー
		strcpy_s(csoFileName + prefixLength, 5, ".cso"); // 新しい拡張子を追加
	}
	else {
		strcpy_s(csoFileName, strlen(szFileName), szFileName); // 拡張子がない場合はそのままコピー
	}

	FILE* fp;
	// コンパイル済みシェーダーファイル(cso)があれば読み込む
	if (fopen_s(&fp, csoFileName, "rb") == 0)
	{
		long int size = _filelength(_fileno(fp));
		unsigned char* buffer = new unsigned char[size];
		fread(buffer, size, 1, fp);
		if (!buffer) return E_FAIL;
		*ShaderObject = buffer;
		ShaderObjectSize = size;
		fclose(fp);
	}
	// コンパイル済みシェーダーファイルが無ければシェーダーファイル(hlsl)をコンパイルする
	else
	{
		ID3DBlob* p1 = nullptr;
		HRESULT hr = S_OK;
		WCHAR	filename[512];
		size_t 	wLen = 0;
		int err = 0;

		// char -> wcharに変換
		setlocale(LC_ALL, "japanese");
		err = mbstowcs_s(&wLen, filename, 512, szFileName, _TRUNCATE);

		DWORD dwShaderFlags = D3DCOMPILE_ENABLE_STRICTNESS;
#if defined( DEBUG ) || defined( _DEBUG )
		// D3DCOMPILE_DEBUGフラグを設定すると、シェーダーにデバッグ情報が埋め込まれる
		dwShaderFlags |= D3DCOMPILE_DEBUG;
#endif

		ID3DBlob* pErrorBlob = nullptr;
		hr = D3DCompileFromFile(filename, nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			szEntryPoint, szShaderModel, dwShaderFlags, 0, ppBlobOut, &pErrorBlob);
		if (FAILED(hr))
		{
			if (pErrorBlob != nullptr) {
				MessageBoxA(NULL, (char*)pErrorBlob->GetBufferPointer(), "Error", MB_OK);
			}
			if (pErrorBlob) pErrorBlob->Release();
			if (*ppBlobOut)(*ppBlobOut)->Release();
			return hr;
		}
		if (pErrorBlob) pErrorBlob->Release();

		*ShaderObject = (*ppBlobOut)->GetBufferPointer();
		ShaderObjectSize = (*ppBlobOut)->GetBufferSize();
	}

	delete[] csoFileName;
	return S_OK;
}


//--------------------------------------------------------------------------------------
// 頂点シェーダーオブジェクトを生成する
//--------------------------------------------------------------------------------------
HRESULT CreateVertexShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel,
	D3D11_INPUT_ELEMENT_DESC* layout, unsigned int numElements, ID3D11VertexShader** ppVertexShader, ID3D11InputLayout** ppVertexLayout)
{
	HRESULT   hr;
	ID3DBlob* pBlob = nullptr;
	void* ShaderObject;
	size_t	  ShaderObjectSize;

	// ファイルの拡張子に合わせてコンパイル
	hr = CompileShader(szFileName, szEntryPoint, szShaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return E_FAIL;
	}

	// 頂点シェーダーを生成
	hr = device->CreateVertexShader(ShaderObject, ShaderObjectSize, NULL, ppVertexShader);
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return E_FAIL;
	}

	// 頂点データ定義生成
	hr = device->CreateInputLayout(
		layout,
		numElements,
		ShaderObject,
		ShaderObjectSize,
		ppVertexLayout);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "CreateInputLayout error", "error", MB_OK);
		pBlob->Release();
		return E_FAIL;
	}

	return S_OK;
}

//--------------------------------------------------------------------------------------
// ピクセルシェーダーオブジェクトを生成する
//--------------------------------------------------------------------------------------
HRESULT CreatePixelShader(ID3D11Device* device, const char* szFileName, LPCSTR szEntryPoint, LPCSTR szShaderModel, ID3D11PixelShader** ppPixelShader)
{
	HRESULT   hr;
	ID3DBlob* pBlob = nullptr;
	void* ShaderObject;
	size_t	  ShaderObjectSize;

	// ファイルの拡張子に合わせてコンパイル
	hr = CompileShader(szFileName, szEntryPoint, szShaderModel, &ShaderObject, ShaderObjectSize, &pBlob);
	if (FAILED(hr))
	{
		return E_FAIL;
	}

	// ピクセルシェーダーを生成
	hr = device->CreatePixelShader(ShaderObject, ShaderObjectSize, NULL, ppPixelShader);
	if (FAILED(hr))
	{
		if (pBlob)pBlob->Release();
		return E_FAIL;
	}

	return S_OK;
}
//==================================================
//				End of FIle
//==================================================
