//==================================================
// [SpriteComponent.h] 描画コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：とても描画コンポーネントの宣言
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>
#include <cassert>
#include <string>

#include "SpriteComponent.h"
#include "../../../GameManager.h"
#include "../../../SubSystem/dx11helper.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"

#include <wrl/client.h>
using namespace DirectX::SimpleMath;

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
SpriteComponent::SpriteComponent(GameObject* _owner,const std::string _imgname,  int _drawOrder)
	: RenderComponent(_owner, _drawOrder)
{
	std::cout << std::format("＜SpriteComponent＞ -> Constructor\n");

	// テクスチャ読み込み
	bool sts = texture_.Load(_imgname);
	assert(sts == true);

	// バッファ初期化
	this->InitBuffers();

	this->Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
SpriteComponent::~SpriteComponent()
{
	std::cout << std::format("＜SpriteComponent＞ -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void SpriteComponent::Init()
{
	auto transform = owner_->GetComponent<TransformComponent>();
	if (transform)
	{
		transform->SetScale(150, 150);
	}


	// 描画オブジェクトとして登録
	this->owner_->GetGameManager()->GetRenderer()->AddSprite(this);

}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------

void SpriteComponent::Uninit()
{
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
	
	auto transform = owner_->GetComponent<TransformComponent>();
	if (transform)
	{
		auto t = transform->GetPosition();
		auto r = transform->GetRotation();
		auto s = transform->GetScale();
		rot = Matrix::CreateFromYawPitchRoll(r.x, r.y, r.z);
		pos = Matrix::CreateTranslation(t);
		scale = Matrix::CreateScale(s);
	}
	else 
	{
		std::cout << std::format("＜SpriteComponent＞ -> default position\n");
		rot = Matrix::CreateFromYawPitchRoll(0.f, 0.f, 0.f);
		pos = Matrix::CreateTranslation(0.f, 0.f, 0.f);
		scale = Matrix::CreateScale(1.f, 1.f, 1.f);
	}



	Matrix worldmtx;
	worldmtx = scale * rot * pos;
	Renderer::SetWorldMatrix(&worldmtx); // GPUにセット

	// 描画の処理
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();
	assert(devicecontext);

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

//--------------------------------------------------
// 色変更
//--------------------------------------------------
void SpriteComponent::SetColor(const DirectX::SimpleMath::Vector4& _color)
{
	for (auto& vertex : vertices_)
	{
		vertex.color = _color;		// 色を変更
	}

	vertex_buffer_.Modify(vertices_);	// バッファを書き換え
}

