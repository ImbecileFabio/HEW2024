//==================================================
// [TransformComponent.cpp] 姿勢制御コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：姿勢制御コンポーネント
//==================================================

/*----- インクルード -----*/
#include "../GameObject.h"
#include "../Component.h"
#include "TransformComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
TransformComponent::TransformComponent(std::shared_ptr<GameObject> _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	SetPosition(DirectX::SimpleMath::Vector3(0.f, 0.f, 0.f));
	SetRotation(DirectX::SimpleMath::Vector3(0.f, 0.f, 0.f));
	SetScale(DirectX::SimpleMath::Vector3(1.f, 1.f, 1.f));

}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
TransformComponent::~TransformComponent()
{
	std::cout << "＜TransformComponent＞ -> 破棄\n";

}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void TransformComponent::Init(void)
{
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void TransformComponent::Uninit(void)
{
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void TransformComponent::Update(void)
{

}

