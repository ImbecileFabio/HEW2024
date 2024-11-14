//==================================================
// [RenderComponent.cpp] 描画モジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：描画処理の定義
//==================================================

/*----- インクルード -----*/
#include "../../StdAfx.h"
#include "RenderComponent.h"


//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
RenderComponent::RenderComponent(std::shared_ptr<GameObject> _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
RenderComponent::~RenderComponent(void)
{
	std::cout << "＜RenderComponent＞ -> 破棄\n";

}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void RenderComponent::Uninit()
{
}
