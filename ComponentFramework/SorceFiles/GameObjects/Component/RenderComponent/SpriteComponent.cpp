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
SpriteComponent::SpriteComponent(GameObject* _owner,const std::string _imgname,  int _drawOrder)
	: RenderComponent(_owner)
	, draw_order_(_drawOrder)
{
	InitBuffers();

	// テクスチャ読み込み
	bool sts = texture_.Load(_imgname);
	assert(sts == true);

	this->owner_->GetGameManager()->GetRenderer()->AddSprite(this);

	object_name_ = std::string("不明なオブジェクト");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
SpriteComponent::~SpriteComponent(void)
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
// 名前を定義する関数
//--------------------------------------------------
void SpriteComponent::SetObjectName(std::string _objectName)
{
	object_name_ = _objectName;
}

void SpriteComponent::Draw(void)
{
	std::cout << "＜" + object_name_ + "＞ -> 描画\n";

	Matrix r;
	Matrix t;
	Matrix s;

	GameObject* gameObject = GetOwner();
	TransformComponent* transform = gameObject->GetComponent<TransformComponent>();
	if (transform)
	{
		// SRT情報作成
		r = Matrix::CreateFromYawPitchRoll(transform->GetRotation());

		t = Matrix::CreateTranslation(
			transform_->position_.x,
			transform_.position_.y,
			transform_.position_.z);

		s = Matrix::CreateScale(
			transform_.scale_.x,
			transform_.scale_.y,
			transform_.scale_.z);


	}
	else 
	{
		r = Matrix::CreateFromYawPitchRoll(0.f, 0.f, 0.f);
		t = Matrix::CreateTranslation(0.f, 0.f, 0.f);
		s = Matrix::CreateScale(1.f, 1.f, 1.f);
	}
	
	Matrix worldmtx;
	worldmtx = s * r * t;
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
