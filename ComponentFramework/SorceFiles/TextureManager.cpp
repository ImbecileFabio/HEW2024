//=================================================================
// [TextureManager.cpp] テクスチャ管理クラス
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：そんな感じ
//=================================================================

/*----- インクルード -----*/
#include <iostream>
#include "TextureManager.h"
#include "TileMapManager.h"
#include "SubSystem/stb_image.h"
#include "Renderer.h"

//-----------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------
TextureManager::TextureManager()
{
}

//-----------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------
TextureManager::~TextureManager()
{
	this->ClearCache();
}

void TextureManager::RegisterTextureInfo(const std::string& _textureName, const TextureInfo& _textureInfo)
{
	texture_info_[_textureName] = _textureInfo;
}

//-----------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------
void TextureManager::Init()
{
	RegisterAllTextures();
}

//-----------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------
void TextureManager::Uninit()
{
	ClearCache();
}


//-----------------------------------------------------------------
// @param  _imgName 画像名, _fileName ファイルパス
// @brief  テクスチャの登録
//-----------------------------------------------------------------
// アニメーション付き
void TextureManager::RegisterTexture(const std::string& _imgName, const std::string& _fileName, bool _loopFlg, int _cutU, int _cutV, float _anmSpeed, int _totalFrame)
{
	RegisterTexture(_imgName, _fileName, DirectX::SimpleMath::Vector2(0.0f, 0.0f), DirectX::SimpleMath::Vector2(1.0f, 1.0f), _loopFlg, _cutU, _cutV, _anmSpeed, _totalFrame);
}
// すべて
void TextureManager::RegisterTexture(const std::string& _textureName, const std::string& _fileName, const DirectX::SimpleMath::Vector2& _offsetPos, const DirectX::SimpleMath::Vector2& _offsetSize, bool _loopFlg, int _cutU, int _cutV, float _anmSpeed, int _totalFrame)
{
	texture_info_[_textureName] = { _fileName, _offsetPos, _offsetSize, _loopFlg, _cutU, _cutV, _anmSpeed , _totalFrame };
}

//-----------------------------------------------------------------
// @param  _imgName 画像名
// @brief  読み込んだテクスチャの取得
// @return 存在していればit->second, なければ生成してtexture, 生成できなければnullptr
//-----------------------------------------------------------------
std::shared_ptr<Texture> TextureManager::GetTexture(const std::string& _textureName)
{

	// キャッシュに存在する場合
	auto it = texture_cache_.find(_textureName);
	if (it != texture_cache_.end()) {
		// LRUリストを更新
		lru_list_.erase(lru_map_[_textureName]);
		lru_list_.push_front(_textureName);
		lru_map_[_textureName] = lru_list_.begin();
		return it->second;
	}

	// 新規テクスチャの生成
	auto texInfo = texture_info_[_textureName];
	auto texture = std::make_shared<Texture>(texInfo.offsetPos, texInfo.offsetSize, texInfo.loop, texInfo.cutU, texInfo.cutV, texInfo.animationSpeed, texInfo.totalFrame);
	if (texture->Load(texInfo.filePath)) {
		// キャッシュサイズの確認
		if (texture_cache_.size() >= max_cache_size_) {
			// 最後に使用された要素を削除
			std::string old_texture = lru_list_.back();
			lru_list_.pop_back();
			lru_map_.erase(old_texture);
			texture_cache_.erase(old_texture);
		}

		// 新しいテクスチャをキャッシュに追加
		texture_cache_[_textureName] = texture;
		lru_list_.push_front(_textureName);
		lru_map_[_textureName] = lru_list_.begin();

		return texture;
	}

	// 失敗
	std::cout << std::format("＜TextureManager＞ -> {} GetTexture Error\n", _textureName);

}

