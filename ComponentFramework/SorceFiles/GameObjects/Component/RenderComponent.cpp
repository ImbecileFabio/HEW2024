//==================================================
// [RenderComponent.cpp] 描画モジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：描画処理の定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>

#include "RenderComponent.h"
#include "../Component.h"


//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
RenderComponent::RenderComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	std::cout << std::format("＜RenderComponent＞ -> Constructor\n");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
RenderComponent::~RenderComponent(void)
{
	std::cout << std::format("＜RenderComponent＞ -> Destructor\n");

}
