//==================================================
// [PendulumComponent.h] 振り子モジュールヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：振り子の動作を決める機能の宣言
//==================================================
#ifndef PENDULUM_COMPONENT_H_
#define PENDULUM_COMPONENT_H_

/*----- インクルード -----*/
#include <memory>

#include "../Component.h"
/*----- 構造体宣言 -----*/

/*----- 前方宣言 -----*/
class GameObject;

//--------------------------------------------------
// 振り子コンポーネントクラス
//--------------------------------------------------
class PendulumComponent : public Component
{
public:
	PendulumComponent(GameObject* _owner, int _drawOrder = 50);
	~PendulumComponent();

	void Init(void) override {};
	void Uninit(void) override;
	void Update(void) override {};

	virtual TypeID GetComponentType(void) const override { return TypeID::PendulumComponent; }

private:
	float angle_{};		// 角度
	float rength_{};	// 長さ

};

#endif	// PENDULUM_COMPONENT_H_