//==================================================
// [TitleScene.h] タイトルシーン
// 著者：有馬啓太
//--------------------------------------------------
// 説明：タイトルの管理をするクラス
//==================================================
#ifndef TITLE_SCENE_H_
#define TITLE_SCENE_H_

/*----- インクルード -----*/
#include "SceneBase.h"
#include <array>
/*----- 前方宣言 ------*/
class Revolution;
/*----- 定数 ------*/
constexpr int CHAPTER_MAX = 3;
constexpr int STAGE_MAX = 4;

//--------------------------------------------------
// タイトルシーンクラス
//--------------------------------------------------
class TitleScene :
    public SceneBase
{
public:
	enum class State
	{
		none = -1,
		title,
		option,
		select,
		end,
		max,
	};
	TitleScene(GameManager* _gameManager);
	~TitleScene();

	void Init  () override;
	void Uninit() override;
	void Update() override;

	int GetCreateCount() { return create_count; }
private:
	State state_;
	class Camera*	   camera_;					// カメラ
	Revolution*		 backdrop_;					// タイトルとセレクトの背景
	// タイトル周りのオブジェクトと変数
	Revolution* title_logo_;					// タイトルのロゴ
	Revolution* title_ribbon_;					// ボタンの背景リボン
	Revolution* title_cursor_;					// タイトルのカーソル
	std::array<Revolution*, 3> title_buttons_;	// タイトルのボタン
	int title_select_button_ = 0;				// タイトルのボタンの添え字
	static int create_count;					// タイトルシーンが生成されたかどうかのカウント
	// セレクト画面周りのオブジェクトと変数
	Revolution* select_left_button_;			// LBボタン
	Revolution* select_right_button_;			// RBボタン
	Revolution* select_option_button_;			// オプションボタン
	Revolution* select_return_button_;			// 戻るボタン
	Revolution* select_chapter_left;			// LBボタンに表示されるチャプターナンバー
	Revolution* select_chapter_right;			// RBボタンに表示されるチャプターナンバー
	Revolution* select_chapter_center;			// 現在の選択チャプター（中央）に表示されるチャプターナンバー
	Revolution* select_numbers_s_;				// ステージナンバーのSサイズ
	Revolution* select_numbers_m_left_;			// ステージナンバー（左）
	Revolution* select_numbers_m_center_;		// ステージナンバー（中）
	Revolution* select_numbers_m_right_;		// ステージナンバー（右）
	Revolution* select_numbers_w_;				// ステージナンバーのLサイズ
	int chapter_ = 0;							// 章
	int stage_	 = 0;							// ステージ
	std::array<std::array<std::function<void()>, STAGE_MAX>, CHAPTER_MAX> select_stages_;	// 5*5つ分のステージ用添え字配列
	// オプションボタン周りのオブジェクトと変数
	std::array<Revolution*, 10> option_images_;	// オプション画面の動きがなさそうなもの
	Revolution* option_ball_slider_bgm_;		// BGMボールスライダー
	Revolution* option_ball_slider_se_;			// SEボールスライダー
	Revolution* option_stick_slider_bgm_;		// BGMスティックスライダー
	Revolution* option_stick_slider_se_;		// SEスティックスライダー
	void StageSelect();
	void MoveSelect();
};

#endif  // TITLE_SCENE_H_