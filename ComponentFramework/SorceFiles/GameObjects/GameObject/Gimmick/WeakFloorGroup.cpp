//=================================================================
// [WeakFloorGroup.cpp] WeakFloorGroupソースファイル
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：WeakFloorGroup実装
//=================================================================
/*----- インクルード -----*/
#include "WeakFloorGroup.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
WeakFloorGroup::WeakFloorGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "WeakFloorGroup")
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
WeakFloorGroup::~WeakFloorGroup(void)
{
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void WeakFloorGroup::InitGameObject(void)
{
}

//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void WeakFloorGroup::UpdateGameObject(void)
{
	// グループの方で脆いタイルを一括で変更をかける
	for (auto& tile : weakFloorTiles_)
	{

	}
}
//--------------------------------------------------
// @brief 脆い床タイルを追加
// @param _tile[追加するタイルオブジェクト]
//--------------------------------------------------
void WeakFloorGroup::AddWeakFlootTile(GameObject* _tile)
{
	weakFloorTiles_.emplace_back(_tile);
}

