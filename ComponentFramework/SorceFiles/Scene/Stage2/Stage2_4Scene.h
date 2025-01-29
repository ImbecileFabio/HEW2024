//==================================================
// [Stage2_4Scene.h] ステージ1-4シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ2-4を管理をするクラス
//==================================================
#ifndef STAGE2_4SCENE_H_
#define STAGE2_4SCENE_H_
/*----- インクルード -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// ステージ2-4シーンクラス
//--------------------------------------------------
class Stage2_4Scene : public SceneBase
{
public:
	Stage2_4Scene(GameManager* _gameManager);
	~Stage2_4Scene();

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

#endif // STAGE2_4SCENE_H_