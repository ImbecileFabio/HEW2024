//==================================================
// [DebugCollisionDrawComponent.h] 描画コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：とても描画コンポーネントの宣言
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>
#include <string>

#include "DebugCollisionDrawComponent.h"
#include "../../../GameManager.h"
#include "../../../SubSystem/dx11helper.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"
#include "../ColliderComponent/BoxColliderComponent.h"


#include <wrl/client.h>

using namespace DirectX::SimpleMath;
/*----- 前方宣言 -----*/
bool CreateGeometryShader(ID3D11Device* device, ID3D11GeometryShader** geometryShader, ID3D11Buffer** constantBuffer);

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
DebugCollisionDrawComponent::DebugCollisionDrawComponent(GameObject* _owner, int _drawOrder)
	: RenderComponent(_owner, _drawOrder)
{
	std::cout << std::format("＜DebugCollisionDrawComponent＞ -> Constructor\n");

	// バッファ初期化
	InitDebugBuffers();

	this->Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
DebugCollisionDrawComponent::~DebugCollisionDrawComponent()
{
	std::cout << std::format("＜DebugCollisionDrawComponent＞ -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void DebugCollisionDrawComponent::Init()
{

}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void DebugCollisionDrawComponent::Uninit()
{
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void DebugCollisionDrawComponent::Update()
{
}

//--------------------------------------------------
// 描画処理
//--------------------------------------------------
void DebugCollisionDrawComponent::Draw()
{
	auto collider = owner_->GetComponent<BoxColliderComponent>();
	if (!collider) { return; }	// コライダーがない場合は描画しない


	const auto& box = collider->GetBoxSize();

	Color debugColor = collider->GetHitFg() ? Color(1, 0, 0, 1) : Color(0, 1, 0, 1);	// true == Red, false == Green
	float thickness = 20.0f;

	 // 四角形の各辺を描画
	DrawLine({ box.y, box.w }, { box.z, box.w }, debugColor, thickness); // 上辺
	DrawLine({ box.z, box.w }, { box.z, box.x }, debugColor, thickness); // 右辺
	DrawLine({ box.z, box.x }, { box.y, box.x }, debugColor, thickness); // 下辺
	DrawLine({ box.y, box.x }, { box.y, box.w }, debugColor, thickness); // 左辺
}





// 当たり判定の線を描画
void DebugCollisionDrawComponent::DrawLine(const Vector2& _start, const Vector2& _end, const Color& _color, const float& _thickness) {
	// 線の方向ベクトル
	DirectX::SimpleMath::Vector2 direction = _end - _start;
	direction.Normalize();

	// 垂直方向ベクトルを計算
	DirectX::SimpleMath::Vector2 perpendicular = { -direction.y, direction.x };

	// 線の四角形部分の頂点を計算
	DirectX::SimpleMath::Vector2 topLeft = _start + perpendicular * (_thickness / 2);
	DirectX::SimpleMath::Vector2 topRight = _end + perpendicular * (_thickness / 2);
	DirectX::SimpleMath::Vector2 bottomLeft = _start - perpendicular * (_thickness / 2);
	DirectX::SimpleMath::Vector2 bottomRight = _end - perpendicular * (_thickness / 2);



	index_buffer_.Create({ 0, 1, 2, 1, 3, 2 });


	shader_.SetGeometryGPU();
	vertex_buffer_.SetGPU();
	index_buffer_.SetGPU();


	// バッファをセット
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Renderer::GetDeviceContext()->DrawIndexed(6, 0, 0);
}



//--------------------------------------------------------------------------------------
// ジオメトリーシェーダを生成する
//--------------------------------------------------------------------------------------
bool CreateGeometryShader(ID3D11Device* device, ID3D11GeometryShader** geometryShader, ID3D11Buffer** constantBuffer) {
	// シェーダーバイナリをコンパイル
	ID3D10Blob* gsBlob = nullptr;
	HRESULT hr = D3DCompileFromFile(
		L"GeometryuShader.hlsl",
		nullptr, nullptr, "gs_main", "hs_5_0",
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &gsBlob, nullptr);
	assert(SUCCEEDED(hr));

	// ジオメトリシェーダを作成
	hr = device->CreateGeometryShader(gsBlob->GetBufferPointer(), gsBlob->GetBufferSize(), nullptr, geometryShader);
	assert(SUCCEEDED(hr));
	gsBlob->Release();

	// 定数バッファを作成
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(GeometryShaderBuffer);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = device->CreateBuffer(&bufferDesc, nullptr, constantBuffer);
	assert(SUCCEEDED(hr));
}
