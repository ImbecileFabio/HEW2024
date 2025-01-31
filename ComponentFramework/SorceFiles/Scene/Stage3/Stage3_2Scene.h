//==================================================
// [Stage3_2Scene.h] ステージ1-4シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ3-2を管理をするクラス
//==================================================
#ifndef STAGE3_2SCENE_H_
#define STAGE3_2SCENE_H_
/*----- インクルード -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// ステージ3-2シーンクラス
//--------------------------------------------------
class Stage3_2Scene : public SceneBase
{
public:
	Stage3_2Scene(GameManager* _gameManager);
	~Stage3_2Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;
private:
	// 作ったオブジェクトをここに記述
	class BackGround* back_ground_{};			// 背景
	class Camera* camera_{};					// カメラ
	class HammerCursor* hammerCursor_{};		// ハンマーカーソル
	std::vector<class Item*> items_;			// アイテムリスト
};

#endif // STAGE3_2SCENE_H_