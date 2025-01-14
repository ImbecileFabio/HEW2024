//=================================================================
// [TileMapManager.cpp] タイルマップマネージャ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：オブジェクトをマス目状に配置するためのマネージャ
// とはいっても動くものはシーン内で生成しないと動きに差を作れないかもどうしよう
//-----------------------------------------------------------------
// 998. 歯車
// 999. ロボット
// 1. タイル
// 2. 脆いタイル
// 3. 振り子
// 4. 
// 
// 100~109. リフトの始点
// 110~119. リフトの終点
// 
// 200. けむりの始点 / 201. けむりの終点
// 
// 滑車、鉄柱、
//=================================================================

/*----- インクルード -----*/
#include <fstream>
#include <sstream>
#include <iostream>
#include <format>

#include "GameObjects/GameObject.h"
#include "TileMapManager.h"

#include "GameObjects/GameObject/Tile.h"
#include "GameObjects/GameObject/Gimmick/WeakFloor.h"
#include "GameObjects/GameObject/Pendulum.h"

#include "GameObjects/GameObject/Gimmick/Smoke.h"
#include "GameObjects/GameObject/Gimmick/SteePillar.h"
#include "GameObjects/GameObject/Gimmick/Pulley.h"

#include "GameObjects/GameObject/Lift.h"

#include "GameObjects/GameObject/Item.h"
#include "GameObjects/GameObject/Robot.h"
//-----------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------
TileMapManager::TileMapManager(GameManager* _gameManager)
	: game_manager_(_gameManager)
{
}
//-----------------------------------------------------------------
// @param _mapData マップデータ
// @brief マップデータを読み込む
//-----------------------------------------------------------------
void TileMapManager::LoadTileMap(const std::vector<std::vector<std::vector<int>>>& _mapData)
{
	map_data_ = _mapData;
	GenerateGameObjects();
}

//-----------------------------------------------------------------
// @param _fileName ファイル名
// @brief CSVファイルを読み込む
// @return マップデータ map、失敗すると空のmapを返す
//-----------------------------------------------------------------
std::vector<std::vector<std::vector<int>>> TileMapManager::LoadCSV(const std::string& _fileName)
{
	std::vector<std::vector<std::vector<int>>> map;
	std::ifstream file(_fileName);

	if (!file.is_open())
	{
		std::cerr << std::format("＜TileMapManager＞ -> Failed to open CSV file : {}", _fileName);
		return map;
	}

	std::string line;
	while (std::getline(file, line))
	{
		std::vector<std::vector<int>> row;
		std::stringstream ss(line);
		std::string cell;
		while (std::getline(ss, cell, ','))
		{
			std::vector<int> objects;
			std::stringstream cellStream(cell);
			std::string obj;
			while (std::getline(cellStream, obj, '|'))	// オブジェクトが複数ある場合
			{
				objects.push_back(std::stoi(obj));
			}
			row.push_back(objects);
		}
		map.push_back(row);
	}

	file.close();
	return map;
}

//-----------------------------------------------------------------
// @brief ゲームオブジェクトを生成
//-----------------------------------------------------------------
void TileMapManager::GenerateGameObjects()
{
	for (int y = 0; y < map_data_.size(); ++y)
	{
		for (int x = 0; x < map_data_[y].size(); ++x)
		{
			for (int objectID : map_data_[y][x])
			{
				CreateGameObject(x, y, objectID);
			}
		}
	}
}

