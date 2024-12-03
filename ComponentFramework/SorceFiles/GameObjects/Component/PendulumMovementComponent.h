//==================================================
// [PendulumMovementComponent.h] 振り子運動コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の運動の定義
//
//		PendulumPosition(VECTOR3型, float);	振り子の支点の座標と振り子の中心からの長さをセット・・・振り子の位置と角度を計算
//		PendulumAngle(float);					角加速度を入力・・・振り子の加減速処理
// 
// 予定：振り子運動（振り子の支点, 角度, 振り子運動の中心からの長さ）・・・振り子の位置を計算
// 　　　角度（最大角度, 角加速度）・・・振り子の角度を計算（角速度とかをなんやかんやする）
// 
// 支点の取得方法を相談する（支点のセッター？）ここで設定するのもあり？
// 振り子を静止から動かし始めた時の角加速度は0°の時にゲッターで取得する
//==================================================

#include "../Component.h"
#include "../GameObject.h"
#include "RigidbodyComponent/AngularVelocityComponent.h"
#include <iostream>
#include <SimpleMath.h>
#include <cmath>

#define PI 3.14f

class PendulumMovementComponent : public Component
{
private:
	DirectX::SimpleMath::Vector3 pemdulumPosition_;	// -位置
	float angle_;									// -振り子の角度
	//float length_;									// -振り子の中心からの長さ
	float pendulumRadian_;							// -振り子の角度（ラジアン）

public:
	PendulumMovementComponent(GameObject* _owner, int _updateOrder = 50);
	~PendulumMovementComponent();

	void Init();
	void Uninit();
	void Update();

	void PendulumPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length);
	void PendulumAngle(float _angularAcceleration);

	void ConversionRadian(float _angle);	// 角度をラジアンに変換

	//virtual TypeID GetComponentType() const override { return TypeID::PendulumMovementComponent; }
};