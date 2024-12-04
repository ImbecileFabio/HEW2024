//==================================================
// [ColliderEventComponent.h] イベント処理を行うコンポーネントのベースヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：イベント処理を行うコンポーネントのベースクラス
//==================================================
#ifndef COLLIDER_EVENT_COMPONENT_H_
#define COLLIDER_EVENT_COMPONENT_H_
/*----- インクルード -----*/
#include "EventBaseComponent.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// コライダーのイベント処理を行うクラス
//--------------------------------------------------
class ColliderEventComponent :
    public EventBaseComponent
{
public:
	ColliderEventComponent(GameObject* _owner, int _updateOrder = 50) :EventBaseComponent(_owner, _updateOrder) {};
	~ColliderEventComponent() {};

	void Init(void) override {};
	void Uninit(void) override {};
	void Update(void) override {};

	TypeID GetComponentType(void) const override { return TypeID::ColliderEventComponent; }
};

#endif // COLLIDER_EVENT_COMPONENT_H_

