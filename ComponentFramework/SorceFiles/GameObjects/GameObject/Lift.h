//==================================================
// [Lift.h] リフトヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：リフトオブジェクト
//==================================================
#ifndef LIFT_H_
#define LIFT_H_
/*----- インクルード -----*/
#include "../GameObject.h"
#include <SimpleMath.h>
/*----- 前方宣言 -----*/
class Pendulum;
class LiftGroup;
//--------------------------------------------------
// リフトオブジェクト
//--------------------------------------------------
class Lift : public GameObject
{
public:
	enum class LiftState {
		Move,
		Wait,
		Stop
	};

	enum class MoveState
	{
		length,		// 縦移動
		side,		// 横移動
		diagonalRight,	// 斜め移動(右)
		diagonalLeft,	// 斜め移動(左)
	};
	Lift(GameManager* _gameManager, int _order = 45);
	Lift(GameManager* _gameManager, Lift::MoveState _moveState, Vector3 _startpos, Vector3 _endPos, Pendulum* _pendulum = nullptr);

	~Lift(void);

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Lift; }	
	void OnCollisionEnter(GameObject* _other = nullptr) override;

	void SetPendulum(Pendulum* _pendulum);

	void SetMoveState(Lift::MoveState _moveState);
	auto GetMoveState() { return move_state_; }

	void SetLiftState(LiftState _state) { lift_state_ = _state; }
	auto GetLiftState() { return lift_state_; }

	void SetLiftGroup(LiftGroup* _group) { lift_group_ = _group; }
	LiftGroup* GetLiftGroup() { return lift_group_; }
private:
	class ColliderBaseComponent* collider_component_ = {};
	class EventBaseComponent*	collider_event_component_ = {};
	class RenderComponent*		sprite_component_		  = {};	// 画像表示
	class VelocityComponent*	velocity_component_		  = {};
	class LiftComponent*		lift_component_ = {};

	LiftState lift_state_;		// リフトの状態
	MoveState move_state_;		// 移動方向
	int turn_count_;			// 経過時間
	int max_count_;				// 切り返しまでの時間

	Pendulum* pendulum_;					// 連動させたい振り子
	LiftGroup* lift_group_{};					// リフトをまとめるグループ


};
#endif // _LIFT_H_