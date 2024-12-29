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
/*----- 定数 ------*/
constexpr int CHAPTER_MAX = 1;
constexpr int STAGE_MAX = 5;
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
		option,
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

	static int create_count;	// タイトルシーンが生成されたかどうかのカウント

	int chapter_ = 0;	// 章
	int stage_	 = 0;	// ステージ
	std::array<std::array<std::function<void()>, STAGE_MAX>, CHAPTER_MAX> select_stages_;	// 5*5つ分のステージ用添え字配列

	void StageSelect();
	void MoveSelect();
};

#endif  // TITLE_SCENE_H_