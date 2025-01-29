//==================================================
// [DebugColliderDrawComponent.h] 描画コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：とても描画コンポーネントの宣言
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>
#include <string>

#include "DebugColliderDrawComponent.h"
#include "../../../GameManager.h"
#include "../../../Renderer.h"
#include "../../../SubSystem/dx11helper.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"
#include "../ColliderComponent/BoxColliderComponent.h"


#include <wrl/client.h>

using namespace DirectX::SimpleMath;




//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
DebugColliderDrawComponent::DebugColliderDrawComponent(GameObject* _owner, int _drawOrder)
	: RenderComponent(_owner, _drawOrder)
{
	// バッファ初期化
	this->InitDebugBuffers();
	this->Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
DebugColliderDrawComponent::~DebugColliderDrawComponent()
{
	Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void DebugColliderDrawComponent::Init()
{

}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void DebugColliderDrawComponent::Uninit()
{
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void DebugColliderDrawComponent::Update()
{
}

//--------------------------------------------------
// 描画処理
//--------------------------------------------------
void DebugColliderDrawComponent::Draw()
{
	auto collider = owner_->GetComponent<ColliderBaseComponent>();
	if (collider && collider->GetComponentType() == TypeID::BoxColliderComponent)
	{
		auto boxCollider = static_cast<BoxColliderComponent*>(collider);

		Matrix rot;
		Matrix pos;
		Matrix scale;

		auto transform = owner_->GetTransformComponent();
		if (transform)
		{
			auto si = boxCollider->GetSize();
			auto t = transform->GetPosition();
			auto r = transform->GetRotation();
			auto sc = transform->GetScale();

			auto finalSize = Vector3(si * sc);	// 最終的なサイズ


			rot = Matrix::CreateFromYawPitchRoll(r.x, r.y, r.z);
			pos = Matrix::CreateTranslation(t);
			scale = Matrix::CreateScale(finalSize);
		}
		else
		{
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

		devicecontext->DrawIndexed(
			4,							// 描画するインデックス数（四角形なんで４）
			0,							// 最初のインデックスバッファの位置
			0);
	}
}



//--------------------------------------------------
// デバッグ用のバッファ初期化
//--------------------------------------------------
void DebugColliderDrawComponent::InitDebugBuffers()
{
	// 頂点データ
	vertices_.resize(4);

	vertices_[0].position = Vector3(-0.5f, 0.5f, 0);
	vertices_[1].position = Vector3(0.5f, 0.5f, 0);
	vertices_[2].position = Vector3(-0.5f, -0.5f, 0);
	vertices_[3].position = Vector3(0.5f, -0.5f, 0);


	vertices_[0].color = Color(1.0f, 0.0f, 0.0f, 0.1f);
	vertices_[1].color = Color(1.0f, 0.0f, 0.0f, 0.1f);
	vertices_[2].color = Color(1.0f, 0.0f, 0.0f, 0.1f);
	vertices_[3].color = Color(1.0f, 0.0f, 0.0f, 0.1f);

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
	shader_.Create(
		"shader/drawColliderVS.hlsl",
		"shader/drawColliderPS.hlsl");
}