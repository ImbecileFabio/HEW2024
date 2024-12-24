//==================================================
// [RenderComponent.cpp] 描画モジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：描画処理の定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>

#include "../../GameManager.h"
#include "../../Renderer.h"
#include "../GameObject.h"
#include "RenderComponent.h"
#include "ColliderComponent/BoxColliderComponent.h"

#include "../Component.h"

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
RenderComponent::RenderComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
	, draw_order_(_updateOrder)
{
	std::cout << std::format("＜RenderComponent＞ -> Constructor\n");

	// 描画オブジェクトとして登録
	this->owner_->GetGameManager()->GetRenderer()->AddSprite(this);

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
RenderComponent::~RenderComponent(void)
{
	std::cout << std::format("＜RenderComponent＞ -> Destructor\n");

	// 描画オブジェクトとして登録解除
	this->owner_->GetGameManager()->GetRenderer()->RemoveSprite(this);



}
//--------------------------------------------------
// UV座標の変更
//--------------------------------------------------
void RenderComponent::SetUV(const DirectX::SimpleMath::Vector2& _uv)
{
	vertices_[0].uv = _uv;
	vertices_[1].uv = Vector2(_uv.x , _uv.y);
	vertices_[2].uv = Vector2(_uv.x, _uv.y + 1);
	vertices_[3].uv = Vector2(_uv.x + 1, _uv.y + 1);

	vertex_buffer_.Modify(vertices_);
}

//--------------------------------------------------
// バッファ初期化
//--------------------------------------------------
void RenderComponent::InitBuffers()
{
	// 頂点データ

	vertices_.resize(4);

	vertices_[0].position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices_[1].position = Vector3(0.5f, 0.5f, 0.0f);
	vertices_[2].position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices_[3].position = Vector3(0.5f, -0.5f, 0.0f);

	vertices_[0].color = Color(1, 1, 1, 1);
	vertices_[1].color = Color(1, 1, 1, 1);
	vertices_[2].color = Color(1, 1, 1, 1);
	vertices_[3].color = Color(1, 1, 1, 1);

	vertices_[0].uv = Vector2(0, 0);
	vertices_[1].uv = Vector2(1, 0);
	vertices_[2].uv = Vector2(0, 1);
	vertices_[3].uv = Vector2(1, 1);

	// 頂点バッファ生成
	vertex_buffer_.Create(vertices_);

	// インデックスバッファ生成
	std::vector<unsigned int> indices;
	indices.resize(4);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	// インデックスバッファ生成
	index_buffer_.Create(indices);

	// シェーダオブジェクト生成
	shader_.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");

}

//--------------------------------------------------
// デバッグ用のバッファ初期化
//--------------------------------------------------
void RenderComponent::InitGeometryBuffers()
{
	auto collider = owner_->GetComponent<BoxColliderComponent>();
	if (!collider) { return; }	// コライダーがない

	const auto& box = collider->GetBoxSize();


	// 中心座標
	Vector2 pos =
	{
		(box.x + box.z) * 0.5f,
		(box.w - box.y) * 0.5f
	};

	Vector2 size =
	{
		box.z - box.x,	// 幅
		box.y - box.w 	// 高さ
	};

	GeometryShaderBuffer gsBuffer;
	gsBuffer.position = pos;
	gsBuffer.color = Color(1.0f, 0.0f, 0.0f, 1.0f);	// 赤色
	gsBuffer.thickness = 2.0f;



	constant_buffer_.Create(std::vector<GeometryShaderBuffer>{gsBuffer});

	shader_.CreateGeometry("shader/GeometryShader.hlsl");

}

