//==================================================
// [SpriteComponent.cpp] 描画コンポーネント 
// 著者：有馬啓太
//--------------------------------------------------
// 説明：四角を描画する
//==================================================
/*----- インクルード -----*/
#include "../../../StdAfx.h"
#include "SpriteComponent.h"
#include "../../GameObject.h"
#include "../../../GameManager.h"
#include "../../../Direct3D.h"


//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
SpriteComponent::SpriteComponent(GameObject* _owner, int _drawOrder)
	: RenderComponent(_owner)
	, draw_order_(_drawOrder)
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
// オブジェクトの名前をセット
//--------------------------------------------------
void SpriteComponent::SetObjectName(std::string objectName)
{
	object_name_ = objectName;
}

//--------------------------------------------------
// 描画処理
//--------------------------------------------------
void SpriteComponent::Draw(void)
{
	std::cout << object_name_ + "のスプライトが描画された\n";
}

//==================================================
//				End of FIle
//==================================================