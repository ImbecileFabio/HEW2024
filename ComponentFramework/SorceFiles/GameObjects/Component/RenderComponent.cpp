//==================================================
// [RenderComponent.cpp] 描画モジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：描画処理の定義
//==================================================

/*----- インクルード -----*/
#include <format>

#include "RenderComponent.h"
#include "../Component.h"


//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
RenderComponent::RenderComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	std::format("{}\n", "＜RenderComponent＞ -> Constructor");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
RenderComponent::~RenderComponent(void)
{
	std::format("{}\n", "＜RenderComponent＞ -> Destructor");

}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void RenderComponent::Uninit()
{
}
