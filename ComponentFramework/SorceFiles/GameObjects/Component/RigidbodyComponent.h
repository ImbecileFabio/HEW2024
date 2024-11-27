//==================================================
// [RigidbodyComponent.h] 物理演算オブジェクト
// 著者：中谷凌也
//--------------------------------------------------
// 説明：物理演算をおこなうクラス
//		１．位置、速度
//		２．重力
//		３．衝突検出
//		４．角速度、回転
//		５．制約
//		６．（デバッグ）
//==================================================

#pragma once
#include "../Component.h"
#include <iostream>
#include <format>
#include <SimpleMath.h>

using namespace DirectX;

class RigidbodyComponent :
    public Component
{
private:
	Vector3 position_;
	Vector3 acceleration_;
	bool use_acceleration_ = true;	// 使用フラグがtrueなら作用する
	Vector3 velocity_;
	bool use_velocity_ = true;

	//DirectX::XMFLOAT3 m_velocity;			// -速度
	//float m_gravity;						// -重力
	//DirectX::XMFLOAT3 m_angularVelocity;		// -角速度
	//bool m_useGravity;						// -重力の有無
	//bool m_isKinematic;						// -このフラグが立っていると物理演算が無効になる
	//bool m_freezePosition;					// -このフラグが立っていると位置の変更が無効になる
	//bool m_freezeRotation;					// -このフラグが立っていると回転の変更が無効になる
	//bool m_collisionDetection;				// -衝突検出の有無
	//bool m_constraints;						// -制約の設定（他のオブジェクトに干渉するか否か的な）
public:
	RigidbodyComponent(GameObject* _owner, int _updateOrder = 50);
	~RigidbodyComponent();

	void Init();
	void Uninit();
	void Updata();		// すべての更新を行う

	// 加速度
	void	SetAcceleration(const Vector3 _acceleration);
	Vector3 GetAcceleration() const;
	void	SetUseAcceleration(const bool _use_acceleration);
	bool	GetUseAcceleration() const;

	// 速度
	void	SetVelocity(const Vector3 _velocity);
	void	UpdateVelocity();
	Vector3	GetVelocity() const;
	void	SetUseVelocity(const bool _use_velocity);
	bool	GetUseVelocity() const;
	

	//void Init() {};
	//void Uninit() {};
	//void Update() {};
	//void Draw() {};
	//void SetVelocity(const DirectX::XMFLOAT3 velocity);				// 速度の設定
	//DirectX::XMFLOAT3 GetVelocity() const;
	//void SetGravity(float gravity);									// 重力の設定
	//float GetGravity();
	//void SetAngularVelocity(const DirectX::XMFLOAT3 angularVelocity);	// 角速度の設定
	//DirectX::XMFLOAT3 GetAngularVelocity() const;
	//void SetUseGravity(bool useGravity);								// 重力の有無
	//bool GetUseGravity();
	//void SetIsKinematic(bool isKinematic);							// このフラグが立っていると物理演算が無効になる
	//bool GetIsKinematic();
	//void SetFreezePosition(bool freezePosition);						// このフラグが立っていると位置の変更が無効になる
	//bool GetFreezePosition();
	//void SetFreezeRotation(bool freezeRotation);						// このフラグが立っていると回転の変更が無効になる
	//bool GetFreezeRotation();
	//void SetCollisionDetection(bool collisionDetection);				// 衝突検出の有無
	//bool GetCollisionDetection();
	//void SetConstraints(bool constraints);							// 制約の設定（他のオブジェクトに干渉するか否か的な）
	//bool GetConstraints();
};

