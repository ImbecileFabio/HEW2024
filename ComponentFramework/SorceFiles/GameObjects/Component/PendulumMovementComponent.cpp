//==================================================
// [PendulumMovementComponent.cpp] 振り子運動コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の運動の定義
//==================================================

#include "PendulumMovementComponent.h"
#include "RigidbodyComponent/AngularVelocityComponent.h"

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
	isPendulumAngle_	= 0.f;
	wasPendulumAngle_	= 0.f;
	pendulumRadian_		= 0.f;
	turnPendulum_		= true;
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void PendulumMovementComponent::Uninit() {

}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void PendulumMovementComponent::Update(float _angle, DirectX::SimpleMath::Vector3 _fulcrum, float _length) {
	//std::cout << std::format("{}  {}  {}  {}  {}\n", turnPendulum_, isPendulumAngle_, wasPendulumAngle_,
	//	this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularVelocity(),
	//	this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularAcceleration());
	PendulumAcceleration(_angle);			// 角加速度を設定, 角速度を適用
	PendulumPosition(_fulcrum, _length);	// 座標を計算
	
}


//--------------------------------------------------
// 振り子の座標を計算
//--------------------------------------------------
void PendulumMovementComponent::PendulumPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length) {
	if (isPendulumAngle_ > 0) {		// -角度が正の場合
		ConversionRadian(isPendulumAngle_);
		pemdulumPosition_.x = _fulcrum.x + _length * cos(pendulumRadian_);
		pemdulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);

	}
	else if (isPendulumAngle_ < 0) {	// -角度が負の場合
		ConversionRadian(-isPendulumAngle_);
		pemdulumPosition_.x = _fulcrum.x - _length * cos(pendulumRadian_);
		pemdulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);
	}
	else {					// -角度が0の場合
		pemdulumPosition_.x = 0;
		pemdulumPosition_.y = _fulcrum.y - _length;
	}
	
	this->owner_->GetComponent<TransformComponent>()->SetPosition(pemdulumPosition_);
	this->owner_->GetComponent<TransformComponent>()->SetRotation(-isPendulumAngle_);
}

//--------------------------------------------------
// 振り子の角度の推移を計算
//--------------------------------------------------
void PendulumMovementComponent::PendulumAcceleration(float _angularAcceleration) {
	if (turnPendulum_) {
		if (isPendulumAngle_ > 0) {
			this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(-_angularAcceleration);
			PendulumVelocity();			// -角速度を適用 
			if (isPendulumAngle_ <= 0) {	// -角度が0を跨いでしまったら
				isPendulumAngle_ = -wasPendulumAngle_;
			}
		}
		else {
			this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(_angularAcceleration);
			PendulumVelocity();			// -角速度を適用 
			// 最高到達点に至ったら反転
			if (this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularVelocity() >= 0) {	
				turnPendulum_ = false;
			}
		}
	} else {
		if (isPendulumAngle_ < 0) {
			this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration( _angularAcceleration);
			PendulumVelocity();			// -角速度を適用 
			if (isPendulumAngle_ >= 0) {	// -角度が0を跨いでしまったら
				isPendulumAngle_ = -wasPendulumAngle_;
			}
		}
		else {
			this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(-_angularAcceleration);
			PendulumVelocity();			// -角速度を適用 
			// 最高到達点に至ったら反転
			if (this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularVelocity() <= 0) {
				turnPendulum_ = true;
			}
		}
	}
	//if (isPendulumAngle_ > 0) {			// -正の角度の場合
	//	this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(-_angularAcceleration);
	//} else if (isPendulumAngle_ < 0) {	// -負の角度の場合
	//	this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration( _angularAcceleration);
	//} else {					// -角度が0の場合
	//	this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularAcceleration(0.f);
	//}
}

//--------------------------------------------------
// 振り子の角度に角速度を適用
//--------------------------------------------------
void PendulumMovementComponent::PendulumVelocity() {
	// 角速度に角加速度を適用した値を、角速度に入力する
	this->owner_->GetComponent<AngularVelocityComponent>()->SetAngularVelocity(
		this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularVelocity() +
		this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularAcceleration());

	wasPendulumAngle_ = isPendulumAngle_;
	isPendulumAngle_ += this->owner_->GetComponent<AngularVelocityComponent>()->GetAngularVelocity();
}

//--------------------------------------------------
// 角度をラジアンに変換
//--------------------------------------------------
void PendulumMovementComponent::ConversionRadian(float _angle) {
	pendulumRadian_ = (90 - _angle) * (PI / 180.0f);
}

//--------------------------------------------------
// 振り子の角度のセッターゲッター
//--------------------------------------------------
void PendulumMovementComponent::SetPendulumAngle(float _pendulumAngle) {
	if (_pendulumAngle > 0) {
		turnPendulum_ = true;
	} else {
		turnPendulum_ = false;
	}
	isPendulumAngle_ = _pendulumAngle;
}
float PendulumMovementComponent::GetPendulumAngle() {
	return isPendulumAngle_;
}