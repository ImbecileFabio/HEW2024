//==================================================
// [Stage3_1Scene.h] ステージ1-4シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ3-1を管理をするクラス
//==================================================
#ifndef STAGE3_1SCENE_H_
#define STAGE3_1SCENE_H_
/*----- インクルード -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// ステージ3-1シーンクラス
//--------------------------------------------------
class Stage3_1Scene : public SceneBase
{
public:
	Stage3_1Scene(GameManager* _gameManager);
	~Stage3_1Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;

	enum STATE {
		Game,
		Result,
		Pouse,
		Rewind
	};
private:
	STATE state_;

	// 作ったオブジェクトをここに記述
	class BackGround* back_ground_{};			// 背景
	class Camera* camera_{};					// カメラ
	class HammerCursor* hammerCursor_{};		// ハンマーカーソル
	std::vector<class Item*> items_;			// アイテムリスト
	std::array<class Revolution*, 2> stageUIs_;	// 動きのないステージUI
};

#endif // STAGE3_1SCENE_H_