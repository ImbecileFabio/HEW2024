//#include "LiftComponent.h"
//#include "../Component.h"
//#include "../GameObject.h"
//#include "../Component/RigidbodyComponent/VelocityComponent.h"
//#include "../Component/ColliderComponent/BoxColliderComponent.h"
////--------------------------------------------------
//// @brief コンストラクタ
//// @param _maxPos リフトの折り返し地点（＋）横の場合はXだけ、縦の場合はYだけ設定する
//// @param _minPos リフトの折り返し地点（ー）
//// @param _moveState リフトを縦か横に移動するかの設定
////--------------------------------------------------
//LiftComponent::LiftComponent(DirectX::SimpleMath::Vector2 _maxPos, DirectX::SimpleMath::Vector2 _minPos, 
//	MoveState _moveState, GameObject* _owner, int _updateOrder) : Component(_owner, _updateOrder), maxPos_(_maxPos), minPos_(_minPos), state_(_moveState)
//{
//	this->Init();
//}
////--------------------------------------------------
//// @brief デストラクタ
////--------------------------------------------------
//LiftComponent::~LiftComponent()
//{
//
//}
////--------------------------------------------------
//// @brief 初期化処理
////--------------------------------------------------
//void LiftComponent::Init(void)
//{
//	// リフトが持つコライダーを取得
//	colliderComponent_  = owner_->GetComponent<ColliderBaseComponent>();
//	velocityComponent_  = owner_->GetComponent<VelocityComponent>();
//}
////--------------------------------------------------
//// @brief 終了処理
////--------------------------------------------------
//void LiftComponent::Uninit(void)
//{
//	delete velocityComponent_;
//	delete colliderComponent_;
//}
////--------------------------------------------------
//// @brief 更新処理
////--------------------------------------------------
//void LiftComponent::Update(void)
//{
//	// リフトの移動処理
//	switch (state_)
//	{
//	case MoveState::length:
//		// 縦移動
//		break;
//	case MoveState::side:
//		// 横移動
//		DirectX::SimpleMath::Vector3 pos = this->owner_->GetTransformComponent()->GetPosition();
//		if (pos.x < maxPos_.x && switchFg_ == false)
//		{
//			pos.x += 2.0f;
//			if (pos.x >= maxPos_.x)
//				switchFg_ = true;
//		}
//		if (pos.x > minPos_.x && switchFg_ == true)
//		{
//			pos.x -= 2.0f;
//			if (pos.x <= minPos_.x)
//				switchFg_ = false;
//		}
//		this->owner_->GetTransformComponent()->SetPosition(pos.x, pos.y, pos.z);
//		break;
//	}
//}
