//==================================================
// [Lift.cpp] リフトファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：リフトオブジェクト
//==================================================
/*----- インクルード -----*/
#include <algorithm>
#include "Lift.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
// @param _maxPos 正方向の最大座標
// @param _minPos 負方向の最大座標
// @param _gameManager オブジェクトを所持しているマネージャー
//--------------------------------------------------
Lift::Lift(MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameManager* _gameManager)
	:GameObject(_gameManager, "Lift")
	,moveState_(_moveState), maxPos_(_maxPos), minPos_(_minPos), switchFg_(false)
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
Lift::~Lift()
{
	delete spriteComponent_;
	delete velocityComponent_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void Lift::InitGameObject(void)
{
	this->spriteComponent_   = new SpriteComponent(this, TEXTURE_PATH_"gimmick/lift/v01/lift_LR_01.png", 0);
	this->velocityComponent_ = new VelocityComponent(this);

	this->transform_component_->SetScale(300.0f, 300.0f);
	this->transform_component_->SetPosition(-50.0f, 0.0f);

	this->velocityComponent_->SetUseGravity(false);
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void Lift::UpdateGameObject(void)
{
	DirectX::SimpleMath::Vector3 pos = this->transform_component_->GetPosition();
	DirectX::SimpleMath::Vector3 current_acceleration = velocityComponent_->GetAcceleration();

	switch (moveState_)
	{
	case Lift::MoveState::length:	// 縦移動
		break;
	case Lift::MoveState::side:		// 横移動
	{
		if (pos.x < maxPos_.x && switchFg_ == false)
		{
			velocityComponent_->SetAcceleration({ 0.1f, 0.0f, 0.0f });
			if (pos.x >= maxPos_.x)
				switchFg_ = true;
		}
		if (pos.x > minPos_.x && switchFg_ == true)
		{
			velocityComponent_->SetAcceleration({ -0.1f, 0.0f, 0.0f });
			if (pos.x <= minPos_.x)
				switchFg_ = false;
		}
		// 加速度の絶対値を減速率に基づいて減少させる
		if (current_acceleration.x > 0.0f)
		{
			current_acceleration.x =
				max( 0.0f , current_acceleration.x - 0.01f );
		}
		else if (current_acceleration.x < 0.0f)
		{
			current_acceleration.x =
				min(0.0f , current_acceleration.x + 0.01f );
		}
		velocityComponent_->SetAcceleration(current_acceleration);
		break;
	}
	default:
		break;
	}
	this->transform_component_->SetPosition(pos);
}
//if (pos.x < maxPos_.x && switchFg_ == false)
//{
//	pos.x += 2.0f;
//	if (pos.x >= maxPos_.x)
//	{
//		switchFg_ = true;
//	}
//}
//if (pos.x > minPos_.x && switchFg_ == true)
//{
//	pos.x -= 2.0f;
//	if (pos.x <= minPos_.x)
//	{
//		switchFg_ = false;
//	}
//}