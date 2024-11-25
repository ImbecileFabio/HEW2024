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

	//// 振り子の長さに合わせる
	//transform->SetPosition(Vector3(0, -rength_, 0));

	//// 角度を更新
	//angle_ += 0.1f;// ここの処理をいじって振り子の動きを作る
	//transform->SetRotation(Vector3(0, 0, angle_));


	//// SpriteComponentに渡すと計算の順番が違うので先にやっとく
	//auto r = transform->GetRotation();
	//auto t = transform->GetPosition();
	//auto s = transform->GetScale();
	//auto rot = Matrix::CreateFromYawPitchRoll(r.y, r.x, r.z);
	//auto pos = Matrix::CreateTranslation(t);
	//auto scale = Matrix::CreateScale(s);
	//
	//Matrix mtx;
	//mtx = scale * rot*pos;

	//// 行列から位置を抽出
	//transform->SetPosition(mtx.Translation());
	//
	//transform->SetRotation(Vector3(0, 0, 0));

}