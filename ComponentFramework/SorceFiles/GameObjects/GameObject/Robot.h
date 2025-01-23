//==================================================
// [Robot.h] ロボットオブジェクトヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ロボットオブジェクトです
//==================================================
#ifndef ROBOT_H_
#define ROBOT_H_

/*----- インクルード -----*/
#include <memory>
#include "../GameObject.h"

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------------------
// タイルオブジェクト
//--------------------------------------------------
class Robot
	: public GameObject
{
public:
	enum class RobotState {
		Idle,
		Move,
		Fall,
		OnLift
	};

	Robot(GameManager* _gameManager);
	~Robot(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Robot; }

	void SetRobotState(RobotState _state) { robot_state_ = _state; }
	auto GetRobotState(void) { return robot_state_; }

	auto GetCollisionLift() { return collision_lift_; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	RobotState robot_state_;

	// 触れているリフト
	class Lift* collision_lift_ = nullptr;


	// 所有するコンポーネント
	class SpriteComponent* sprite_component_{};
	class AnimationComponent* animation_component_{};	// アニメーション
	class FlipComponent* flip_component_{};	// 反転
	class ColliderBaseComponent* collider_component_{};	// 当たり判定
	class ColliderEventComponent* collider_event_component_{};	// 当たり判定イベント
	class VelocityComponent* velocity_component_{};		// 速度
	class GravityComponent* gravity_component_{};		// 重力
	class RobotMoveComponent* robot_move_component_{};	// ロボットの移動
	class PushOutComponent* push_out_component_{};	// 押し出し

};
#endif	// ROBOT_H_