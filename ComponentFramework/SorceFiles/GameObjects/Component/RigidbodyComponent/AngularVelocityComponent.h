//==================================================
// [AngularVelocityComponent.h] 角速度演算コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：物理演算をおこなうクラス
//		４．角速度、回転
// 
//		Update();								処理の実行
//	・角加速度
//		SetAngularAcceleration(VECTOR3型);			角加速度のセット
// 		GetAngularAcceleration() const;			角加速度の取得
// 		SetUseAngularAcceleration(true　or false);	角加速度のフラグ
// 		GetUseAngularAcceleration() const;			角加速度のフラグの取得
//	・角速度
//		SetAngularVelocity(VECTOR3型);				角速度のセット
// 		GetAngularVelocity() const;				角速度の取得
// 		SetUseAngularVelocity(true　or false);		角速度の使用フラグ
// 		GetUseAngularVelocity() const;				角速度の使用フラグの取得
//==================================================

#pragma once
#include "../RigidbodyComponent.h"
class AngularVelocityComponent :
    public RigidbodyComponent
{
private:
	float rotation_;
	float angularAcceleration_;		// -角加速度
	bool use_angularAcceleration_;							// -角加速度の使用フラグ
	float angularVelocity_;			// -角速度
	bool use_angularVelocity_;								// -角速度の使用フラグ
public:
	AngularVelocityComponent(GameObject* _owner, int _updateOrder = 50);
	~AngularVelocityComponent();

	void Init();
	void Uninit();
	void Update();

	// 角加速度
	void	SetAngularAcceleration(const float _angularAcceleration);
	float GetAngularAcceleration() const;
	void	SetUseAngularAcceleration(const bool _use_angularAcceleration);
	bool	GetUseAngularAcceleration() const;

	// 角速度
	void	SetAngularVelocity(const float _angularVelocity);
	float GetAngularVelocity() const;
	void	SetUseAngularVelocity(const bool _use_angularVelocity);
	bool	GetUseAngularVelocity() const;

	virtual TypeID GetComponentType() const override { return TypeID::AngularVelocityComponent; }
};

