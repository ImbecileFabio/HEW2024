//==================================================
// [PendulumComponent.cpp] 振り子モジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：振り子の処理の定義
//==================================================

/*----- インクルード -----*/
#include <format>

#include "PendulumComponent.h"
#include "../Component.h"


//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
PendulumComponent::PendulumComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	std::format("＜PendulumComponent＞ -> Constructor\n");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
PendulumComponent::~PendulumComponent(void)
{
	std::format("＜PendulumComponent＞ -> Destructor\n");

}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void PendulumComponent::Uninit()
{
}
