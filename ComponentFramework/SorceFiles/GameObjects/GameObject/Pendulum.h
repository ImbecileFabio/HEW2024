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

/*----- 構造体定義 -----*/



/*----- 前方宣言 -----*/
class SpriteComponent;
class PendulumComponent;
//--------------------------------------------------
// プレイヤーオブジェクト
//--------------------------------------------------
class Pendulum
	: public GameObject
{
public:
	Pendulum(GameManager* _gameManager);
	~Pendulum(void);
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Pendulum; }

private:
	// 所有するコンポーネント
	SpriteComponent* sprite_component_{};
	PendulumComponent* pendulum_component_{};
};
#endif	// PENDULUM_H_