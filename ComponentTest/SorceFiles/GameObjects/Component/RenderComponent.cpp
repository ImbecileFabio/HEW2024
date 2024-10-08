//==================================================
// [RenderComponent.cpp] レンダリングコンポーネントのベースコンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：レンダリングコンポーネントに共通する処理の定義
//==================================================

/*----- インクルード -----*/
#include "../../StdAfx.h"
#include "RenderComponent.h"


RenderComponent::RenderComponent(GameObject* owner, int updateOrder)
	: Component(owner, updateOrder)
{
}

RenderComponent::~RenderComponent(void)
{
}


//==================================================
//				End of FIle
//==================================================
