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
#include "../Component/LiftComponent.h"
#include <SimpleMath.h>
/*----- 前方宣言 -----*/
class Pendulum;
//--------------------------------------------------
// リフトオブジェクト
//--------------------------------------------------
class Lift : public GameObject
{
public:
	Lift(Pendulum* _pendulum, LiftComponent::MoveState _moveState ,DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameManager* _gameManager);
	~Lift(void);

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Lift; }	
	void OnCollisionEnter(GameObject* _other = nullptr) override;

private:
	class ColliderBaseComponent* collider_base_component_ = {};
	class EventBaseComponent*	collider_event_component_ = {};
	class RenderComponent*		sprite_component_		  = {};	// 画像表示
	class VelocityComponent*	velocity_component_		  = {};
	class LiftComponent*		lift_component_			  = {};	// リフトの移動
};
#endif // _LIFT_OBJECT_H_
