//==================================================
// [EventBaseComponent.h] イベント処理を行うコンポーネントのベースヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：イベント処理を行うコンポーネントのベースクラス
//==================================================
#ifndef EVENT_BASE_COMPONENT_H_
#define EVENT_BASE_COMPONENT_H_
/*----- インクルード -----*/
#include <memory>
#include <unordered_map>
#include <functional>
#include <string>
#include "../../Component.h"
#include "../../GameObject.h"
/*----- 構造体定義 -----*/
/*----- 前方宣言 -----*/
//--------------------------------------------------
// イベント処理を行うベースクラス　実体にして使わない
//--------------------------------------------------
class EventBaseComponent : public Component
{
public:
	EventBaseComponent(GameObject* _owner, int _updateOrder = 50) :Component(_owner, _updateOrder) {};
	~EventBaseComponent() = default;

	void Init(void) override {};
	void Uninit(void) override {};
	virtual void Update(void) override {};
	virtual void Update(GameObject* _other) {};
	// イベントコンポーネントごとのAddEventの引数違いをオーバーロードで置いとく
	virtual void AddEvent(std::function<void(GameObject*)> _event) {};

	TypeID GetComponentType(void) const override { return TypeID::EventBaseComponent; }
protected:
};
#endif // EVENT_BASE_COMPONENT_H_