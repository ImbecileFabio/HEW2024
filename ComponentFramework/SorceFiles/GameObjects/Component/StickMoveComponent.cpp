//==================================================
// [StickMoveComponent.cpp] 振り子の棒の動きコンポーネント
// 著者：HOGE太郎
//--------------------------------------------------
// 説明：振り子の棒の動きコンポーネントの定義
//==================================================
/*----- インクルード -----*/
#include "StickMoveComponent.h"
#include "../GameObject.h"
#include <iostream>

#define PI 3.14f

constexpr float normalLangth = 250.0f;
constexpr float langthChange = 50.0f;
constexpr float pendulumAcceleration = 0.1f;
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
StickMoveComponent::StickMoveComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
	, stickPosition_{}
	, isStickAngle_{ 0 }
	, wasStickAngle_{ 0 }
	, isStickVelocity_{ 0 }
	, wasStickVelocity_{ 0 }
	, stickAcceleration_{ 0 }
	, fulcrumPosition_{}
	, stickLength_{ 0 }
	, stickRadian_{ 0 }
	, turnStick_{ true }
	, maxStickAngle_{ 0 }
	, maxStickVelocity_{ 0 }
	, stickMovement_{ false }
	, pendulum_transform_component_{}
{
	std::cout << std::format("＜StickMoveComponent＞ -> Constructor\n");
	this->Init();
}


//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
StickMoveComponent::~StickMoveComponent()
{
	std::cout << std::format("＜StickMoveComponent＞ -> Destructor\n");
	this->Uninit();
}

//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void StickMoveComponent::Init()
{
}
//--------------------------------------------------
// @brief 終了処理
//--------------------------------------------------
void StickMoveComponent::Uninit()
{

}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void StickMoveComponent::Update()
{
	// 振り子の状態遷移
	switch (lengthState_)
	{
	case LengthState::shortLength:
		SetStickLength(normalLangth - langthChange);
		break;
	case LengthState::normalLength:
		SetStickLength(normalLangth);
		break;
	case LengthState::longLength:
		SetStickLength(normalLangth + langthChange);
		break;
	default:
		break;
	}
	if (stickMovement_ && GetStickAngle() == 0)
	{
		StartStickMovement();
		StickVelocity();
	}

	StickAcceleration(stickAcceleration_);			// 角加速度を設定, 角速度を適用
	StickPosition(fulcrumPosition_, stickLength_);	// 座標を計算
}
//--------------------------------------------------
// @brief 振り子の棒の初期設定
//--------------------------------------------------
void StickMoveComponent::StickInit(DirectX::SimpleMath::Vector3 _fulcrum, bool _movement, float _stickAngle)
{
	fulcrumPosition_ = _fulcrum;
	stickMovement_ = _movement;
	maxStickAngle_ = _stickAngle;
	SetStickAngle(0.0f);
}
//--------------------------------------------------
// 振り子の座標を計算
//--------------------------------------------------
void StickMoveComponent::StickPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length)
{
	//if (isStickAngle_ > 0) {		// -角度が正の場合
	//	stickPosition_.x = _fulcrum.x + _length * cos(stickRadian_);
	//	stickPosition_.y = _fulcrum.y - _length * sin(stickRadian_);
	//}
	//else if (isStickAngle_ < 0) {	// -角度が負の場合
	//	stickPosition_.x = _fulcrum.x + _length * cos(stickRadian_);
	//	stickPosition_.y = _fulcrum.y - _length * sin(stickRadian_);
	//}
	//else {					// -角度が0の場合
	//	stickPosition_.x = _fulcrum.x;
	//	stickPosition_.y = _fulcrum.y - _length;
	//}

	// 振り子の角度の計算を修正してみました by arima
	// 問題がなければ上のコードを消しといてください。
	// 角度が0度付近の時に「ガクッ」っとする感触があるので要修正かも。

	ConversionRadian(isStickAngle_);

	stickPosition_.x = _fulcrum.x + _length * cos(stickRadian_);
	stickPosition_.y = _fulcrum.y - _length * sin(stickRadian_);

	auto pendulumPos = pendulum_transform_component_->GetPosition();
	float deltaX = pendulumPos.x - fulcrumPosition_.x;
	float deltaY = pendulumPos.y - fulcrumPosition_.y;

	float angle = atan2(deltaX, deltaY);

	this->owner_->GetTransformComponent()->SetPosition({ stickPosition_.x, stickPosition_.y , 0.0f});
	this->owner_->GetTransformComponent()->SetRotation(-angle);
}

