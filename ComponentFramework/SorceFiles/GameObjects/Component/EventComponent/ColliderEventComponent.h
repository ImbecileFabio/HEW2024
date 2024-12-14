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
	void AddEvent(size_t _id, std::function<void(GameObject* _other)>& _event) override;	// とりあえずオブジェクトごと渡す
	void RemoveEvent();	// いらなくなったオブジェクトを消す予定

	size_t GetID(void) { return id_; }

	TypeID GetComponentType(void) const override { return TypeID::ColliderEventComponent; }
private:
	size_t id_{};
	std::map<size_t, std::function<void(GameObject*)>> functions_{};
};
#endif // COLLIDER_EVENT_COMPONENT_H_

