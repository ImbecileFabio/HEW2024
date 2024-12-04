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
#include "../../Component.h"
/*----- 構造体定義 -----*/
/*----- 前方宣言 -----*/
//--------------------------------------------------
// イベント処理を行うベースクラス　実体にして使わないよ☆彡
//--------------------------------------------------
class EventBaseComponent : public Component
{
public:
	EventBaseComponent(GameObject* _owner, int _updateOrder = 50) :Component(_owner, _updateOrder) {};
	~EventBaseComponent() {};

	void Init(void) override {};
	void Uninit(void) override {};
	void Update(void) override {};

	TypeID GetComponentType(void) const override { return TypeID::ColliderBaseComponent; }	// TODOあとで変える
};
#endif // EVENT_BASE_COMPONENT_H_