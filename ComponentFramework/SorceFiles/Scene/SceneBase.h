//==================================================
// [SceneBase.h] シーンベースクラス
// 著者：有馬啓太
//--------------------------------------------------
// 説明：シーンの基底クラス
//==================================================
#ifndef SCENE_BASE_H_
#define SCENE_BASE_H_

/*----- インクルード -----*/
#include <vector>
#include "../GameObjects/GameObject.h"

class GameManager;
//--------------------------------------------------
// シーンベースクラス
//--------------------------------------------------
class SceneBase
{
public:
	SceneBase(GameManager* _gameManager, std::string _sceneName);
	virtual ~SceneBase() {};

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;	// シーン切り替えの条件とかをSceneのUpdateに書く感じだとおもいます

protected:
	 GameManager* game_manager_{};

	 std::string scene_name_{};
};

#endif  // SCENE_BASE_H_