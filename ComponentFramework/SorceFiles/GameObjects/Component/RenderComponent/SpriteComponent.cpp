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
#include "../../../TextureManager.h"
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
	
	// テクスチャ取得
	texture_ = TextureManager::GetInstance().GetTexture(_imgname);

	// バッファ初期化
	this->InitBuffers(texture_->GetCutU(), texture_->GetCutV());	// 画像の分割数を渡す

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
	
	auto transform = owner_->GetTransformComponent();
	if (transform)
	{
		auto si = transform->GetSize();
		auto t  = transform->GetPosition();
		auto r  = transform->GetRotation();
		auto sc = transform->GetScale();

		auto finalSize = Vector3(si * sc);	// 最終的なサイズ


		rot = Matrix::CreateFromYawPitchRoll(r.x, r.y, r.z);
		pos = Matrix::CreateTranslation(t);
		scale = Matrix::CreateScale(finalSize);
	}
	else 
	{
		std::cout << std::format("＜SpriteComponent＞ -> default position\n");
		rot = Matrix::CreateFromYawPitchRoll(0.0f, 0.0f, 0.0f);
		pos = Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
		scale = Matrix::CreateScale(100.0f, 100.0f, 100.0f);
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

	texture_->SetGPU();
	material_->SetGPU();

	devicecontext->DrawIndexed(
		4,							// 描画するインデックス数（四角形なんで４）
		0,							// 最初のインデックスバッファの位置
		0);
}

void SpriteComponent::SetUV(const DirectX::SimpleMath::Vector2& _uv)
{
	float cutU = texture_.get()->GetCutU();
	float cutV = texture_.get()->GetCutV();

	vertices_[0].uv = Vector2(_uv.x / cutU, _uv.y / cutV);
	vertices_[1].uv = Vector2((_uv.x + 1.0f) / cutU, _uv.y / cutV);
	vertices_[2].uv = Vector2(_uv.x / cutU, (_uv.y + 1.0f) / cutV);
	vertices_[3].uv = Vector2((_uv.x + 1.0f) / cutU, (_uv.y + 1.0f) / cutV);

	vertex_buffer_.Modify(vertices_);

}


void SpriteComponent::SetTexture(const std::string _imgname)
{
	texture_ = TextureManager::GetInstance().GetTexture(_imgname);
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