//-----------------------------------------------------------------
// @param  _imgName 画像名
// @brief	テクスチャのプリロード
//-----------------------------------------------------------------
void TextureManager::LoadTexture(const std::string& _textureName)
{
	// キャッシュに存在する場合
	auto it = texture_cache_.find(_textureName);
	if (it != texture_cache_.end()) {
		// LRUリストを更新
		lru_list_.erase(lru_map_[_textureName]);
		lru_list_.push_front(_textureName);
		lru_map_[_textureName] = lru_list_.begin();
		return;
	}

	// 新規テクスチャの生成
	auto texInfo = texture_info_[_textureName];
	auto texture = std::make_shared<Texture>(texInfo.offsetPos, texInfo.offsetSize, texInfo.loop, texInfo.cutU, texInfo.cutV, texInfo.animationSpeed, texInfo.totalFrame);
	if (texture->Load(texInfo.filePath)) {
		// キャッシュサイズの確認
		if (texture_cache_.size() >= max_cache_size_) {
			// 最後に使用された要素を削除
			std::string old_texture = lru_list_.back();
			lru_list_.pop_back();
			lru_map_.erase(old_texture);
			texture_cache_.erase(old_texture);
		}

		// 新しいテクスチャをキャッシュに追加
		texture_cache_[_textureName] = texture;
		lru_list_.push_front(_textureName);
		lru_map_[_textureName] = lru_list_.begin();

		return;
	}

	// 失敗
	std::cout << std::format("＜TextureManager＞ -> {} GetTexture Error\n", _textureName);

}

