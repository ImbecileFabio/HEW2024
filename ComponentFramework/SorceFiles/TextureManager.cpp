//=================================================================
// [TextureManager.cpp] テクスチャ管理クラス
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：そんな感じ
//=================================================================

/*----- インクルード -----*/
#include <iostream>
#include "TextureManager.h"
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
void TextureManager::RegisterTexture(const std::string& _imgName, const std::string& _fileName, bool _loopFlg, int _texU, int _texV, int _anmSpeed)
{
	// すでに読み込まれているか確認
	auto it = texture_cache_.find(_imgName);
	if (it != texture_cache_.end())
	{
		// すでに読み込まれている
		std::cout << std::format("\n＜TextureManager＞ -> {} is already loaded\n\n", _imgName);
		return;
	}

	// 存在していないので生成する
	auto texture = std::make_shared<Texture>(_loopFlg, _texU, _texV, _anmSpeed);
	if (texture->Load(_fileName)) {
		texture_cache_[_imgName] = texture;
		std::cout << std::format("＜TextureManager＞ -> {} LoadTexture Success\n", _imgName);
		return;
	}
	
	// 失敗
	std::cout << std::format("＜TextureManager＞ -> {} LoadTexture Error\n", _imgName);
	return;
}

//-----------------------------------------------------------------
// @param  _imgName 画像名
// @brief  読み込んだテクスチャの取得
// @return 存在していればit, なければnullptr
//-----------------------------------------------------------------
std::shared_ptr<Texture> TextureManager::GetTexture(const std::string& _imgName)
{
	auto it = texture_cache_.find(_imgName);
	if (it != texture_cache_.end())
	{
		return it->second;
	}

	std::cout << std::format("＜TextureManager＞ -> {} GetTexture Error\n", _imgName);
	return nullptr;
}

