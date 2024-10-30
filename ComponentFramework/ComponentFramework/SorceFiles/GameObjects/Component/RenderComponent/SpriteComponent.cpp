//==================================================
// [SpriteComponent.h] 描画コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：とても描画コンポーネントの宣言
//==================================================

/*----- インクルード -----*/
#include "../../../StdAfx.h"
#include "SpriteComponent.h"
#include "../../GameObject.h"
#include "../../../GameManager.h"
#include "../../../Renderer.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
SpriteComponent::SpriteComponent(GameObject* owner, int drawOrder)
	: RenderComponent(owner)
	, draw_order_(draw_order_)
{
	this->owner_->GetGameManager()->GetRenderer()->AddSprite(this);

	object_name_ = std::string("不明なオブジェクト");
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
SpriteComponent::~SpriteComponent(void)
{
}

//--------------------------------------------------
// 名前を定義する関数
//--------------------------------------------------
void SpriteComponent::SetObjectName(std::string _objectName)
{
	object_name_ = _objectName;
}

void SpriteComponent::Draw(void)
{
	std::cout << "[" +  object_name_ + "] -> 描画\n";




}
