//==================================================
// [VelocityComponent.cpp] 速度演算コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：速度演算をおこなうクラス
//		１．位置、速度
//		２．重力
//==================================================

#include "VelocityComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
VelocityComponent::VelocityComponent(GameObject* _owner, int _updateOrder)
	:RigidbodyComponent(_owner, _updateOrder) {
	std::cout << std::format("＜VelocityComponent＞ -> Constructor\n");

	Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
VelocityComponent::~VelocityComponent() {
	std::cout << std::format("＜VelocityComponent＞ -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void VelocityComponent::Init() {
	// 使用フラグがtrueなら作用する
	use_acceleration_	= true;
	use_velocity_		= true;

	acceleration_	= { 0.0f, 0.0f, 0.0f };
	velocity_		= { 0.0f, 0.0f, 0.0f };
	speed_rate_ = 1.0f;
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void VelocityComponent::Uninit() {

}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void VelocityComponent::Update() {
	position_ = this->owner_->GetTransformComponent()->GetPosition();	// -現在座標の取得

	// 速度を適用
	if (use_velocity_) {
		// 加速度を適用
		if (use_acceleration_) {
			velocity_ += acceleration_;
		}
		position_ += (velocity_ * speed_rate_);
	}

	this->owner_->GetTransformComponent()->SetPosition(position_);

	std::cout << std::format("＜VelocityComponent＞ ->[{}] x : {}, y : {}\n", owner_->GetObjectName(), velocity_.x, velocity_.y);

}
//--------------------------------------------------
// 速度係数をセット
//--------------------------------------------------
void VelocityComponent::SetSpeedRate(const float _speed_rate)
{
	speed_rate_ = _speed_rate;
}
//--------------------------------------------------
// 速度係数をゲット
//--------------------------------------------------
float VelocityComponent::GetSpeedRate(void)
{
	return speed_rate_;
}
//--------------------------------------------------
// 加速度
//--------------------------------------------------
void	VelocityComponent::SetAcceleration(const DirectX::SimpleMath::Vector3 _acceleration) {
	acceleration_ = _acceleration;
}
DirectX::SimpleMath::Vector3 VelocityComponent::GetAcceleration() const {
	return acceleration_;
}
// -使用フラグ
void	VelocityComponent::SetUseAcceleration(const bool _use_acceleration) {
	use_acceleration_ = _use_acceleration;
}
bool	VelocityComponent::GetUseAcceleration() const {
	return use_acceleration_;
}


//--------------------------------------------------
// 速度
//--------------------------------------------------
void	VelocityComponent::SetVelocity(const DirectX::SimpleMath::Vector3 _velocity) {
	velocity_ = _velocity;
}
DirectX::SimpleMath::Vector3	VelocityComponent::GetVelocity() const {
	return velocity_;
}
// -使用フラグ
void	VelocityComponent::SetUseVelocity(const bool _use_velocity) {
	use_velocity_ = _use_velocity;
}
bool	VelocityComponent::GetUseVelocity() const {
	return use_velocity_;
}
