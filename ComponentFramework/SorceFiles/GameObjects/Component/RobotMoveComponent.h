//==================================================
// [RobotMoveComponent.h] ロボット移動コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ロボットの挙動を制御するコンポーネント
//==================================================

#ifndef ROBOT_MOVE_COMPONENT_H_
#define ROBOT_MOVE_COMPONENT_H_
/*----- インクルード -----*/
#include <optional>
#include "SimpleMath.h"
#include "../Component.h"


/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class GameObject;
class TransformComponent;
class BoxColliderComponent;

using namespace DirectX::SimpleMath;
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
    // 段差の高さを調べる
    std::optional<float> CheckStepHeight(const TransformComponent& _transform, const Vector3& _size, const std::vector<GameObject*> _environmentObjects);

	float speed_;                    // 移動速度
	float max_step_height_;	         // 上り下りできる段差の高さ
	float step_scan_distance_;	     // 段差を探す距離
	// 移動方向 ( 右:1,0 / 左:-1,0 / 上:0,1 / 下:0,-1)
    Vector2 direction_;
};

#endif // ROBOT_MOVE_COMPONENT_H_


