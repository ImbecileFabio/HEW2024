//==================================================
// [PendulumMovementComponent.h] 振り子運動コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の運動の定義
//
// 予定：振り子運動（角度, 振り子運動の中心からの長さ）・・・振り子の位置を計算
// 　　　角度（最大角度, 1往復の時間）・・・振り子の角度を計算（角速度とかをなんやかんやする）
//==================================================

#include "../Component.h"
#include <iostream>

class PendulumMovementComponent : public Component
{
private:

public:
	PendulumMovementComponent(GameObject* _owner, int _updateOrder = 50);
	~PendulumMovementComponent();

	void Init();
	void Uninit();
	void Update();
};