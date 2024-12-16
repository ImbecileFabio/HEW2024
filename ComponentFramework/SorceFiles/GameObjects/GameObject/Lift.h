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
//--------------------------------------------------
// リフトオブジェクト
//--------------------------------------------------
class Lift : public GameObject
{
public:
	enum class MoveState
	{
		length,	// 縦移動
		side,	// 横移動
	};

	Lift(MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos,GameManager* _gameManager);
	~Lift(void);

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;
	DirectX::SimpleMath::Vector3 maxPos_;	// 正方向の最大座標
	DirectX::SimpleMath::Vector3 minPos_;	// 負方向の最大座標
	TypeID GetType(void) override { return TypeID::Lift; }	
	void OnCollisionEnter(GameObject* _other = nullptr) override;

	void SetPendulum(PendulumMovementComponent& _pendulum_movement_component) { pendulum_movement_component_ = _pendulum_movement_component; }
private:
	class PendulumMovementComponent& pendulum_movement_component_;
	bool switchFg_;			// スイッチフラグ
	MoveState moveState_;	// 移動状態

	class ColliderBaseComponent* collider_base_component_ = {};
	class EventBaseComponent*	collider_event_component_ = {};
	class RenderComponent*		spriteComponent_		= {};	// 画像表示
	class VelocityComponent* velocityComponent_ = {};
	class PendulumMovementComponent* pendulum_movement_component = {};

};
#endif // _LIFT_OBJECT_H_
