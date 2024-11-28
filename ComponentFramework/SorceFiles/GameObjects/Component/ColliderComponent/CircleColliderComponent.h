//==================================================
// [BoxColliderComponent.h] 描画モジュールヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：当たり判定のコンポーネント　試作
//==================================================
#ifndef CIRCLE_COLLIDER_COMPONENT_H_
#define CIRCLE_COLLIDER_COMPONENT_H_
/*----- インクルード -----*/
#include <memory>
#include <iostream>
#include <SimpleMath.h>
#include "ColliderBaseComponent.h"
/*----- 構造体宣言 -----*/
struct CIRCLE
{
	DirectX::SimpleMath::Vector3 position;
	float radius;
};
//--------------------------------------------------
// 円の当たり判定
//--------------------------------------------------
class CircleColliderComponent :public ColliderBaseComponent
{
public:
	CircleColliderComponent(GameObject* _owner, int _updateOrder = 50);
	~CircleColliderComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	bool CheckCollisionCollider(ColliderBaseComponent* _other) override;
	bool CheckCollisionCollider(CircleColliderComponent* _other) override;
	bool CheckCollisionCollider(BoxColliderComponent* _other) override;

	TypeID GetComponentType(void) const override { return TypeID::CircleColliderComponent; }

	void SetPosition(DirectX::SimpleMath::Vector3 _pos) { circle_.position = _pos; }
	CIRCLE GetCircleSize(void) const { return circle_; }
private:
	CIRCLE circle_;	// 原点・半径
};

#endif 
// _CIRCLE_COLLIDER_COMPONENT_H_	
//{
	//	for (auto& otherCol : targetCols) {
	//		playerCol->CheckCollisionCollider(otherCol);
	//	}
	//}

	//class ColliderBaseComponent {
	//public:
	//	virtual bool CheckCollisionCollider(ColliderBaseComponent* _other) = 0;
	//	virtual bool CheckCollisionCollider(CircleColliderComponent* _other) = 0;
	//	virtual bool CheckCollisionCollider(BoxColliderComponent* _other) = 0;
	//}

	//bool CheckCollisionCollider(ColliderBaseComponent* _other) override {
	//	return _other->CheckCollisionCollider(this);
	//}
	//bool CheckCollisionCollider(CircleColliderComponent* _other) override {

	//}
	//bool CheckCollisionCollider(BoxColliderComponent* _other) override {

	//}