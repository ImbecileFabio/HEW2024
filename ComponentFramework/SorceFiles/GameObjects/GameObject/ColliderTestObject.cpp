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
#include "../../InputManager.h"
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
	this->sprite_component_ = new SpriteComponent(this, TEXTURE_PATH "TestBlock.png");

	// 四角当たり判定コンポーネント
	this->circle_collider_component_ = new CircleColliderComponent(this);
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
ColliderTestObject::~ColliderTestObject(void)
{
	delete sprite_component_;
	delete circle_collider_component_;
}
//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void ColliderTestObject::UpdateGameObject(void)
{
	if (circle_collider_component_->testFg)
	{
		//transform_component_->position_.x = 100.0f;
	}
}
