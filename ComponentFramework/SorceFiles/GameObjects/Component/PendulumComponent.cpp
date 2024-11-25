//==================================================
// [PendulumComponent.cpp] 振り子モジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：振り子の処理の定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>
#include <SimpleMath.h>


#include "PendulumComponent.h"
#include "../GameObject.h"
#include "../Component.h"

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
PendulumComponent::PendulumComponent(GameObject* _owner, float _rength, float _angle, int _updateOrder)
	: Component(_owner, _updateOrder)
	, rength_(_rength)
	, angle_(_angle)
{
	std::format("＜PendulumComponent＞ -> Constructor\n");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
PendulumComponent::~PendulumComponent(void)
{
	std::format("＜PendulumComponent＞ -> Destructor\n");

}


//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void PendulumComponent::Uninit()
{
}


//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void PendulumComponent::Update(void)
{

	auto& transform = owner_->GetTransformComponent();

	transform->position_.y = -rength_;
	transform->rotation_.z += 0.1f;
}