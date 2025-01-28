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

#include "../TransformComponent.h"
#include "AnimationComponent.h"

#include "../../GameObject.h"

#include <wrl/client.h>
using namespace DirectX::SimpleMath;

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
SpriteComponent::SpriteComponent(GameObject* _owner, const std::string _imgname, int _drawOrder)
	: RenderComponent(_owner, _drawOrder)
{
	std::cout << std::format("＜SpriteComponent＞ -> Constructor\n");
	
	// テクスチャ取得
	texture_ = TextureManager::GetInstance().GetTexture(_imgname);
	if (!texture_)
	{
		std::cerr << std::format("＜SpriteComponent＞ -> Failed to get texture : {}\n", _imgname);
		return;
	}
	// バッファ初期化
	this->InitBuffers(texture_->GetCutU(), texture_->GetCutV());	// 画像の分割数を渡す

	this->Init();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
SpriteComponent::~SpriteComponent()
{
	std::cout << std::format("＜SpriteComponent＞ -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SpriteComponent::Init()
{

}

//--------------------------------------------------
// @brief 終了処理
//--------------------------------------------------
void SpriteComponent::Uninit()
{
}


//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SpriteComponent::Update()
{
}

//--------------------------------------------------
// @brief 描画処理
//--------------------------------------------------
void SpriteComponent::Draw()
{
	Matrix rot;
	Matrix pos;
	Matrix scale;
	
	if(owner_)
	{
		auto transform = owner_->GetTransformComponent();
		if (transform)
		{
			auto si = transform->GetSize();
			auto t = transform->GetPosition();
			auto r = transform->GetRotation();
			auto sc = transform->GetScale();

			auto offsetPos = texture_->GetOffsetPos();	// オフセットポジション
			auto offsetSize = texture_->GetOffsetSize();	// オフセットサイズ

			Vector3 finalPos = { t.x + offsetPos.x, t.y + offsetPos.y, t.z };	// 最終的な位置
			Vector3 finalSize = { (si.x * offsetSize.x) * sc.x,  (si.y * offsetSize.y) * sc.y, si.z * si.z };	// 最終的なサイズ


			rot = Matrix::CreateFromYawPitchRoll(r.x, r.y, r.z);
			pos = Matrix::CreateTranslation(finalPos);
			scale = Matrix::CreateScale(finalSize);
		}
	}
	else 
	{
		std::cout << std::format("＜SpriteComponent＞ -> default position\n");
		rot = Matrix::CreateFromYawPitchRoll(0.0f, 0.0f, 0.0f);
		pos = Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
		scale = Matrix::CreateScale(1.0f, 1.0f, 1.0f);
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



	// 情報をGPUにセット
	shader_.SetGPU();
	vertex_buffer_.Modify(vertices_);	// バッファの更新
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
	auto frameSize = texture_->GetFrameSize();
	
	current_uv_ = _uv;
	Vector2 uvMin = { current_uv_.x, current_uv_.y };
	Vector2 uvMax = { current_uv_.x + frameSize.x, current_uv_.y + frameSize.y };


	vertices_[0].uv = { (x_flip_ ? uvMax.x : uvMin.x), (y_flip_ ? uvMax.y : uvMin.y)};
	vertices_[1].uv = { (x_flip_ ? uvMin.x : uvMax.x), (y_flip_ ? uvMax.y : uvMin.y)};
	vertices_[2].uv = { (x_flip_ ? uvMax.x : uvMin.x), (y_flip_ ? uvMin.y : uvMax.y)};
	vertices_[3].uv = { (x_flip_ ? uvMin.x : uvMax.x), (y_flip_ ? uvMin.y : uvMax.y)};
}
void SpriteComponent::SetUV()
{
	auto frameSize = texture_->GetFrameSize();

	Vector2 uvMin = current_uv_;
	Vector2 uvMax = { current_uv_.x + frameSize.x, current_uv_.y + frameSize.y };

	vertices_[0].uv = { (x_flip_ ? uvMax.x : uvMin.x), (y_flip_ ? uvMax.y : uvMin.y) };
	vertices_[1].uv = { (x_flip_ ? uvMin.x : uvMax.x), (y_flip_ ? uvMax.y : uvMin.y) };
	vertices_[2].uv = { (x_flip_ ? uvMax.x : uvMin.x), (y_flip_ ? uvMin.y : uvMax.y) };
	vertices_[3].uv = { (x_flip_ ? uvMin.x : uvMax.x), (y_flip_ ? uvMin.y : uvMax.y) };
}



//--------------------------------------------------
// @brief テクスチャ変更
//--------------------------------------------------
void SpriteComponent::SetTexture(const std::string _imgname)
{
	auto newTexture = TextureManager::GetInstance().GetTexture(_imgname);

	// 同じテクスチャなら何もしない
	if (texture_ == newTexture) return;

	// 分割数が違う時だけバッファを再初期化
	if (texture_->GetCutU() != newTexture->GetCutU() || texture_->GetCutU() != newTexture->GetCutV())
	{
		this->InitBuffers(newTexture->GetCutU(), newTexture->GetCutV());	// 画像の分割数を渡す
	}
	// テクスチャを変更
	texture_ = newTexture;

	// オーナーがアニメーションコンポーネントを持っているなら
	if (auto anmComp = owner_->GetComponent<AnimationComponent>())
	{
		anmComp->ResetAnimation();	// アニメーションをリセット
	}
}

//--------------------------------------------------
// @brief 色変更
//--------------------------------------------------
void SpriteComponent::SetColor(const DirectX::SimpleMath::Vector4& _color)
{
	for (auto& vertex : vertices_)
	{
		vertex.color = _color;		// 色を変更
	}
}


//--------------------------------------------------
// @param _xFlip X軸反転, _yFlip Y軸反転
// @brief 画像反転
//--------------------------------------------------
void SpriteComponent::SetFlip(bool _xFlip, bool _yFlip)
{
	x_flip_ = _xFlip;
	y_flip_ = _yFlip;

	// UV座標を変更
	this->SetUV();
}


