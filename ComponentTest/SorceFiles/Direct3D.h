//==================================================
// [Direct3D.h] レンダラーモジュールヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：Direct3Dの出力処理部分をまとめたクラス
//==================================================
#ifndef DIRECT3D_H_
#define DIRECT3D_H_

/*----- マクロの定義 -----*/
#define SCREEN_WIDTH (800)	// ウインドウの幅
#define SCREEN_HEIGHT (800)	// ウインドウの高さ
#define WINDOW_NAME ("Mitana")	// ウィンドウに表示される名前


/*----- インクルード -----*/
#include "StdAfx.h"
#include <d3d11.h>  // DirectX11を使うためのヘッダーファイル
#include <DirectXMath.h>// DirectXの数学関数関連のヘッダーファイル
#include <cstdlib>




/*----- 構造体定義 -----*/
// 頂点データを表す構造体
struct Vertex
{
	// 頂点の位置座標
	float x, y, z;
	// 色情報
	float r, g, b, a;
	// テクスチャ座標（UV座標）
	float u, v;
};

// 定数バッファ用構造体
struct ConstBuffer
{
	// 頂点カラー行列
	DirectX::XMFLOAT4 color;
	// UV座標移動行列
	DirectX::XMMATRIX matrixTex;
	// プロジェクション変換行列
	DirectX::XMMATRIX matrixProj;
	// ワールド変換行列
	DirectX::XMMATRIX matrixWorld;
};

// 方向の定義
enum class DIRECTION
{
	Up
	, Right
	, Left
	, Down
};

/*----- 前方宣言 -----*/

//--------------------------------------------------
// レンダラーの出力処理クラス
//--------------------------------------------------
class Direct3D
{
public:
	Direct3D(class GameManager* gameManager);
	~Direct3D();

	HRESULT WindowCreate(HWND* hWnd);
	void Release();
	void Draw();
	void StartRender();
	void FinishRender();

	void AddSprite(class SpriteComponent* spriteComponent);
	void RemoveSprite(class SpriteComponent* SpriteComponent);

private:
	std::vector<class SpriteComponent*> sprites_;
};


/*----- エクスターン -----*/
extern ComPtr<ID3D11Device> g_cpDevice; // デバイス＝DirectXの各種機能を作る
extern ComPtr<ID3D11DeviceContext> g_cpDeviceContext;// コンテキスト＝描画関連を司る機能
extern ComPtr<ID3D11Buffer> g_cpConstantBuffer;


#endif	// DIRECT3D_H_
//==================================================
//				End of FIle
//==================================================
