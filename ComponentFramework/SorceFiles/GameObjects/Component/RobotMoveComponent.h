//==================================================
// [RobotMoveComponent.h] ロボット移動コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ロボットの挙動を制御するコンポーネント
//==================================================

#ifndef ROBOT_MOVE_COMPONENT_H_
#define ROBOT_MOVE_COMPONENT_H_
/*----- インクルード -----*/
#include "SimpleMath.h"

#include "../Component.h"


/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameObject;

//--------------------------------------------------
// カメラコンポーネント
//--------------------------------------------------
class RobotMoveComponent :
    public Component
{
public:
    RobotMoveComponent(GameObject* _owner, int _updateOrder = 50);
    ~RobotMoveComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    virtual TypeID GetComponentType(void) const override { return TypeID::RobotMoveComponent; }

private:
    void CheckTurnAround(class TransformComponent& _transform, class BoxColliderComponent& _collider);

	float speed_;		// 移動速度
	bool right_move_flg_;	// 移動方向
	bool on_ground_flg_;	// 地面に接地しているか
};

#endif // ROBOT_MOVE_COMPONENT_H_


