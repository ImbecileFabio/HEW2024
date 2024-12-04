//==================================================
// [PendulumMovementComponent.h] 振り子運動コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の運動の定義
//
//		Update(float, VECTOR型, float);	(角加速度, 支点の座標, 振り子の長さ)
//		SetPendulumAngle(float);			振り子の角度をセット（初期値用）
//		GetPendulumAngle();				振り子の角度を取得
// 
// 
//	※AngularVelocityComponentを先にGameObjectに追加する
// 
//	支点の取得方法を相談する（支点のセッター？）ここで設定するのもあり？
//	振り子を静止から動かし始めた時の角加速度は0°の時にゲッターで取得する
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
	float pendulumAngle_;							// -振り子の角度
	float pendulumRadian_;							// -振り子の角度（ラジアン）

public:
	PendulumMovementComponent(GameObject* _owner, int _updateOrder = 50);
	~PendulumMovementComponent();

	void Init();
	void Uninit();
	// Update(float, VECTOR型, float);	(角加速度, 支点の座標, 振り子の長さ)
	void Update() {};
	void Update(float _angle, DirectX::SimpleMath::Vector3 _fulcrum, float _length);

	void PendulumPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length);
	void PendulumAcceleration(float _angularAcceleration);

	void PendulumVelocity();				// 振り子の角度に角速度を適用
	void ConversionRadian(float _angle);	// 角度をラジアンに変換

	void  SetPendulumAngle(float _pendulumAngle);
	float GetPendulumAngle();

	virtual TypeID GetComponentType() const override { return TypeID::PendulumMovementComponent; }
};