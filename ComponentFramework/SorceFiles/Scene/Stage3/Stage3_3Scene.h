//==================================================
// [Stage3_3Scene.h] ステージ1-4シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ3-3を管理をするクラス
//==================================================
#ifndef STAGE3_3SCENE_H_
#define STAGE3_3SCENE_H_
/*----- インクルード -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// ステージ3-3シーンクラス
//--------------------------------------------------
class Stage3_3Scene : public SceneBase
{
public:
	Stage3_3Scene(GameManager* _gameManager);
	~Stage3_3Scene();

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

#endif // STAGE3_1SCENE_H_