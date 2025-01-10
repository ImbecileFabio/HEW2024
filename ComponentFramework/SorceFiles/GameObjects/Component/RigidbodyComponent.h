//==================================================
// [RigidbodyComponent.h] 物理演算コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：物理演算をおこなうクラス
//		１．位置、速度
//		２．角速度、回転
//		３．制約
//==================================================

#pragma once
#include "../Component.h"
#include "../GameObject.h"
#include "TransformComponent.h"
#include <iostream>
#include <format>
#include <SimpleMath.h>

class RigidbodyComponent :
    public Component
{
private:

public:
	RigidbodyComponent(GameObject* _owner, int _updateOrder = 50);
	~RigidbodyComponent();

	virtual void Init();
	virtual void Uninit();
	virtual void Update();		// すべての更新を行う
};

