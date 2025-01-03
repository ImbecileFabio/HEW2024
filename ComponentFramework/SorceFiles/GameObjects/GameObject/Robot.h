//==================================================
// [Robot.h] タイルオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：床や壁のタイルオブジェクト
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
	Robot(GameManager* _gameManager);
	~Robot(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Robot; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	// 所有するコンポーネント
	class RenderComponent* sprite_component_{};
	class ColliderBaseComponent* collider_component_{};	// 当たり判定
	class ColliderEventComponent* collider_event_component_{};	// 当たり判定イベント
	class VelocityComponent* velocity_component_{};		// 速度
	class RobotMoveComponent* robot_move_component_{};	// ロボットの移動
	class PushOutComponent* push_out_component_{};	// 押し出し

	//
	class DebugColliderDrawComponent* debug_collider_draw_component_{};
};
#endif	// ROBOT_H_