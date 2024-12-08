//==================================================
// [PendulumMovementComponent.cpp] 振り子運動コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の運動の定義
//==================================================

#include "PendulumMovementComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
PendulumMovementComponent::PendulumMovementComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder) {
	std::cout << std::format("＜PendulumMovementComponent＞ -> Constructor\n");

	Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
PendulumMovementComponent::~PendulumMovementComponent() {
	std::cout << std::format("＜PendulumMovementComponent＞ -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void PendulumMovementComponent::Init() {
	angle_ = -(this->owner_->GetComponent<TransformComponent>()->GetRotation().z);
	pendulumRadian_ = 0.f;
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void PendulumMovementComponent::Uninit() {

}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void PendulumMovementComponent::Update() {
	
}


//--------------------------------------------------
// 振り子の座標を計算
//--------------------------------------------------
void PendulumMovementComponent::PendulumPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length) {
	angle_ = -(this->owner_->GetComponent<TransformComponent>()->GetRotation().z);

	if (angle_ > 0) {		// -角度が正の場合
		ConversionRadian(angle_);
		pemdulumPosition_.x = _fulcrum.x + _length * cos(pendulumRadian_);
		pemdulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);

	}
	else if (angle_ < 0) {	// -角度が負の場合
		ConversionRadian(-angle_);
		pemdulumPosition_.x = _fulcrum.x - _length * cos(pendulumRadian_);
		pemdulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);
	}
	else {					// -角度が0の場合
		pemdulumPosition_.x = 0;
		pemdulumPosition_.y = _fulcrum.y - _length;
	}
	
	this->owner_->GetComponent<TransformComponent>()->SetPosition(pemdulumPosition_);
}

//--------------------------------------------------
// 振り子の角度の推移を計算
//--------------------------------------------------
void PendulumMovementComponent::PendulumAngle(float _angularAcceleration) {
	if (angle_ > 0) {			// -正の角度の場合
		this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration( _angularAcceleration);
	} else if (angle_ < 0) {	// -負の角度の場合
		this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(-_angularAcceleration);
	} else {					// -角度が0の場合
		this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(0.f);
	}
}

//--------------------------------------------------
// 角度をラジアンに変換
//--------------------------------------------------
void PendulumMovementComponent::ConversionRadian(float _angle) {
	pendulumRadian_ = (90 - _angle) * (PI / 180.0f);
}