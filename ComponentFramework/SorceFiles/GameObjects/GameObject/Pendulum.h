//==================================================
// [Pendulum.h] 振り子オブジェクトヘッダ
// 著者：有馬啓太
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
	Pendulum(GameManager* _gameManager);
	~Pendulum(void);

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Pendulum; }
private:
	// 所有するコンポーネント
	class RenderComponent*		   sprite_component_   {};
	class ColliderBaseComponent*	   collider_component_ {};
	class PendulumMovementComponent* pendulum_component_ {};
	class TimeZoneComponent*	       time_zone_component_{};
};
#endif	// PENDULUM_H_