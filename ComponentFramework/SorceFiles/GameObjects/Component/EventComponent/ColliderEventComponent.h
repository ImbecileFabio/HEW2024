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
	ColliderEventComponent(GameObject* _owner, int _updateOrder = 50);
	~ColliderEventComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update() override {};

	void AllUpdate(GameObject* _other);

	void AllActions() {};	// TRUEになった関数を実行
	void AddEvent	(std::function<void(GameObject*)> _event);	// とりあえずオブジェクトごと渡す
	void RemoveEvent(std::function<void(GameObject*)> _event) {};

	TypeID GetComponentType(void) const override { return TypeID::ColliderEventComponent; }
private:
	std::vector<std::function<void(GameObject*)>> functions_{};	// イベントを格納するリスト
};
#endif // COLLIDER_EVENT_COMPONENT_H_

