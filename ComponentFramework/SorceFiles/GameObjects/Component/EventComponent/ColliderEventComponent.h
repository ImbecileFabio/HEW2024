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
#include <map>
/*----- 前方宣言 -----*/
//--------------------------------------------------
// コライダーのイベント処理を行うクラス
//--------------------------------------------------
class ColliderEventComponent :
    public EventBaseComponent
{
public:
	ColliderEventComponent(GameObject* _owner, int _updateOrder = 50);
	~ColliderEventComponent();

	void Init(void)override;
	void Uninit(void) override;
	void Update(void) override {};

	void AllUpdate(GameObject* _other, size_t _id);
	void AddEvent(std::function<void(GameObject* _other)>& _event);	// とりあえずオブジェクトごと渡す
	void RemoveEvent();	// いらなくなったオブジェクトを消す予定

	TypeID GetComponentType(void) const override { return TypeID::ColliderEventComponent; }
private:
	std::map<size_t, std::function<void(GameObject*)>> functions_{};
};
#endif // COLLIDER_EVENT_COMPONENT_H_

