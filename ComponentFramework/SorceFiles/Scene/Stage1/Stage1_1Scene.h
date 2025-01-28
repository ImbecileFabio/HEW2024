//==================================================
// [Stage1_1Scene.h] ステージ1-1シーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ステージ1-1を管理をするクラス
//==================================================
#ifndef STAGE1_1SCENE_H_
#define STAGE1_1SCENE_H_

/*----- インクルード -----*/
#include "../SceneBase.h"                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           

constexpr int gearCounter_1_1 = 1;
constexpr int hammerCounter_1_1 = 2;	// 叩ける上限

#include <array>

//--------------------------------------------------
// ステージ1-1シーンクラス
//--------------------------------------------------
class Stage1_1Scene :
	public SceneBase
{
public:
	Stage1_1Scene(GameManager* _gameManager);
	~Stage1_1Scene();

	void Init() override;
	void Uninit() override;
	void Update() override;


private:
	// 作ったオブジェクトをここに記述
	class BackGround* back_ground_{};	// 背景
	class Camera* camera_{};			// カメラ
	class HammerCursor* hammerCursor_{};	// ハンマーカーソル
	std::vector<class Item*> items_;	// アイテムリスト
	std::array<class Revolution*, 2> stageUIs_;	// 動きのないステージUI
	class SmokePipe* smoke_{};
};
#endif  // STAGE1_1SCENE_H_