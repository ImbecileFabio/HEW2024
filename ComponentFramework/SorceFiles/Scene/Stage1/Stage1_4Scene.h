//==================================================
// [Stage1_4Scene.h] ステージ1-4シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ1-4を管理をするクラス
//==================================================
#ifndef STAGE1_4SCENE_H_
#define STAGE1_4SCENE_H_
/*----- インクルード -----*/
#include "../SceneBase.h"


//--------------------------------------------------
// ステージ1-4シーンクラス
//--------------------------------------------------
class Stage1_4Scene : public SceneBase
{
public:
	Stage1_4Scene(GameManager* _gameManager);
	~Stage1_4Scene();

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

#endif // STAGE1_4SCENE_H_