//-----------------------------------------------------------------
// @brief  すべてのテクスチャを登録する
//-----------------------------------------------------------------
void TextureManager::RegisterAllTextures()
{
		//名前が適当なもの多いので調整しつつお願いします

	// Hogehoge
	RegisterTexture("hoge", TEXTURE_PATH"hogehoge.png");

	
	// インゲームのオブジェクト系
	/*--------------- ロボット ---------------*/
	RegisterTexture("robot_drop" , TEXTURE_PATH"robot/v03/robot_dorp_01.png");	// 落下
	RegisterTexture("robot_still", TEXTURE_PATH"robot/v03/robot_still_01.png");	// 静止
	RegisterTexture("robot_walk" , TEXTURE_PATH"robot/v03/robot_walk_01.png");	// 歩行

	/*--------------- 振り子 ---------------*/
	RegisterTexture("ball", TEXTURE_PATH"huriko/v02/ball_01.png");		// ボール
	RegisterTexture("stick", TEXTURE_PATH"huriko/v03/stick_01.png");	// 棒

	/*--------------- タイル ---------------*/
	// 床
	RegisterTexture("tile_center", TEXTURE_PATH"tile/v02/tile_center_01.png");	// 中央
	RegisterTexture("tile_left", TEXTURE_PATH"tile/v02/tile_left_01.png");		// 左
	RegisterTexture("tile_right", TEXTURE_PATH"tile/v02/tile_right_01.png");	// 右
	// 壁
	RegisterTexture("tile_wall", TEXTURE_PATH"tile/v02/tile_wall_01.png");		// 壁

	/*--------------- ギミック ---------------*/
	// リフト
	RegisterTexture("lift_floor_center", GIMMICK_PATH"lift/v02/lift_floor_center_01.png");	// 中央
	RegisterTexture("lift_floor_left", GIMMICK_PATH"lift/v02/lift_floor_left_01.png");		// 左
	RegisterTexture("lift_floor_right", GIMMICK_PATH"lift/v02/lift_floor_right_01.png");	// 右
	RegisterTexture("lift_circle", GIMMICK_PATH"lift/v02/lift_circle_01.png");					// 留め具
	RegisterTexture("lift_rail", GIMMICK_PATH"lift/v02/lift_rail_01.png");						// レール
	// 脆い床 （氷だったもの）
	RegisterTexture("weakfloor_cnter", GIMMICK_PATH"weakfloor/v01/weakfloor_center_01.png");	// 中央
	RegisterTexture("weakfloor_left", GIMMICK_PATH"weakfloor/v01/weakfloor_left_01.png");		// 左
	RegisterTexture("weakfloor_right", GIMMICK_PATH"weakfloor/v01/weakfloor_right_01.png");		// 右
	// 鉄柱
	RegisterTexture("steelpillar_floor_center", GIMMICK_PATH"steelpillar/v02/steelpillar_floor_center_01.png");			// 床, 中央
	RegisterTexture("steelpillar_floor_end_01", GIMMICK_PATH"steelpillar/v02/steelpillar_floor_end_01.png");			// 床, 左
	RegisterTexture("steelpillar_floor_end_02", GIMMICK_PATH"steelpillar/v02/steelpillar_floor_end_02.png");			// 床, 右

	RegisterTexture("steelpillar_pillar_top", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_top_01.png");					// 柱, 上
	RegisterTexture("steelpillar_pillar_bottom", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_bottom_01.png");			// 柱, 下
	RegisterTexture("steelpillar_pillar_break", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_break_01.png");				// 柱, 壊れ
	RegisterTexture("steelpillar_pillar_normal", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_normal_01.png");			// 柱, 通常
	RegisterTexture("steelpillar_pillar_still", GIMMICK_PATH"steelpillar/v02/steelpillar_pillar_normal_01.png");			// 柱, 欠け
	// 煙
	RegisterTexture("smoke01", GIMMICK_PATH"smoke/v01/smoke_bace_back_01.png");		// 柱の奥
	RegisterTexture("smoke02", GIMMICK_PATH"smoke/v01/smoke_bace_front_01.png");		// 柱の手前
	// 滑車
	//RegisterTexture("pulley", GIMMICK_PATH"pulley/v01/pulley_01.png");
	// タイムゾーン
	RegisterTexture("timezone", TEXTURE_PATH"kouka/v02/pendulum_area_01.png");	// 青い円




	// その他の背景、UIなど
	/*--------------- バックドロップ ---------------*/
	RegisterTexture("backdrop_01", TEXTURE_PATH"backdrop/v02/backdrop_01.png");
	RegisterTexture("backdrop_02", TEXTURE_PATH"backdrop/v02/backdrop_02.png");

	/*--------------- UI ---------------*/
	// ハンマー
	RegisterTexture("hammer", UI_PATH"v01/hammer_01.png");
	// ギア
	RegisterTexture("gear", UI_PATH"v02/gear_01.png");
	// 数字
	RegisterTexture("numbers", UI_PATH"v02/numbers_01.png");
	// ポーズボタン
	RegisterTexture("pause_button", UI_PATH"v02/pause_button_01.png");
	// ステージUI
	RegisterTexture("stageUI", UI_PATH"v02/stage_ui_01.png");
	// テスト用ボタン
	RegisterTexture("hoge", UI_PATH"hoge.png");
	/*--------------- SCENE ---------------*/
	// オプション
	RegisterTexture("option_menu", SCENE_PATH"option/v01/9.JPG");
	RegisterTexture("option_sound", SCENE_PATH"option/v01/11.JPG");
	// リザルト
	RegisterTexture("result_menu", SCENE_PATH"result/v01/10.JPG");
	// タイトル
	RegisterTexture("title_menu", SCENE_PATH"title/v01/6.JPG");
	RegisterTexture("title_select", SCENE_PATH"title/v01/7.JPG");
	RegisterTexture("transition_01", SCENE_PATH"title/v01/transition_01.png");
	RegisterTexture("transition_02", SCENE_PATH"title/v01/transition_02.png");


}

//-----------------------------------------------------------------
// @brief キャッシュのクリア
//-----------------------------------------------------------------
void TextureManager::ClearCache(void)
{
	texture_cache_.clear();
}
