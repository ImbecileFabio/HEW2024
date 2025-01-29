//==================================================
// [Stage1_2Scene.h] ステージ1-2シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ1-2を管理をするクラス
//==================================================
#ifndef STAGE1_2SCENE_H_
#define STAGE1_2SCENE_H_
/*----- インクルード -----*/
#include "../SceneBase.h"

#include <array>
//--------------------------------------------------
// ステージ1-2シーンクラス
//--------------------------------------------------
class Stage1_2Scene :  public SceneBase
{
public:
	Stage1_2Scene(GameManager* _gameManager);
	~Stage1_2Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;


private:
	// 作ったオブジェクトをここに記述
	class BackGround* back_ground_{};			// 背景
	class Camera* camera_{};					// カメラ
	class HammerCursor* hammerCursor_{};		// ハンマーカーソル
	std::vector<class Item*> items_;			// アイテムリスト
	std::array<class Revolution*, 2> stageUIs_;	// 動きのないステージUI
};

#endif // STAGE1_2SCENE_H_