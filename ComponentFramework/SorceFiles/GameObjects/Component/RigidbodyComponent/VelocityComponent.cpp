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

	// 使用フラグがtrueなら作用する
	use_acceleration_	= true;
	use_velocity_		= true;
	use_gravity_		= true;
	gravity_ = { 0.0f,-1.0f,0.0f };	// 一応固定
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

}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void VelocityComponent::Uninit() {

}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void VelocityComponent::Updata() {
	position_ = owner_->GetTransformComponent()->GetPosition();	// -現在座標の取得

	// 加速度を適用
	if (use_acceleration_) {
		velocity_.x += acceleration_.x;
		velocity_.y += acceleration_.y;
		velocity_.z += acceleration_.z;
	}
	// 重力を適用（一応三つとも）
	if (use_gravity_) {
		velocity_.x += gravity_.x;
		velocity_.y += gravity_.y;
		velocity_.z += gravity_.z;
	}

	position_.x += velocity_.x;
	position_.y += velocity_.y;
	position_.z += velocity_.z;

	owner_->GetTransformComponent()->SetPosition(velocity_);
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
//void	VelocityComponent::UpdateVelocity() {
//
//}
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


//--------------------------------------------------
// 重力
//--------------------------------------------------
// -使用フラグ
void	VelocityComponent::SetUseGravity(const bool _use_gravity) {
	use_gravity_ = _use_gravity;
}
bool	VelocityComponent::GetUseGravity() const {
	return use_gravity_;
}