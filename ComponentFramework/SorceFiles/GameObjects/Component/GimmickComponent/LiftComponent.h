//==================================================
// [LiftComponent.h] リフトコンポーネント
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：リフトの挙動を制御するコンポーネント
//==================================================
#ifndef LIFT_COMPONENT_H_
#define LIFT_COMPONENT_H_
/*----- インクルード -----*/
#include <SimpleMath.h>

#include "../../Component.h"


/*----- 前方宣言 -----*/
class Pendulum;

//--------------------------------------------------
// リフトコンポーネント
//--------------------------------------------------
class LiftComponent : public Component
{
public:
	enum class LiftComState {
		Move,
		Stop
	};

	enum class LiftComMoveState
	{
		length,		// 縦移動
		side,		// 横移動
		diagonalRight,	// 斜め移動(右)
		diagonalLeft,	// 斜め移動(左)
	};

	LiftComponent(GameObject* _owner, Pendulum* _pendulum, LiftComMoveState _moveState, int _updateOrder = 50);
	~LiftComponent();

	void Init() override;
	void Uninit() override;
	void Update() override;

	TypeID GetComponentType(void) const override { return TypeID::LiftComponent; }

	bool CheckTraveledDistance();	// 移動距離のチェック

	void SetLiftComState(LiftComState _state) { lift_com_state_ = _state; }
	auto GetLiftComState(void) { return lift_com_state_; }

	void SetLiftComMoveState(LiftComMoveState _state) { lift_com_move_state_ = _state; }
	auto GetLiftComMoveState(void) { return lift_com_move_state_; }

	void SetMaxMoveDistance(float _distance) { max_move_distance_ = _distance; }
	auto GetMaxMoveDistance(void) { return max_move_distance_; }

	void SetTraveledDistance(DirectX::SimpleMath::Vector2 _distance) { traveled_distance_ = _distance; }
	auto GetTraveledDistance(void) { return traveled_distance_; }

	void SetDirection(DirectX::SimpleMath::Vector2 _direction) { direction_ = _direction; }
	auto GetDirection(void) { return direction_; }

	void SetStartPos(DirectX::SimpleMath::Vector3 _pos) { start_pos_ = _pos; }
	auto GetStartPos(void) { return start_pos_; }

private:
	bool CheckLengthSideTraveled();	// 縦横移動の移動距離のチェック
	bool CheckDiagonalTraveled();	// 斜め移動の移動距離のチェック

	void InitDirection();	// 移動方向の初期化

	LiftComState lift_com_state_;					// リフトの状態
	LiftComMoveState lift_com_move_state_;			// 移動方向

	Pendulum* pendulum_;				// 連動させたい振り子

	class TransformComponent* owner_transform_ = {};
	class VelocityComponent* owner_velocity_ = {};

	float max_move_distance_;								// 最大移動距離
	DirectX::SimpleMath::Vector2 traveled_distance_;		// 累積移動距離
	DirectX::SimpleMath::Vector2 direction_;			// 移動方向
	DirectX::SimpleMath::Vector3 start_pos_;				// 開始位置
};

#endif // LIFT_COMPONENT_H_