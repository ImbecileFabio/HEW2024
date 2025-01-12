//==================================================
// [ResultScene.h] リザルトシーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：タイトルの管理をするクラス
//==================================================
#ifndef RESULT_SCENE_H_
#define RESULT_SCENE_H_

/*----- インクルード -----*/
#include "SceneBase.h"
#include <array>
/*----- 前方宣言 -----*/
class Revolution;
//--------------------------------------------------
// リザルトシーンクラス
//--------------------------------------------------
class ResultScene :
	public SceneBase
{
public:
	ResultScene(GameManager* _gameManager);
	~ResultScene();

	void Init() override;
	void Uninit() override;
	void Update() override;
private:
	class Camera*	  camera_{};	// カメラ
	Revolution*		backdrop_{};	// リザルトの背景
	Revolution* result_ribbon_{};	// リザルトのリボン
	std::array<Revolution*, 2> result_buttons_{};
	std::array<std::function<void()>, 2> select_button_functions_;
	int select_button_ = 0;

};

#endif  // RESULT_SCENE_H_