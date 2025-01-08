//==================================================
// [TransformComponent.cpp] 姿勢制御コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：姿勢制御コンポーネント
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>
#include "../../TileMapManager.h"

#include "TransformComponent.h"
#include "../GameObject.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
TransformComponent::TransformComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	std::cout << std::format("＜TransformComponent＞ -> Constructor\n");

	this->Init();
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
TransformComponent::~TransformComponent()
{
	std::cout << std::format("＜TransformComponent＞ -> Destructor\n");

}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void TransformComponent::Init(void)
{
	this->SetSize(TILE_SIZE_X, TILE_SIZE_Y);
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void TransformComponent::Uninit(void)
{
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void TransformComponent::Update(void)
{

}

