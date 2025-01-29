//==================================================
// [Stage2_3Scene.h] ステージ1-4シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ2-3を管理をするクラス
//==================================================
#ifndef STAGE2_3SCENE_H_
#define STAGE2_3SCENE_H_
/*----- インクルード -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// ステージ2-3シーンクラス
//--------------------------------------------------
class Stage2_3Scene : public SceneBase
{
public:
	Stage2_3Scene(GameManager* _gameManager);
	~Stage2_3Scene();

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

#endif // STAGE2_3SCENE_H_