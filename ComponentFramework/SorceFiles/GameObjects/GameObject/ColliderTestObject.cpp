//==================================================
// [ColliderTestObject.cpp] 当たり判定テスト用オブジェクトのCPPファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：当たり判定を持ったテスト用オブジェクトの処理を定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>

#include "ColliderTestObject.h"
#include "../../GameManager.h"
#include "../Component.h"
#include "../Component/ColliderComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/TransformComponent.h"
#define TEXTURE_PATH "Asset/Texture/"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
ColliderTestObject::ColliderTestObject(GameManager* _gameManager)
	:GameObject(_gameManager)
{
	std::cout << std::format("{}\n", "＜ColliderTestObject＞ -> Constructor");

	// スプライトコンポーネント
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH"TestBlock.png");
	sprite_component_->SetObjectName("ColliderTestObject");

	// 四角当たり判定コンポーネント
	box_collider_component_ = new BoxColliderComponent(this);
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
ColliderTestObject::~ColliderTestObject(void)
{
	delete sprite_component_;
	delete box_collider_component_;
}
//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void ColliderTestObject::UpdateGameObject(void)
{

}
