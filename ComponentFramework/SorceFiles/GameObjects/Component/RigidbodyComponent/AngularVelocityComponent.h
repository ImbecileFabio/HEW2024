//==================================================
// [AngularVelocityComponent.h] 角速度演算コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：物理演算をおこなうクラス
//		４．角速度、回転
//==================================================

#pragma once
#include "../RigidbodyComponent.h"
class AngularVelocityComponent :
    public RigidbodyComponent
{
private:
	
public:
	AngularVelocityComponent(GameObject* _owner, int _updateOrder = 50);
	~AngularVelocityComponent();
	void Init();
	void Uninit();
	void Update();

	TypeID GetComponentType() const override { return TypeID::AngularVelocityComponent; }

};

