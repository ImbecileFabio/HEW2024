//==================================================
// [Renderer.h] レンダラーモジュールヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：DirectXの宣言
//==================================================
#ifndef RENDERER_H_
#define RENDERER_H_

#define TEXTURE_PATH_ "asset/Texture/"


/*----- インクルード -----*/
#include <d3d11.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include	<io.h>
#include	<string>
#include	<vector>
#include	<memory>

#pragma comment(lib, "directxtk.lib")
#pragma comment(lib, "d3d11.lib")
/*----- 構造体定義 -----*/
// ３Ｄ頂点データ
struct VERTEX_3D
{
	DirectX::SimpleMath::Vector3 position;
	DirectX::SimpleMath::Vector3 normal;
	DirectX::SimpleMath::Color color;
	DirectX::SimpleMath::Vector2 uv;
};

// ブレンドステート
enum EBlendState {
	BS_NONE = 0,							// 半透明合成無し
	BS_ALPHABLEND,							// 半透明合成
	BS_ADDITIVE,							// 加算合成
	BS_SUBTRACTION,							// 減算合成
	MAX_BLENDSTATE
};

// メッシュ
struct SUBSET
{
	std::string MtrlName;			// マテリアル名
	unsigned int IndexNum = 0;		// インデックス数
	unsigned int VertexNum = 0;		// 頂点数
	unsigned int IndexBase = 0;		// 開始インデックス	
	unsigned int VertexBase = 0;	// 頂点ベース
	unsigned int MaterialIdx = 0;	// マテリアルの番号
};

// マテリアル
struct MATERIAL
{
	DirectX::SimpleMath::Color Ambient; // 環境反射
	DirectX::SimpleMath::Color Diffuse;	// 拡散反射 (≒カラー)
	DirectX::SimpleMath::Color Specular;	// 鏡面反射
	DirectX::SimpleMath::Color Emission;	// 発光
	float Shiness;	// 光沢の滑らかさ
	BOOL TextureEnable;	//テクスチャを使うか否かのフラグ
	BOOL Dummy[2];
};

/*----- 前方宣言 -----*/
class GameManager;
class Renderer;
class RenderComponent;


//-----------------------------------------------------------------
//Rendererクラス
//-----------------------------------------------------------------
class Renderer
{
public:
	Renderer();
	~Renderer();

	void Init();
	void Uninit();
	void Begin();
	void Draw();
	void End();

	void AddSprite(RenderComponent* renderComponent);
	void RemoveSprite(RenderComponent* renderComponent);

	static void SetDepthEnable(bool Enable);

	static void SetATCEnable(bool Enable);

	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(DirectX::SimpleMath::Matrix* WorldMatrix);
	static void SetViewMatrix(DirectX::SimpleMath::Matrix* ViewMatrix);
	static void SetProjectionMatrix(DirectX::SimpleMath::Matrix* ProjectionMatrix);

	static auto GetRenderTargetView() { return m_RenderTargetView; }

	// デバイスを返す
	static ID3D11Device* GetDevice(void) { return m_Device; }
	// デバイスコンテキストを返す
	static ID3D11DeviceContext* GetDeviceContext(void) { return m_DeviceContext; }

	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);

	static void SetMaterial(MATERIAL Material);
	//static void SetUV(float u, float v);
private:

	std::vector<RenderComponent*> sprites_;

	static D3D_FEATURE_LEVEL m_FeatureLevel;

	static ID3D11Device* m_Device;
	static ID3D11DeviceContext* m_DeviceContext;
	static IDXGISwapChain* m_SwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11Texture2D* render_target_texture_;
	static ID3D11ShaderResourceView* render_target_SRV_;
	static ID3D11DepthStencilView* m_DepthStencilView;

	static ID3D11Buffer* m_WorldBuffer;
	static ID3D11Buffer* m_ViewBuffer;
	static ID3D11Buffer* m_ProjectionBuffer;

	static ID3D11Buffer* m_MaterialBuffer;
	static ID3D11Buffer* m_TextureBuffer;

	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

	static ID3D11BlendState* m_BlendState[MAX_BLENDSTATE]; // ブレンド ステート;
	static ID3D11BlendState* m_BlendStateATC;

	//-----------------------------------------------------------------
	// ブレンド ステート設定
	//-----------------------------------------------------------------
	static void SetBlendState(int nBlendState)
	{
		if (nBlendState >= 0 && nBlendState < MAX_BLENDSTATE) {
			float blendFactor[4] = { 0.0f, 0.0f, 0.0f, 0.0f };
			m_DeviceContext->OMSetBlendState(m_BlendState[nBlendState], blendFactor, 0xffffffff);
		}
	}
};

#endif	// RENDERER_H_
