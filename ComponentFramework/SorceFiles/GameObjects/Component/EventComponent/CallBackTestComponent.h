//==================================================
// [CallBackComponent.h] コールバックが動作するかテストするコンポーネント
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：コールバックテスト用コンポーネント
//==================================================
#ifndef CALLBACK_COMPONENT_H_
#define CALLBACK_COMPONENT_H_
/*----- インクルード -----*/
#include "../../Component.h"
/*----- 構造体宣言 -----*/
/*----- 前方宣言 -----*/
//--------------------------------------------------
// コールバックテスト用クラス
//--------------------------------------------------
class CallBackComponent :public Component
{
public:
	CallBackComponent(GameObject* _owner, int _updateOrder = 50);
	~CallBackComponent();
	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;
private:
};
#endif // CALLBACK_COMPONENT_H_