//--------------------------------------------------
// 振り子の角度の推移を計算
//--------------------------------------------------
void StickMoveComponent::StickAcceleration(float _angularAcceleration) 
{
	if (turnStick_) 
	{
		if (isStickAngle_ > 0) {
			SetStickAcceleration(-_angularAcceleration);
			StickVelocity();			// -角速度を適用 
			if (isStickAngle_ <= 0) {	// -角度が0を跨いでしまったら
				SetStickAngle(-wasStickAngle_);
				if (!stickMovement_) { StopStickMovement(); }
			}
		}
		else if (isStickAngle_ < 0) {
			SetStickAcceleration(_angularAcceleration);
			StickVelocity();			// -角速度を適用 
			// 最高到達点に至ったら反転
			if (GetStickVelocity() >= 0) {
				turnStick_ = false;
			}
		}
	}
	else {
		if (isStickAngle_ < 0) {
			SetStickAcceleration(_angularAcceleration);
			StickVelocity();			// -角速度を適用 
			if (isStickAngle_ >= 0) {	// -角度が0を跨いでしまったら
				SetStickAngle(-wasStickAngle_);
				if (!stickMovement_) { StopStickMovement(); }
			}
		}
		else if (isStickAngle_ > 0) {
			SetStickAcceleration(-_angularAcceleration);
			StickVelocity();			// -角速度を適用 
			// 最高到達点に至ったら反転
			if (GetStickVelocity() <= 0) {
				turnStick_ = true;
			}
		}
	}
}

//--------------------------------------------------
// 振り子の角度に角速度を適用
//--------------------------------------------------
void StickMoveComponent::StickVelocity()
{
	SetStickVelocity(std::round((GetStickVelocity() + GetStickAcceleration()) * 1000) / 1000);
	SetStickAngle(std::round((GetStickAngle() + GetStickVelocity()) * 1000) / 1000);
}
//--------------------------------------------------
// 角度をラジアンに変換
//--------------------------------------------------
void StickMoveComponent::ConversionRadian(float _angle)
{
	stickRadian_ = (90 - _angle) * (PI / 180.0f);
}
//--------------------------------------------------
// 振り子の角度のセッターゲッター
//--------------------------------------------------
void StickMoveComponent::SetStickAngle(float _stickAngle) 
{
	wasStickAngle_ = isStickAngle_;
	isStickAngle_ = _stickAngle;
}
float StickMoveComponent::GetStickAngle()
{
	return isStickAngle_;
}
//--------------------------------------------------
// 振り子の角速度のセッターゲッター
//--------------------------------------------------
void StickMoveComponent::SetStickVelocity(float _angularVelocity)
{
	wasStickVelocity_ = isStickVelocity_;
	isStickVelocity_ = _angularVelocity;
}
float StickMoveComponent::GetStickVelocity()
{
	return isStickVelocity_;
}

//--------------------------------------------------
// 振り子の角加速度のセッターゲッター
//--------------------------------------------------
void StickMoveComponent::SetStickAcceleration(float _stickAcceleration) 
{
	stickAcceleration_ = _stickAcceleration;
}
float StickMoveComponent::GetStickAcceleration() {
	return stickAcceleration_;
}

//--------------------------------------------------
// 支点の座標のセッターゲッター
//--------------------------------------------------
void StickMoveComponent::SetStickFulcrum(DirectX::SimpleMath::Vector3 _fulcrumPosition)
{
	fulcrumPosition_ = _fulcrumPosition;
}
DirectX::SimpleMath::Vector3 StickMoveComponent::GetStickFulcrum() 
{
	return fulcrumPosition_;
}

//--------------------------------------------------
// 支柱の長さのセッターゲッター
//--------------------------------------------------
void StickMoveComponent::SetStickLength(float _stickLength) 
{
	stickLength_ = _stickLength;
}
float StickMoveComponent::GetStickLength() 
{
	return stickLength_;
}

//--------------------------------------------------
// 振り子の停止、始動
//--------------------------------------------------
void StickMoveComponent::StartStickMovement() 
{
	maxStickVelocity_ = 0;
	for (int i = 1;; i++) {
		maxStickVelocity_ += stickAcceleration_ * i;
		if (maxStickVelocity_ >= maxStickAngle_) {
			SetStickVelocity(stickAcceleration_ * i);
			break;
		}
	}
}
void StickMoveComponent::StopStickMovement() 
{
	SetStickAngle(0);
	SetStickVelocity(0);
	SetStickAcceleration(0);
}