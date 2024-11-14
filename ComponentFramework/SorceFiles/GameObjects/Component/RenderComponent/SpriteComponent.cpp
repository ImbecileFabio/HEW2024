//==================================================
// [SpriteComponent.h] 描画コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：とても描画コンポーネントの宣言
//==================================================

/*----- インクルード -----*/
#include "../../../StdAfx.h"
#include "SpriteComponent.h"
#include "../../../GameManager.h"
#include "../../../Renderer.h"
#include "../../../SubSystem/dx11helper.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"

#include <wrl/client.h>
using namespace DirectX::SimpleMath;

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
SpriteComponent::SpriteComponent(std::shared_ptr<GameObject> _owner,const std::string _imgname,  int _drawOrder)
	: RenderComponent(_owner)
	, draw_order_(_drawOrder)
{

	// テクスチャ読み込み
	bool sts = texture_.Load(_imgname);
	assert(sts == true);

	// バッファ初期化
	InitBuffers();

	GetOwner()->GetGameManager()->GetRenderer()->AddSprite(this);

	object_name_ = std::string("不明なオブジェクト");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
SpriteComponent::~SpriteComponent()
{
	std::cout << "＜SpriteComponent＞ -> 破棄\n";

	Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void SpriteComponent::Init()
{

}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void SpriteComponent::Uninit()
{
}

//--------------------------------------------------
// バッファ初期化
//--------------------------------------------------
void SpriteComponent::InitBuffers()
{
	// 頂点データ
	std::vector<VERTEX_3D>	vertices;

	vertices.resize(4);

	vertices[0].position = Vector3(-10, 10, 0);
	vertices[1].position = Vector3(10, 10, 0);
	vertices[2].position = Vector3(-10, -10, 0);
	vertices[3].position = Vector3(10, -10, 0);

	vertices[0].color = Color(1, 1, 1, 1);
	vertices[1].color = Color(1, 1, 1, 1);
	vertices[2].color = Color(1, 1, 1, 1);
	vertices[3].color = Color(1, 1, 1, 1);

	vertices[0].uv = Vector2(0, 0);
	vertices[1].uv = Vector2(1, 0);
	vertices[2].uv = Vector2(0, 1);
	vertices[3].uv = Vector2(1, 1);

	// 頂点バッファ生成
	vertex_buffer_.Create(vertices);

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
// 名前を定義する処理
//--------------------------------------------------
void SpriteComponent::SetObjectName(std::string _objectName)
{
	object_name_ = _objectName;
}


//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void SpriteComponent::Update()
{
}

//--------------------------------------------------
// 描画処理
//--------------------------------------------------
void SpriteComponent::Draw()
{
	Matrix rot;
	Matrix pos;
	Matrix scale;
	
	TransformComponent* transform = GetOwner()->GetComponent<TransformComponent>();
	if (transform)
	{
		auto t = transform->GetPosition();
		auto r = transform->GetRotation();
		auto s = transform->GetScale();
		rot = Matrix::CreateFromYawPitchRoll(r.y, r.x, r.z);
		pos = Matrix::CreateTranslation(t);
		scale = Matrix::CreateScale(s);
	}
	else 
	{
		std::cout << "<" + object_name_ + "> -> 位置取得失敗\n";
		rot = Matrix::CreateFromYawPitchRoll(0.f, 0.f, 0.f);
		pos = Matrix::CreateTranslation(0.f, 0.f, 0.f);
		scale = Matrix::CreateScale(10.f, 10.f, 1.f);
	}
	
	Matrix worldmtx;
	worldmtx = scale * rot * pos;
	Renderer::SetWorldMatrix(&worldmtx); // GPUにセット

	// 描画の処理
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();

	// トポロジーをセット（プリミティブタイプ）
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	shader_.SetGPU();
	vertex_buffer_.SetGPU();
	index_buffer_.SetGPU();

	texture_.SetGPU();

	devicecontext->DrawIndexed(
		4,							// 描画するインデックス数（四角形なんで４）
		0,							// 最初のインデックスバッファの位置
		0);
}

