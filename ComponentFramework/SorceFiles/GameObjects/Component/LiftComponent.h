//==================================================
// [LiftComponent.h] リフトコンポーネントヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：リフトコンポーネント
//==================================================
#ifndef LIFT_COMPONENT_H_
#define LIFT_COMPONENT_H_
/*----- インクルード -----*/
#include "../Component.h"
#include <SimpleMath.h>
/*----- 前方宣言 -----*/
class GameObject;
class Pendulum;
class LiftComponent : public Component
{
public:
	enum class MoveState
	{
		length,		// 縦移動
		side,		// 横移動
		diagonal,	// 斜め移動
	};

	LiftComponent(Pendulum* _pendulum, MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos,
		GameObject* _owner, int _updateOrder = 50);
	~LiftComponent(void);
	
	void Init  () override;
	void Uninit() override;
	void Update() override;

	TypeID GetComponentType(void) const override { return TypeID::LiftComponent; }

	DirectX::SimpleMath::Vector3 GetMaxPos(void) const { return maxPos_; }
	DirectX::SimpleMath::Vector3 GetMinPos(void) const { return minPos_; }
private:
	DirectX::SimpleMath::Vector3 maxPos_;	// 正方向の最大座標
	DirectX::SimpleMath::Vector3 minPos_;	// 負方向の最大座標

	Pendulum* pendulum_;			// リフトの動きと連動させる振り子の参照
	bool switchFg_;					// スイッチフラグ
	MoveState moveState_;			// 移動状態
};

#endif // _LIFT_COMPONENT_H_