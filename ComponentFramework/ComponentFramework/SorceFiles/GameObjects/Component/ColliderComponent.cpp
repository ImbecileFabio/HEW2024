//==================================================
// [ColliderComponent.h] コライダーのベース
// 著者：有馬啓太
//--------------------------------------------------
// 説明：だそうです
//==================================================


/*----- インクルード -----*/
#include "../../StdAfx.h"
#include "ColliderComponent.h"

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
ColliderComponent::ColliderComponent(GameObject* owner, int updateOrder)
	:Component(owner, updateOrder)
{
}
	

//--------------------------------------------------
// コライダーコンポーネント
//--------------------------------------------------
ColliderComponent::~ColliderComponent(void)
{
}

//=======================================
//初期化処理
//=======================================
void ColliderComponent::Init()
{
	// 頂点データ
	std::vector<VERTEX_3D>	vertices;

	vertices.resize(4);

	vertices[0].position = Vector3(-10, 0, 10);
	vertices[1].position = Vector3(10, 0, 10);
	vertices[2].position = Vector3(-10, 0, -10);
	vertices[3].position = Vector3(10, 0, -10);

	vertices[0].color = Color(1, 1, 1, 1);
	vertices[1].color = Color(1, 1, 1, 1);
	vertices[2].color = Color(1, 1, 1, 1);
	vertices[3].color = Color(1, 1, 1, 1);

	vertices[0].uv = Vector2(0, 0);
	vertices[1].uv = Vector2(0, 0);
	vertices[2].uv = Vector2(0, 0);
	vertices[3].uv = Vector2(0, 0);

	// 頂点バッファ生成
	m_VertexBuffer.Create(vertices);

	// インデックスバッファ生成
	std::vector<unsigned int> indices;
	indices.resize(4);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	// インデックスバッファ生成
	m_IndexBuffer.Create(indices);

}
