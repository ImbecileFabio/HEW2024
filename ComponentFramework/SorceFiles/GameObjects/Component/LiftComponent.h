////==================================================
//// [LiftComponent.cpp] リフトヘッダ
//// 著者：尾上莉奈
////--------------------------------------------------
//// 説明：リフトコンポーネント
////==================================================
//#ifndef LIFT_COMPONENT_H_
//#define LIFT_COMPONENT_H_
///*----- インクルード -----*/
//#include "../Component.h"
//#include <SimpleMath.h>
///*----- 前方宣言 -----*/
//class ColliderBaseComponent;
//class VelocityComponent;
///*----- enum class -----*/
//enum class MoveState
//{
//	length,	// 縦移動
//	side,	// 横移動
//};
////--------------------------------------------------
//// リフトクラス
////--------------------------------------------------
//class LiftComponent : public Component
//{
//public:
//	LiftComponent(DirectX::SimpleMath::Vector2 _maxPos, DirectX::SimpleMath::Vector2 _minPos,
//		MoveState _moveState, GameObject* _owner, int _updateOrder = 50);
//	~LiftComponent();
//
//	void Init  (void) override;
//	void Uninit(void) override;
//	void Update(void) override;
//	
//	TypeID GetComponentType(void) const override { return TypeID::LiftComponent; }
//private:
//	// リフトが使う参照用のコンポーネント
//	ColliderBaseComponent* colliderComponent_  = {};
//	VelocityComponent*	   velocityComponent_ = {};
//
//	DirectX::SimpleMath::Vector2 maxPos_ = {};
//	DirectX::SimpleMath::Vector2 minPos_ = {};
//	float direction_ = 1.0f;	// 移動方向 正＝１、負＝－１
//	bool switchFg_ = false;		// 移動方向の切り替えフラグ
//
//	MoveState state_ = MoveState::length;
//};
//#endif // _LIFT_COMPONENT_H_