//-----------------------------------------------------------------
// @brief  すべてのテクスチャを登録する
// 
// テクスチャのoffsetを設定する際
// 
// ポジション: 何pxずらせばオブジェクトの中心になるか
// 例： 画像のサイズの高さが 80px で、オブジェクトの影が上に 10px、下に 6px ある場合
//		上方向に 2px ずらせばいいので
//		{0.0f, 2.0f} を記述してね。
//
// サイズ: 画像サイズを何倍にすればタイルのサイズに合うか
// 例： 画像のサイズ高さが 80px で、影を除いたオブジェクトのサイズが 64px の場合
// 		オブジェクトのサイズを 80px にしたいので、
//		80 / 64 = 1.25f で {1.0f, 1.25f} を記述してね。
// 
// 少々複雑でごめんなさい
//-----------------------------------------------------------------
void TextureManager::RegisterAllTextures()
{
	//名前が適当なもの多いので調整しつつお願いします

	// Hogehoge
	RegisterTexture("hoge", TEXTURE_PATH"hogehoge.png");
	RegisterTexture("piyo", TEXTURE_PATH"piyo.jpg", true, 8, 12, 0.05f);
	RegisterTexture("fade_out", TEXTURE_PATH"fadeout.png", false, 5, 5, 0.1f);


	// インゲームのオブジェクト系
	/*--------------- ロボット ---------------*/
	RegisterTexture("robot_drop", TEXTURE_PATH"robot/v03/robot_dorp_01.png", false, 3, 1, 0.05f, 3);	// 落下
	RegisterTexture("robot_still", TEXTURE_PATH"robot/v03/robot_still_01.png");	// 静止
	RegisterTexture("robot_walk", TEXTURE_PATH"robot/v03/robot_walk_01.png", true, 2, 1, 0.5f, 2);	// 歩行

	/*--------------- ギア ---------------*/
	RegisterTexture("gear", UI_PATH"v02/gear_01.png", { 0.0f, 15.0f }, { 1.0f, 1.0f });

	/*--------------- 振り子 ---------------*/
	RegisterTexture("ball", TEXTURE_PATH"huriko/v02/ball_01.png", { 0.0f, 0.0f }, { 1.25f, 1.25f });		// ボール
	RegisterTexture("stick", TEXTURE_PATH"huriko/v03/stick_01.png", { 0.0f, 0.0f }, { 0.75f, 1.0f });	// 棒

	/*--------------- タイル ---------------*/
	// 床
	RegisterTexture("tile_center", TEXTURE_PATH"tile/v02/tile_center_01.png", { 0.0f, -3.0f }, { 1.0f, 1.501f });	// 中央
	RegisterTexture("tile_left", TEXTURE_PATH"tile/v02/tile_left_01.png", { -6.0f, -3.0f }, { 1.2f, 1.5f });	// 左
	RegisterTexture("tile_right", TEXTURE_PATH"tile/v02/tile_right_01.png", { 6.0f, -3.0f }, { 1.2f, 1.5f });	// 右
	// 壁
	RegisterTexture("wall_left", TEXTURE_PATH"tile/v02/tile_wall_01.png", { 9.0f, 0.0f }, { 1.2f, 1.0f });		// 壁（左向き）
	RegisterTexture("wall_right", TEXTURE_PATH"tile/v02/tile_wall_01.png", { -9.0f, 0.0f }, { 1.2f, 1.0f });		// 壁（右向き）


	/*--------------- ギミック ---------------*/
	// リフト
	RegisterTexture("lift_floor_center", GIMMICK_PATH"lift/v02/lift_floor_center_01.png", { 0.0f, 8.0f }, { 1.0f, 1.25f });	// 中央
	RegisterTexture("lift_floor_left", GIMMICK_PATH"lift/v02/lift_floor_left_01.png", { -7.9f, 8.0f }, { 1.25f, 1.25f });		// 左
	RegisterTexture("lift_floor_right", GIMMICK_PATH"lift/v02/lift_floor_right_01.png", { 8.0f, 8.0f }, { 1.25f, 1.25f });	// 右
	RegisterTexture("lift_circle", GIMMICK_PATH"lift/v02/lift_circle_01.png");					// 留め具
	RegisterTexture("lift_rail", GIMMICK_PATH"lift/v02/lift_rail_01.png");						// レール
	// 脆い床 （氷だったもの）
	RegisterTexture("weakfloor_center", GIMMICK_PATH"weakfloor/v01/weakfloor_center_01.png", { 0.0f, -3.0f }, { 1.0f, 1.501f });	// 中央
	RegisterTexture("weakfloor_left", GIMMICK_PATH"weakfloor/v01/weakfloor_left_01.png", { -6.0f, -3.0f }, { 1.2f, 1.5f });		// 左
	RegisterTexture("weakfloor_right", GIMMICK_PATH"weakfloor/v01/weakfloor_right_01.png", { 6.5f, -3.0f }, { 1.2f, 1.5f });	// 右
	// 鉄柱
	RegisterTexture("steelpillar_floor_center", GIMMICK_PATH"steelpillar/v02/steelpillar_floor_center_01.png", { 0.0f, -8.0f }, { 1.0f, 1.25f });			// 床, 中央
	RegisterTexture("steelpillar_floor_end_01", GIMMICK_PATH"steelpillar/v02/steelpillar_floor_end_01.png", { -7.9f, -8.0f }, { 1.25f, 1.25f });			// 床, 左
	RegisterTexture("steelpillar_floor_end_02", GIMMICK_PATH"steelpillar/v02/steelpillar_floor_end_02.png", { 8.0f, -8.0f }, { 1.25f, 1.25f });			// 床, 右

	RegisterTexture("steelpillar_pillar_top", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_top_01.png", { 15.5f, 0.0f }, { 1.0f, 1.0f });			// 柱, 上
	RegisterTexture("steelpillar_pillar_bottom", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_bottom_01.png", { 15.5f, 0.0f }, { 1.0f, 1.0f });			// 柱, 下
	RegisterTexture("steelpillar_pillar_break", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_break_01.png", { 15.5f, 0.0f }, { 1.0f, 1.0f }, false, 4, 4, 0.5f, 15);			// 柱, 壊れ
	//RegisterTexture("steelpillar_pillar_break", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_break_01.png", { 15.5f, 0.0f }, { 1.0f, 1.0f }, false, 4, 4, 0.001f, 15);			// 柱, 壊れ
	RegisterTexture("steelpillar_pillar_normal", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_normal_01.png", { 15.5f, 0.0f }, { 1.0f, 2.0f });				// 柱, 通常
	RegisterTexture("steelpillar_pillar_still", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_still_01.png", { 15.5f, 0.0f }, { 1.0f, 1.0f });			// 柱, 欠け
	// 煙
	RegisterTexture("smoke00", GIMMICK_PATH"smoke/v01/smoke_anime_scale_01.png", { 0.0f, 0.0f }, { 2.25f, 1.0f }, true, 4, 8, 0.05f, 31);	// 煙本体
	RegisterTexture("smoke01", GIMMICK_PATH"smoke/v01/smoke_bace_back_01.png", { 0.0f, 6.0f }, { 2.0f, 1.25f });		// 柱の奥
	RegisterTexture("smoke02", GIMMICK_PATH"smoke/v01/smoke_bace_front_01.png", { 0.0f, 6.0f }, { 2.0f, 1.25f });	// 柱の手前
	// 滑車
	RegisterTexture("pulley", GIMMICK_PATH"pulley/v01/pulley_01.png");
	// タイムゾーン
	RegisterTexture("timezone", TEXTURE_PATH"kouka/v02/pendulum_area_01.png");	// 青い円

	/*--------------- エフェクト ---------------*/
	RegisterTexture("smoke_impact_effect", GIMMICK_PATH"steelpillar/v02/smoke_impact_effect_01.png", {0.0f, 0.0f}, {4.0f, 1.0f}, false, 4, 5, 0.02f, 16);	// 接地時エフェクト



	// その他の背景、UIなど
	/*--------------- バックドロップ ---------------*/
	RegisterTexture("backdrop_01", TEXTURE_PATH"backdrop/v02/backdrop_01.png");
	RegisterTexture("backdrop_02", TEXTURE_PATH"backdrop/v02/backdrop_02.png");

	/*--------------- UI ---------------*/
	// ハンマー
	RegisterTexture("hammer", UI_PATH"v01/hammer_01.png");
	// ヒットエフェクト
	RegisterTexture("hammer_hit_effect", UI_PATH"v02/hit_effect_01.png", false, 4, 4, 0.1f, 16);
	// ギア
	RegisterTexture("gearUI", UI_PATH"v02/gear_01.png");
	// 数字
	RegisterTexture("numbers", UI_PATH"v02/numbers_01.png", false, 4, 3, 1.0f, 10);
	// ポーズボタン
	RegisterTexture("pause_button", UI_PATH"v02/pause_button_01.png");
	// ステージUI
	RegisterTexture("stageUI", UI_PATH"v02/stage_ui_01.png");
	/*--------------- SCENE ---------------*/
	// 操作説明画像
	RegisterTexture("instruction_window", SCENE_PATH"instruction/v02/window_instruction_01.png");
	// ロード画面
	RegisterTexture("loading_backdrop", SCENE_PATH"loading/v01/loading_startup_01.png");
	// フェード...?
	RegisterTexture("fade_out", SCENE_PATH"loading/v01/loading_result_01.png", false, 5, 6, 0.02f, 30);
	RegisterTexture("fade_in", SCENE_PATH"loading/v01/loading_result_02.png", false, 4, 5, 0.02f, 20);
	// 真っ黒画像
	RegisterTexture("black_backdrop", SCENE_PATH"loding/v01/black_01.png");
	// チュートリアル画像
	RegisterTexture("tutorial_01", SCENE_PATH"tutorial/v02/tutorial_01.png");
	RegisterTexture("tutorial_02", SCENE_PATH"tutorial/v02/tutorial_02.png");
	// チームロゴ
	//RegisterTexture("introduction_backdrop", SCENE_PATH"introduction/v01/backdrop_introduction_01.png");
	//RegisterTexture("introduction_teamlogo", SCENE_PATH"introduction/v01/teamlogo_01.png");
	// オプション
	RegisterTexture("option_window", SCENE_PATH"option/v01/window_option_01.png");
	RegisterTexture("option_return", SCENE_PATH"option/v01/return_option_01.png");
	RegisterTexture("option_frame_slider", SCENE_PATH"option/v01/frame_slider_01.png");
	RegisterTexture("option_stick_slider", SCENE_PATH"option/v01/color_stick_slider_01.png");
	RegisterTexture("option_bgm_button", SCENE_PATH"option/v01/button_bgm_01.png");
	RegisterTexture("option_se_button", SCENE_PATH"option/v01/button_se_01.png");
	RegisterTexture("option_ball_slider", SCENE_PATH"option/v01/ball_slider_01.png");
	RegisterTexture("option_arrow_right", SCENE_PATH"option/v01/arrow_right_01.png");
	RegisterTexture("option_arrow_left", SCENE_PATH"option/v01/arrow_left_01.png");
	// ポーズ
	RegisterTexture("pose_window", SCENE_PATH"pose/v01/window_pose_01.png");
	RegisterTexture("pose_return_game", SCENE_PATH"pose/v01/return_game_button_01.png");
	RegisterTexture("pose_restart", SCENE_PATH"pose/v01/restart_button_01.png");
	RegisterTexture("pose_select", SCENE_PATH"pose/v01/stage_select_button_01.png");
	RegisterTexture("pose_instruction", SCENE_PATH"pose/v01/instruction_button_01.png");
	RegisterTexture("pose_option", SCENE_PATH"pose/v01/option_button_01.png");

	// リザルト
	RegisterTexture("result_backdrop", SCENE_PATH"result/v01/backdrop_result_01.png");
	RegisterTexture("result_front_ribbon", SCENE_PATH"result/v01/front_ribbon_01.png");
	RegisterTexture("result_select", SCENE_PATH"result/v01/select_button_01.png");
	RegisterTexture("result_next", SCENE_PATH"result/v01/next_button_01.png");
	RegisterTexture("result_gear", SCENE_PATH"result/v01/result_gear_01.png");
	RegisterTexture("result_gear_frame", SCENE_PATH"result/v01/result_gear_frame_01.png");
	// タイトル
	RegisterTexture("title_ribbon", SCENE_PATH"title/v01/ribbon_title_01.png");
	RegisterTexture("title_logo", SCENE_PATH"title/v01/titlelogo_01.png");
	RegisterTexture("title_start", SCENE_PATH"title/v01/start_button_01.png");
	RegisterTexture("title_end", SCENE_PATH"title/v01/end_button_01.png");
	RegisterTexture("title_option", SCENE_PATH"title/v01/option_button_01.png");
	RegisterTexture("title_cursor", SCENE_PATH"title/v01/cursor_01.png");
	RegisterTexture("transition_01", SCENE_PATH"title/v01/transition_01.png");
	RegisterTexture("transition_02", SCENE_PATH"title/v01/transition_02.png", 10, 6, 0.05f, 60);

	// ステージセレクト
	RegisterTexture("stageselect_option", SCENE_PATH"stageselect/v01/option_select_button_01.png");
	RegisterTexture("stageselect_return", SCENE_PATH"stageselect/v01/return_title_button_01.png");
	RegisterTexture("stageselect_right", SCENE_PATH"stageselect/v01/right_button_01.png");
	RegisterTexture("stageselect_left", SCENE_PATH"stageselect/v01/left_button_01.png");
	RegisterTexture("stageselect_chapter", SCENE_PATH"stageselect/v02/chapter_numbers_01.png", false, 4, 2, 1.0f, 3);
	RegisterTexture("stageselect_gear_left", SCENE_PATH"stageselect/v01/gear_left_rotation_01.png", true, 4, 4, 0.5f, 16);
	RegisterTexture("stageselect_gear_right", SCENE_PATH"stageselect/v01/gear_right_rotation_01.png", true, 4, 4, 0.5f, 16);
	RegisterTexture("stageselect_stage_numbers_s", SCENE_PATH"stageselect/v01/stage_numbers_s_01.png", false, 4, 4, 1.0f, 15);
	RegisterTexture("stageselect_stage_numbers_m", SCENE_PATH"stageselect/v01/stage_numbers_m_01.png", false, 4, 4, 1.0f, 15);
	RegisterTexture("stageselect_stage_numbers_w", SCENE_PATH"stageselect/v01/stage_numbers_w_01.png", false, 4, 4, 1.0f, 15);
	// セレクトゲーム画像
	RegisterTexture("1-1", SCENE_PATH"stageselect/v02/1-1.png");
	RegisterTexture("1-2", SCENE_PATH"stageselect/v02/1-2.png");
	RegisterTexture("1-3", SCENE_PATH"stageselect/v02/1-3.png");
	RegisterTexture("1-4", SCENE_PATH"stageselect/v02/1-4.png");
	RegisterTexture("2-1", SCENE_PATH"stageselect/v02/2-1.png");
	RegisterTexture("2-2", SCENE_PATH"stageselect/v02/2-2.png");
	RegisterTexture("2-3", SCENE_PATH"stageselect/v02/2-3.png");
	RegisterTexture("2-4", SCENE_PATH"stageselect/v02/2-4.png");
	RegisterTexture("3-1", SCENE_PATH"stageselect/v02/3-1.png");
}

//-----------------------------------------------------------------
// @brief キャッシュのクリア
//-----------------------------------------------------------------
void TextureManager::ClearCache(void)
{
	texture_cache_.clear();
}
