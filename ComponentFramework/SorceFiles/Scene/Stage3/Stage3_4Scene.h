//==================================================
// [Stage3_4Scene.h] ステージ3-4シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ3-4を管理をするクラス
//==================================================
#ifndef STAGE3_4SCENE_H_
#define STAGE3_4SCENE_H_
/*----- インクルード -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// ステージ3-4シーンクラス
//--------------------------------------------------
class Stage3_4Scene : public SceneBase
{
public:
	Stage3_4Scene(GameManager* _gameManager);
	~Stage3_4Scene();

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

#endif // STAGE3_4SCENE_H_