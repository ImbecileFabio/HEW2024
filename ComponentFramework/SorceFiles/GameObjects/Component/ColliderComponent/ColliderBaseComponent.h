//==================================================
// [ColliderBaseComponent.h] 描画モジュールヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：当たり判定のベースコンポーネント
// オブジェクトにColliderBaseComponentを追加して、
// インスタンス生成するときはBox||CircleComponentを使ってください
//==================================================
#ifndef COLLIDER_BASE_COMPONENT_H_
#define COLLIDER_BASE_COMPONENT_H_
/*----- インクルード -----*/
#include <memory>
#include <SimpleMath.h>
#include "../../Component.h"
/*----- 構造体宣言 -----*/
/*----- 前方宣言 -----*/
class CircleColliderComponent;
class BoxColliderComponent;
//--------------------------------------------------
// 当たり判定ベースクラス
//--------------------------------------------------
class ColliderBaseComponent :public Component
{
public:
	ColliderBaseComponent(GameObject* _owner, int _updateOrder = 50);
	~ColliderBaseComponent();

	void Init(void) override {};
	void Uninit(void) override {};
	void Update(void) override {};

	virtual bool CheckCollisionCollider(ColliderBaseComponent* _other) = 0;
	virtual bool CheckCollisionCollider(CircleColliderComponent* _other)= 0;
	virtual bool CheckCollisionCollider(BoxColliderComponent* _other) = 0;

	TypeID GetComponentType(void) const override { return TypeID::ColliderBaseComponent; }
protected:
};

#endif // COLLIDER_BASE_COMPONENT_H_