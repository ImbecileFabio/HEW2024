//==================================================
// [TitleScene.h] タイトルシーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：タイトルの管理をするクラス
//==================================================
#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

/*----- インクルード -----*/
#include "SceneBase.h"
#include <array>
//--------------------------------------------------
// タイトルシーンクラス
//--------------------------------------------------
class TitleScene :
    public SceneBase
{
public:
	enum class State
	{
		none = -1, 
		title,
		select,
		max,
	};
	TitleScene(GameManager* _gameManager);
	~TitleScene();

	void Init  () override;
	void Uninit() override;
	void Update() override;
private:
	State state_;
	class Camera*	 camera_{};			// カメラ
	class Revolution* title_{};
	Revolution* select_rough_{};	// ひとまず確認のためのセレクト画面ラフ

	std::array<std::array<int, 5>, 5> select_stages_;	// 5*5つ分のステージリスト
};

#endif  // TITLE_SCENE_H_