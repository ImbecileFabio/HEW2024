////==================================================
//// [DebugPolygonComponent.h] ポリゴン描画コンポーネント
//// 著者：尾上莉奈
////--------------------------------------------------
//// 説明：Polygon描画
////==================================================
//#include "DebugPolygonComponent.h"
//#include "../../../GameManager.h"
//using namespace DirectX::SimpleMath;
////--------------------------------------------------
//// コンストラクタ
////--------------------------------------------------
//DebugPolygonComponent::DebugPolygonComponent(GameObject* _owner, int _drawOrder)
//	:RenderComponent(_owner, _drawOrder)
//{
//	// バッファ初期化
//	InitBuffers();
//
//	// 描画オブジェクトとして登録
//	this->owner_->GetGameManager()->GetRenderer()->AddSprite(this);
//}
////--------------------------------------------------
//// デストラクタ
////--------------------------------------------------
//DebugPolygonComponent::~DebugPolygonComponent()
//{
//}
////--------------------------------------------------
//// ポリゴン表示の初期化処理
////--------------------------------------------------
//void DebugPolygonComponent::Init(void)
//{
//}
////--------------------------------------------------
//// ポリゴン表示の終了処理
////--------------------------------------------------
//void DebugPolygonComponent::Uninit(void)
//{
//}
////--------------------------------------------------
//// ポリゴン表示の更新処理
////--------------------------------------------------
//void DebugPolygonComponent::Update(void)
//{
//}
//
//void DebugPolygonComponent::InitBuffers()
//{
//	// 頂点データ
//	std::vector<VERTEX_3D>	vertices;
//
//	vertices.resize(4);
//
//	vertices[0].position = Vector3(-0.5f, 0.5f, 0.5f);
//	vertices[1].position = Vector3(0.5f, 0.5f, 0.5f);
//	vertices[2].position = Vector3(-0.5f, -0.5f, 0.5f);
//	vertices[3].position = Vector3(0.5f, -0.5f, 0.5f);
//
//	vertices[0].color = Color(1, 1, 1, 1);
//	vertices[1].color = Color(1, 1, 1, 1);
//	vertices[2].color = Color(1, 1, 1, 1);
//	vertices[3].color = Color(1, 1, 1, 1);
//
//	vertices[0].uv = Vector2(0, 0);
//	vertices[1].uv = Vector2(1, 0);
//	vertices[2].uv = Vector2(0, 1);
//	vertices[3].uv = Vector2(1, 1);
//
//	// 頂点バッファ生成
//	vertex_buffer_.Create(vertices);
//
//	// インデックスバッファ生成
//	std::vector<unsigned int> indices;
//	indices.resize(4);
//
//	indices[0] = 0;
//	indices[1] = 1;
//	indices[2] = 2;
//	indices[3] = 3;
//
//	// インデックスバッファ生成
//	index_buffer_.Create(indices);
//
//	// シェーダオブジェクト生成
//	shader_.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");
//}
//
