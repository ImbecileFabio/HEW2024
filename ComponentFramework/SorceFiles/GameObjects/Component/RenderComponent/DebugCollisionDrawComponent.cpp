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

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
DebugCollisionDrawComponent::DebugCollisionDrawComponent(GameObject* _owner, int _drawOrder)
	: RenderComponent(_owner, _drawOrder)
{
	std::cout << std::format("＜DebugCollisionDrawComponent＞ -> Constructor\n");

	// バッファ初期化
	InitBuffers();

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
	auto transform = owner_->GetComponent<TransformComponent>();


	// 描画オブジェクトとして登録
	this->owner_->GetGameManager()->GetRenderer()->AddSprite(this);

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
	float thickness = 2.0f;

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



	shader_.SetGPU();
	vertex_buffer_.SetGPU();
	index_buffer_.SetGPU();


	// バッファをセット
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Renderer::GetDeviceContext()->DrawIndexed(6, 0, 0);
}