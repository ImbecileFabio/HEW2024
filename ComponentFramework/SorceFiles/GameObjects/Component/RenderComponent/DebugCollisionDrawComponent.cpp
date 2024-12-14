//==================================================
// [DebugCollisionDrawComponent.h] 描画コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：とても描画コンポーネントの宣言
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>
#include <string>

#include "DebugCollisionDrawComponent.h"
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
DebugCollisionDrawComponent::DebugCollisionDrawComponent(GameObject* _owner, int _drawOrder)
	: RenderComponent(_owner, _drawOrder)
{
	std::cout << std::format("＜DebugCollisionDrawComponent＞ -> Constructor\n");

	// バッファ初期化
	InitGeometryBuffers();

	this->Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
DebugCollisionDrawComponent::~DebugCollisionDrawComponent()
{
	std::cout << std::format("＜DebugCollisionDrawComponent＞ -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void DebugCollisionDrawComponent::Init()
{


}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void DebugCollisionDrawComponent::Uninit()
{
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void DebugCollisionDrawComponent::Update()
{
}

//--------------------------------------------------
// 描画処理
//--------------------------------------------------
void DebugCollisionDrawComponent::Draw()
{

	auto devicecontext = Renderer::GetDeviceContext();

	shader_.SetGeometryGPU();
	constant_buffer_.SetGPU();


	// トポロジーをポイントリストに設定
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// 描画
	devicecontext->Draw(1, 0);
}








