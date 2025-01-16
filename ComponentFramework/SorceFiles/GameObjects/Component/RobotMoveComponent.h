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
	enum class RobotMoveState {
		Idle,
		Move,
		Fall,
		OnLift
	};

    RobotMoveComponent(GameObject* _owner, int _updateOrder = 2);
    ~RobotMoveComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

	void SetState(RobotMoveState _state) { move_state_ = _state; }

    virtual TypeID GetComponentType(void) const override { return TypeID::RobotMoveComponent; }

private:
	void UpdateWallScanCollider();	// ウォールスキャンコライダーの更新
	void UpdateStepScanCollider();	// ステップアップ用スキャンコライダーの更新
	void UpdateGroundScanCollider();	// 地面スキャンコライダーの更新

	bool CheckWallCollision();  // 壁との当たり判定
	bool CheckStepUp(); 		 // 段差の上り判定
	bool CheckGround();		 // 地面の判定

	float GetStepHeight();	// 段差の高さを調べる

private:
    // ownerのコンポーネントをキャッシュ
	class TransformComponent* owner_transform_;
	class VelocityComponent* owner_velocity_;
	class BoxColliderComponent* owner_collider_;
	class GravityComponent* owner_gravity_;

private:// コンポーネント内にゲームオブジェクトとはこれ如何に...ゆるして, いつかコンポーネント化するべき
	class GameObject* wall_scan_object_;                 // スキャン用オブジェクト
	class ScanColliderComponent* wall_scan_collider_;    // スキャン用コライダー
	class GameObject* step_scan_object_;                 // ステップアップ用オブジェクト
	class ScanColliderComponent* step_scan_collider_;    // ステップアップ用コライダー
	class GameObject* ground_scan_object_;               // 地面スキャン用オブジェクト
	class ScanColliderComponent* ground_scan_collider_;  // 地面スキャン用コライダー

private:
	RobotMoveState move_state_;

    float speed_;				    // 移動速度
    Vector2 direction_;         	// 移動方向 ( 右:1,0 / 左:-1,0 / 上:0,1 / 下:0,-1)
	float scan_distance_;           // レイキャストの距離
	float max_step_height_;          // 登れる段差の高さ
};

#endif // ROBOT_MOVE_COMPONENT_H_


