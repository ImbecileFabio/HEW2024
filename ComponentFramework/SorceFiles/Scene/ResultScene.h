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

	void SetGearMaxNum(int _gearMaxNum) { oldGearMaxNum_ = _gearMaxNum; }
private:
	class Camera*	  camera_{};						// カメラ
	Revolution*		backdrop_{};						// リザルトの背景
	Revolution* result_ribbon_{};						// リザルトのリボン
	std::array<Revolution*, 5> result_gear_{};			// リザルトのギア
	std::array<Revolution*, 5> result_gear_frame_{};	// リザルトのギアフレーム

	std::array<Revolution*, 2> result_buttons_{};
	std::array<std::function<void()>, 2> select_button_functions_;
	int select_button_ = 0;

	bool isStart_ = false;	// Updateに一回だけ処理を行うためのフラグ
	int oldGearMaxNum_ = 0;	// ギアの最大数　シーンが変わると消えてしまうので切り替え時にリザルトに保存
};

#endif  // RESULT_SCENE_H_