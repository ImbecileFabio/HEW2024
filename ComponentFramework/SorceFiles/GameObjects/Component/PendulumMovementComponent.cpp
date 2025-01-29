//==================================================
// [PendulumMovementComponent.cpp] 振り子運動コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の運動の定義
//==================================================

#include "PendulumMovementComponent.h"
#include "../../PemdulumManager.h"
#include "../../AudioManager.h"

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
	pendulumPosition_ = {};		// -位置
	isPendulumAngle_ = 0;		// -現在の振り子の角度
	wasPendulumAngle_ = 0;		// -直前の振り子の角度
	isPendulumVelocity_ = 0;	// -現在の角速度
	wasPendulumVelocity_ = 0;	// -直前の角速度
	pendulumAcceleration_ = 0;	// -振り子の角加速度
	fulcrumPosition_ = {};		// -支点の座標
	pendulumLength_ = 0;		// -振り子の長さ
	pendulumRadian_ = 0;		// -振り子の角度（ラジアン）
	turnPendulum_ = true;		// -振り子の往復で処理を切り替えるためのフラグ　true：右から左　false：左から右

	langthState_ = LangthState::normalLangth;
	pendulumMovement_ = false;
	pendulumSelected_ = false;
	pendulumDirection_ = 1;
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
	// 振り子の状態遷移
	switch (langthState_)
	{
	case LangthState::shortLangth:
		SetPendulumLength(normalLangth - langthChange);
		break;
	case LangthState::normalLangth:
		SetPendulumLength(normalLangth);
		break;
	case LangthState::longLangth:
		SetPendulumLength(normalLangth + langthChange);
		break;
	default:
		break;
	}

	if (pendulumMovement_ && GetPendulumAngle() == 0.0f) 
	{ 
		StartPendulumMovement();
		PendulumVelocity();
	}

	PendulumAcceleration(pendulumAcceleration);				// 角加速度を設定, 角速度を適用
	PendulumPosition(fulcrumPosition_, pendulumLength_);	// 座標を計算
}


//--------------------------------------------------
// 振り子の座標を計算
//--------------------------------------------------
void PendulumMovementComponent::PendulumPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length) {

	//if (isPendulumAngle_ > 0) {		// -角度が正の場合
	//	pendulumPosition_.x = _fulcrum.x + _length * cos(pendulumRadian_);
	//	pendulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);
	//}
	//else if (isPendulumAngle_ < 0) {	// -角度が負の場合
	//	pendulumPosition_.x = _fulcrum.x + _length * cos(pendulumRadian_);
	//	pendulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);
	//}
	//else {					// -角度が0の場合
	//	pendulumPosition_.x = _fulcrum.x;
	//	pendulumPosition_.y = _fulcrum.y - _length;
	//}

	// 振り子の角度の計算を修正してみました by arima
	// 問題がなければ上のコードを消しといてください。
	// 角度が0度付近の時に「ガクッ」っとする感触があるので要修正かも。

	ConversionRadian(isPendulumAngle_);

	pendulumPosition_.x = _fulcrum.x + _length * cos(pendulumRadian_);
	pendulumPosition_.y = _fulcrum.y - _length * sin(pendulumRadian_);
	
	this->owner_->GetTransformComponent()->SetPosition(pendulumPosition_);
	this->owner_->GetTransformComponent()->SetRotation(-pendulumRadian_);
}

//--------------------------------------------------
// 振り子の角度の推移を計算
//--------------------------------------------------
void PendulumMovementComponent::PendulumAcceleration(float _angularAcceleration) {
	if (turnPendulum_) {
		if (isPendulumAngle_ > 0) {
			SetPendulumAcceleration(-_angularAcceleration);
			PendulumVelocity();			// -角速度を適用 
			if (isPendulumAngle_ <= 0) {	// -角度が0を跨いでしまったら
				SetPendulumAngle(-wasPendulumAngle_);
				if (!pendulumMovement_) { StopPendulumMovement(); }
			}
		}
		else if(isPendulumAngle_ < 0) {
			SetPendulumAcceleration(_angularAcceleration);
			PendulumVelocity();			// -角速度を適用 
			// 最高到達点に至ったら反転
			if (GetPendulumVelocity() >= 0) {
				turnPendulum_ = false;
			}
		}
	} else {
		if (isPendulumAngle_ < 0) {
			SetPendulumAcceleration( _angularAcceleration);
			PendulumVelocity();			// -角速度を適用 
			if (isPendulumAngle_ >= 0) {	// -角度が0を跨いでしまったら
				SetPendulumAngle(-wasPendulumAngle_);
				if (!pendulumMovement_) { StopPendulumMovement(); }
			}
		}
		else if(isPendulumAngle_ > 0) {
			SetPendulumAcceleration(-_angularAcceleration);
			PendulumVelocity();			// -角速度を適用 
			// 最高到達点に至ったら反転
			if (GetPendulumVelocity() <= 0) {
				turnPendulum_ = true;
			}
		}
	}
}

//--------------------------------------------------
// 振り子の角度に角速度を適用
//--------------------------------------------------
void PendulumMovementComponent::PendulumVelocity() {
	SetPendulumVelocity(std::round((GetPendulumVelocity() + GetPendulumAcceleration()) * 1000) / 1000);
	SetPendulumAngle(std::round((GetPendulumAngle() + GetPendulumVelocity()) * 1000) / 1000);
}

//--------------------------------------------------
// 角度をラジアンに変換
//--------------------------------------------------
void PendulumMovementComponent::ConversionRadian(float _angle) {
	pendulumRadian_ = (90 - _angle) * (PI / 180.0f);
}

//--------------------------------------------------
// 振り子の初期値設定
//--------------------------------------------------
void PendulumMovementComponent::PendulumInit(DirectX::SimpleMath::Vector3 _fulcrum, bool _movement, float _pendulumAngle) {
	fulcrumPosition_ = _fulcrum;
	pendulumMovement_ = _movement;
	maxPendulumAngle_ = _pendulumAngle;
	SetPendulumAngle(0.0f);
}

//--------------------------------------------------
// 振り子の角度のセッターゲッター
//--------------------------------------------------
void PendulumMovementComponent::SetPendulumAngle(float _pendulumAngle) {
	wasPendulumAngle_ = isPendulumAngle_;
	isPendulumAngle_ = _pendulumAngle;
}
float PendulumMovementComponent::GetPendulumAngle() {
	return isPendulumAngle_;
}

//--------------------------------------------------
// 振り子の角速度のセッターゲッター
//--------------------------------------------------
void PendulumMovementComponent::SetPendulumVelocity(float _angularVelocity) {
	wasPendulumVelocity_ = isPendulumVelocity_;
	isPendulumVelocity_ = _angularVelocity;
}
float PendulumMovementComponent::GetPendulumVelocity() {
	return isPendulumVelocity_;
}

//--------------------------------------------------
// 振り子の停止、始動
//--------------------------------------------------
void PendulumMovementComponent::StartPendulumMovement() {
	AudioManager::GetInstance()->Play(SoundLabel_HitSE);
	maxPendulumVelocity_ = 0;
	for (int i = 1;;i++) {
		maxPendulumVelocity_ += pendulumAcceleration * i;
		if (maxPendulumVelocity_ >= maxPendulumAngle_) {
			SetPendulumVelocity((pendulumAcceleration * i) * pendulumDirection_);
			break;
		}
	}
}
void PendulumMovementComponent::StopPendulumMovement() {
	SetPendulumAngle(0);
	SetPendulumVelocity(0);
	SetPendulumAcceleration(0);
}