//-----------------------------------------------------------------
// @param _x X座標, _y Y座標, _tileID タイルID
// @brief IDに応じてオブジェクトを生成
//-----------------------------------------------------------------
void TileMapManager::CreateGameObject(int _x, int _y, int _tileID)
{
	GameObject* obj = nullptr;
	Vector2 op = { _x - MAP_SIZE_X / 2 , _y - MAP_SIZE_Y / 2 };	// 中心が0になるように
	Vector2 objPos = { (op.x * TILE_SIZE_X) + (TILE_SIZE_X / 2), -((op.y * TILE_SIZE_Y) + (TILE_SIZE_Y / 2)) };	// オブジェクトの生成する位置を調整（ごり押し）

	if (_tileID == 1)	// タイル
	{
		obj = new Tile(game_manager_);
		if (auto sprite = obj->GetComponent<SpriteComponent>())
		{
			// 周囲のタイルを取得
			bool up = GetAdjacentTile(_tileID, _x, _y, 0, 1);
			bool down = GetAdjacentTile(_tileID, _x, _y, 0, -1);
			bool left = GetAdjacentTile(_tileID, _x, _y, -1, 0);
			bool right = GetAdjacentTile(_tileID, _x, _y, 1, 0);

			// テクスチャを設定
			if (left) {// 左にタイルがある
				if (right) {// 右にタイルがある
					sprite->SetTexture("tile_center");	// 中央
				}
				else {
					sprite->SetTexture("tile_right");	// 右
				}
			}
			// 左にタイルがない
			else if (right) {// 右にタイルがある
				sprite->SetTexture("tile_left");	// 左
			}
		}

	}
	else if (_tileID == 2)	// 脆いタイル
	{
	}
	else if (_tileID == 3)	// 振り子
	{
		obj = new Pendulum(game_manager_, Vector3(objPos.x, objPos.y, 0), false, 30.f);

	}
	else if (_tileID >= 100 && _tileID <= 109)	// リフト
	{
		// リフトの終点を探す
		Vector2 endPos;
		for (int y = 0; y < map_data_.size(); ++y)
		{
			for (int x = 0; x < map_data_[y].size(); ++x)
			{
				for (int tileID : map_data_[y][x])
				{
					if (tileID == _tileID + 10) // 自分のID+10がリフトの終点
					{
						Vector2 ep = {x - MAP_SIZE_X / 2 , y - MAP_SIZE_Y / 2 };	// 座標の調整
						endPos = { (ep.x * TILE_SIZE_X) + (TILE_SIZE_X / 2), -((ep.y * TILE_SIZE_Y) + (TILE_SIZE_Y / 2)) };
						break;
					}
				}
			}
		}

		float dx = endPos.x - objPos.x;
		float dy = endPos.y - objPos.y;

		Lift::MoveState direction{};

		// 移動方向を設定
		if (dy == 0 && dx != 0) {	// 左右
			direction = Lift::MoveState::side;
		}
		else if (dx == 0 && dy != 0) {	// 上下
			direction = Lift::MoveState::length;
		}
		else if (dx > 0 && dy > 0) {	// 斜め(右)
			direction = Lift::MoveState::diagonalRight;
		}
		else if (dx < 0 && dy > 0) {	// 斜め(左)
			direction = Lift::MoveState::diagonalLeft;
		}

		// 移動距離を計算
		float distance = std::sqrt(dx * dx + dy * dy);

		// リフト生成
		obj = new Lift(direction, distance, game_manager_);
		auto lift = dynamic_cast<Lift*>(obj);
		lift->GetTransformComponent()->SetPosition(objPos.x, objPos.y);

		auto pendulum_ = new Pendulum(game_manager_, Vector3(objPos.x, objPos.y, 0.0f), false, 30.f);
		lift->SetPendulum(pendulum_);	// リフトと連動させたい振り子をセット
		
		
	}
	else if (_tileID == 200)	// けむり
	{

	}
	else if (_tileID == 998)	// 歯車
	{
		obj = new Item(game_manager_);
	}
	else if (_tileID == 999)	// ロボット
	{
		obj = new Robot(game_manager_);
	}
	else
	{
		return;
	}




	if (obj != nullptr)
	{
		// オブジェクトの位置を設定
		obj->GetComponent<TransformComponent>()->SetPosition(objPos.x , objPos.y);
	}
}

bool TileMapManager::GetAdjacentTile(int _tyleID ,int _x, int _y, int _dx, int _dy)
{
	// 範囲内かチェック
	if (_x + _dx >= 0 && _x + _dx < map_data_.size() && _y + _dy >= 0 && _y + _dy < map_data_[0].size()) {
		// 範囲内なら
		for (auto& map : map_data_[_x + _dx][_y + _dy])
		{
			if (map == _tyleID)
			{
				return true;
			}
		}
	}
	// 範囲外なら
	return false;
}
