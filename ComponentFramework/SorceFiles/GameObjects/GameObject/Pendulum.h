//==================================================
// [Pendulum.h] 振り子オブジェクトヘッダ
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の制御を行うクラス
//==================================================
#ifndef PENDULUM_H_
#define PENDULUM_H_

/*----- インクルード -----*/
#include <memory>
#include <cmath>

#include "../GameObject.h"

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// プレイヤーオブジェクト
//--------------------------------------------------
class Pendulum
	: public GameObject
{
public:
	Pendulum(GameManager* _gameManager, Vector3 _fulcrum, bool _movement, float _pendulumAngle);
	~Pendulum(void);

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Pendulum; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	// 子オブジェクト
	class TimeZone* time_zone_{};
	class Stick*		stick_{};
	// 所有するコンポーネント
	class RenderComponent*			 sprite_component_	 {};
	class ColliderBaseComponent*	 collider_component_ {};
	class PendulumMovementComponent* pendulum_component_ {};
	class EventBaseComponent*	collider_event_component_{};
	class ChildrenComponent*		children_component_	 {};
};
#endif	// PENDULUM_H_