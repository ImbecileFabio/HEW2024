//==================================================
// [RenderComponent.cpp] 描画モジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：描画処理の定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>

#include "../../../GameManager.h"
#include "../../../Renderer.h"
#include "../../GameObject.h"
#include "RenderComponent.h"
#include "../ColliderComponent/BoxColliderComponent.h"

#include "../../Component.h"

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
	if (owner_) { owner_->GetGameManager()->GetRenderer()->AddSprite(this); }

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
RenderComponent::~RenderComponent(void)
{
	std::cout << std::format("＜RenderComponent＞ -> Destructor\n");

	// 描画オブジェクトとして登録解除
	if (owner_) { this->owner_->GetGameManager()->GetRenderer()->RemoveSprite(this); }



}
//--------------------------------------------------
// バッファ初期化
//--------------------------------------------------
void RenderComponent::InitBuffers(float _cutU, float _cutV)
{
	// 頂点データ

	vertices_.resize(4);

	vertices_[0].position = Vector3(-0.5f, 0.5f,  0.0f);
	vertices_[1].position = Vector3(0.5f, 0.5f,   0.0f);
	vertices_[2].position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices_[3].position = Vector3(0.5f, -0.5f,  0.0f);

	vertices_[0].color = Color(1, 1, 1, 1);
	vertices_[1].color = Color(1, 1, 1, 1);
	vertices_[2].color = Color(1, 1, 1, 1);
	vertices_[3].color = Color(1, 1, 1, 1);

	vertices_[0].uv = Vector2(0.0f,         0.0f        );
	vertices_[1].uv = Vector2(1.0f / _cutU, 0.0f        );
	vertices_[2].uv = Vector2(0.0f,         1.0f / _cutV);
	vertices_[3].uv = Vector2(1.0f / _cutU, 1.0f / _cutV);

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

	// マテリアル情報取得
	material_ = std::make_unique<Material>();
	MATERIAL mtrl;
	mtrl.Diffuse = Color(1, 1, 1, 1);
	mtrl.Shiness = 1;
	mtrl.TextureEnable = true; // テクスチャを使うか否かのフラグ
	material_->Create(mtrl);

}

void  RenderComponent::SetVertexBuffer(std::vector<VERTEX_3D> _vertices)
{
	vertices_ = _vertices; 
	vertex_buffer_.Modify(vertices_);
}