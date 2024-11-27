//==================================================
// [AngularVelocityComponent.cpp] 角速度演算コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：物理演算をおこなうクラス
//		４．角速度、回転
//==================================================

#include "AngularVelocityComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
AngularVelocityComponent::AngularVelocityComponent(GameObject* _owner, int _updateOrder)
	:RigidbodyComponent(_owner, _updateOrder) {
	std::cout << std::format("＜AngularVelocityComponent＞ -> Constructor\n");

	Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
AngularVelocityComponent::~AngularVelocityComponent() {
	std::cout << std::format("＜AngularVelocityComponent＞ -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void AngularVelocityComponent::Init() {
	use_angularAcceleration_	= true;
	use_angularVelocity_		= true;
	angularAcceleration_	= { 0.f,0.f,0.f };
	angularVelocity_		= { 0.f,0.f,0.f };
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void AngularVelocityComponent::Uninit() {

}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void AngularVelocityComponent::Updata() {
	rotation_ = this->owner_->GetComponent<TransformComponent>()->GetRotation();

	// 角加速度を適用
	if (use_angularVelocity_) {
		// 角速度を適用
		if (use_angularAcceleration_) {
			angularVelocity_.x += angularAcceleration_.x;
			angularVelocity_.y += angularAcceleration_.y;
			angularVelocity_.z += angularAcceleration_.z;
		}

		rotation_.x += angularVelocity_.x;
		rotation_.y += angularVelocity_.y;
		rotation_.z += angularVelocity_.z;
	}

	this->owner_->GetComponent<TransformComponent>()->SetRotation(rotation_);
}


//--------------------------------------------------
//角加速度
//--------------------------------------------------
void	AngularVelocityComponent::SetAngularAcceleration(const Vector3 _angularAcceleration) {
	angularAcceleration_ = _angularAcceleration;
}
Vector3 AngularVelocityComponent::GetAngularAcceleration() const {
	return angularAcceleration_;
}
void	AngularVelocityComponent::SetUseAngularAcceleration(const bool _use_angularAcceleration) {
	use_angularAcceleration_ = _use_angularAcceleration;
}
bool	AngularVelocityComponent::GetUseAngularAcceleration() const {
	return use_angularAcceleration_;
}

//--------------------------------------------------
//角速度
//--------------------------------------------------
void	AngularVelocityComponent::SetAngularVelocity(const Vector3 _angularVelocity) {
	angularVelocity_ = _angularVelocity;
}
Vector3 AngularVelocityComponent::GetAngularVelocity() const {
	return angularVelocity_;
}
void	AngularVelocityComponent::SetUseAngularVelocity(const bool _use_angularVelocity) {
	use_angularVelocity_ = _use_angularVelocity;
}
bool	AngularVelocityComponent::GetUseAngularVelocity() const {
	return use_angularVelocity_;
}