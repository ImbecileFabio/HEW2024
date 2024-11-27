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
	std::cout << std::format("＜PendulumComponent＞ -> Constructor\n");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
PendulumComponent::~PendulumComponent(void)
{
	std::cout << std::format("＜PendulumComponent＞ -> Destructor\n");

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

	auto transform = owner_->GetComponent<TransformComponent>();

	// 振り子の長さに合わせる
	transform->SetPosition(0, -rength_);

	// 角度を更新
	angle_ += 0.1f;// ここの処理をいじって振り子の動きを作る
	transform->SetRotation(angle_);


	// SpriteComponentに渡すと計算の順番が違うので先にやっとく
	auto r = transform->GetRotation();
	auto t = transform->GetPosition();
	auto s = transform->GetScale();
	auto rot = Matrix::CreateFromYawPitchRoll(r.y, r.x, r.z);
	auto pos = Matrix::CreateTranslation(t);
	auto scale = Matrix::CreateScale(s);
	
	Matrix mtx;
	mtx = scale * pos * rot;

	// 行列から位置を抽出
	auto mtxPos = mtx.Translation();
	transform->SetPosition(mtxPos.x, mtxPos.y);
	
	transform->SetRotation(0);

}