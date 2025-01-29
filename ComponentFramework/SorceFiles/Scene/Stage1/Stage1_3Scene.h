//==================================================
// [Stage1_3Scene.h] ステージ1-3シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ1-3を管理をするクラス
//==================================================
#ifndef STAGE1_3SCENE_H_
#define STAGE1_3SCENE_H_
/*----- インクルード -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// ステージ1-3シーンクラス
//--------------------------------------------------
class Stage1_3Scene : public SceneBase
{
public:
	Stage1_3Scene(GameManager* _gameManager);
	~Stage1_3Scene();

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

#endif // STAGE1_3SCENE_H_