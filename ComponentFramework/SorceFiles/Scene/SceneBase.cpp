//==================================================
// [SceneBase.cpp] シーンベースクラス
// 著者：有馬啓太
//--------------------------------------------------
// 説明：シーンの基底クラス
//==================================================

/*----- インクルード -----*/
#include <memory>
#include "SceneBase.h"

#include "../GameManager.h"
#include "../TileMapManager.h"
//--------------------------------------------------
// @param	_gameManager シーンの所有者, _sceneName シーン名
// @brief	コンストラクタ
//--------------------------------------------------
SceneBase::SceneBase(GameManager* _gameManager, std::string _sceneName)
	: game_manager_(_gameManager)	// 所有者
	, scene_name_(_sceneName)		// シーン名
{
	std::cout << std::format("\n[{}] -> Constructor\n", scene_name_);
	tile_map_manager_ = std::make_unique<TileMapManager>(game_manager_);
}

SceneBase::~SceneBase()
{
	std::cout << std::format("[{}] -> Destructor\n", scene_name_);




}

