//==================================================
// [SceneBase.cpp] シーンベースクラス
// 著者：有馬啓太
//--------------------------------------------------
// 説明：シーンの基底クラス
//==================================================

/*----- インクルード -----*/
#include "SceneBase.h"

#include "../GameManager.h"
//--------------------------------------------------
// @param	シーンの所有者, シーン名
// @brief	コンストラクタ
//--------------------------------------------------
SceneBase::SceneBase(GameManager* _gameManager, std::string _sceneName)
	: game_manager_(_gameManager)	// 所有者
	, scene_name_(_sceneName)		// シーン名
{
	std::cout << std::format("\n[{}] -> Constructor\n", scene_name_);
}

