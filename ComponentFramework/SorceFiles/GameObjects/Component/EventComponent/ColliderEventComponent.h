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
	void Update(void) override;

	void AllTriggers();	// UPDATEで回してBOOLが{TRUEこれ・FALSE}になったら
	void AllActions();
	void AddEvent	(std::function<void()> _event);
	void RemoveEvent(std::function<void()> _event) {};

	TypeID GetComponentType(void) const override { return TypeID::ColliderEventComponent; }
private:
	std::list<std::function<void>> functions_{};	// 各オブジェクトが持つコライダーに反応して実行するのを関数
};

#endif // COLLIDER_EVENT_COMPONENT_H_

