//==================================================
// [EventDebugComponent.h] イベント挙動確認クラスのヘッダファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：コライダイベントが正しい挙動をしているかどうかをテストするクラス
//==================================================
#ifndef EVENT_DEBUG_COMPONENT_H_
#define EVENT_DEBUG_COMPONENT_H_
/*----- インクルード -----*/
#include "../../Component.h"
//--------------------------------------------------
// イベントデバック用コンポーネント
//--------------------------------------------------
class EventDebugComponent : public Component
{
public:
	EventDebugComponent(GameObject* _owner, int updateOrder = 50);
	~EventDebugComponent();

	void Init() override;
	void Uninit() override;
	void Update() override;

	TypeID GetComponentType(void) const override { return TypeID::EventDebugComponent; }
private:
};

#endif // EVENT_DEBUG_COMPONENT_H_

