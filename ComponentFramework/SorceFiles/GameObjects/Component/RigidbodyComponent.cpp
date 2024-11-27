//==================================================
// [RigidbodyComponent.cpp] 物理演算コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：物理演算をおこなうクラス
//==================================================

#include "RigidbodyComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
RigidbodyComponent::RigidbodyComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder){
	std::cout << std::format("＜RigidbodyComponent＞ -> Constructor\n");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
RigidbodyComponent::~RigidbodyComponent(){
	std::cout << std::format("＜RigidbodyComponent＞ -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void RigidbodyComponent::Init(){

}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void RigidbodyComponent::Uninit(){

}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void RigidbodyComponent::Updata() {
	//UpdateVelocity();
}


////--------------------------------------------------
//// 加速度
////--------------------------------------------------
//void	RigidbodyComponent::SetAcceleration(const Vector3 _acceleration) {
//	acceleration_ = _acceleration;
//}
//Vector3 RigidbodyComponent::GetAcceleration() const {
//	return acceleration_;
//}
//// -使用フラグ
//void	RigidbodyComponent::SetUseAcceleration(const bool _use_acceleration) {
//	use_acceleration_ = _use_acceleration;
//}
//bool	RigidbodyComponent::GetUseAcceleration() const {
//	return use_acceleration_;
//}
//
//
////--------------------------------------------------
//// 速度
////--------------------------------------------------
//void	RigidbodyComponent::SetVelocity(const Vector3 _velocity){
//	velocity_ = _velocity;
//}
//void	RigidbodyComponent::UpdateVelocity() {
//	position_ = owner_->GetTransformComponent()->GetPosition();	// -現在座標の取得
//
//	// 加速度を適用
//	if (use_acceleration_) {	
//		velocity_.x += acceleration_.x;
//		velocity_.y += acceleration_.y;
//		velocity_.z += acceleration_.z;
//	}
//	// 重力を適用（一応三つとも）
//	if (use_gravity_) {
//		velocity_.x += gravity_.x;
//		velocity_.y += gravity_.y;
//		velocity_.z += gravity_.z;
//	}
//
//	position_.x += velocity_.x;
//	position_.y += velocity_.y;
//	position_.z += velocity_.z;
//
//	owner_->GetTransformComponent()->SetPosition(velocity_);
//}
//Vector3	RigidbodyComponent::GetVelocity() const {
//	return velocity_;
//}
//// -使用フラグ
//void	RigidbodyComponent::SetUseVelocity(const bool _use_velocity) {
//	use_velocity_ = _use_velocity;
//}
//bool	RigidbodyComponent::GetUseVelocity() const {
//	return use_velocity_;
//}
//
//
////--------------------------------------------------
//// 重力
////--------------------------------------------------
//// -使用フラグ
//void	RigidbodyComponent::SetUseGravity(const bool _use_gravity) {
//	use_gravity_ = _use_gravity;
//}
//bool	RigidbodyComponent::GetUseGravity() const {
//	return use_gravity_;
//}