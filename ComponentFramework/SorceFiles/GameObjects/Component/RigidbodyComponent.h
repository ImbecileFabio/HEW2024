//==================================================
// [RigidbodyComponent.h] 物理演算オブジェクト
// 著者：中谷凌也
//--------------------------------------------------
// 説明：物理演算をおこなうクラス
//==================================================

#pragma once
#include "../Component.h"
class RigidbodyComponent :
    public Component
{
public:
	void Init() {};
	void Uninit() {};
	void Update() {};
	void Draw() {};
	void SetVelocity(D3DXVECTOR3 velocity);					// 速度の設定
	D3DXVECTOR3 GetVelocity();
	void SetGravity(float gravity);							// 重力の設定
	float GetGravity();
	void SetAngularVelocity(D3DXVECTOR3 angularVelocity);	// 角速度の設定
	D3DXVECTOR3 GetAngularVelocity();
	void SetUseGravity(bool useGravity);					// 重力の有無
	bool GetUseGravity();
	void SetIsKinematic(bool isKinematic);					// このフラグが立っていると物理演算が無効になる
	bool GetIsKinematic();
	void SetFreezePosition(bool freezePosition);			// このフラグが立っていると位置の変更が無効になる
	bool GetFreezePosition();
	void SetFreezeRotation(bool freezeRotation);			// このフラグが立っていると回転の変更が無効になる
	bool GetFreezeRotation();
	void SetCollisionDetection(bool collisionDetection);	// 衝突検出の有無
	bool GetCollisionDetection();
	void SetConstraints(bool constraints);					// 制約の設定（他のオブジェクトに干渉するか否か的な）
	bool GetConstraints();
};

