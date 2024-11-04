//==================================================
// [VertexComponent.h] 
// 著者：有馬啓太
//--------------------------------------------------
// 説明：
//==================================================


/*----- インクルード -----*/
#include "../../StdAfx.h"
#include "VertexComponent.h"

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
VertexComponent::VertexComponent(GameObject* owner, int updateOrder)
	:Component(owner, updateOrder)
{
}
	

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
VertexComponent::~VertexComponent(void)
{
}

//=======================================
//初期化処理
//=======================================
void VertexComponent::Init()
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
	vertex_buffer_.Create(vertices);
}
