//=================================================================
// [TileMapManager.cpp] タイルマップマネージャ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：オブジェクトをマス目状に配置するためのマネージャ
// とはいっても動くものはシーン内で生成しないと動きに差を作れないかもどうしよう
// 999. ロボット
// 1. タイル
// 2. 歯車
// 3. 振り子
// 4. 
// 
// 100~109. リフトの始点
// 110~119. リフトの終点
//=================================================================

/*----- インクルード -----*/
#include <fstream>
#include <sstream>
#include <iostream>
#include <format>

#include "GameObjects/GameObject.h"
#include "TileMapManager.h"

#include "GameObjects/GameObject/Tile.h"
#include "GameObjects/GameObject/Item.h"
#include "GameObjects/GameObject/Lift.h"
#include "GameObjects/GameObject/Robot.h"
#include "GameObjects/GameObject/Pendulum.h"


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
			while (std::getline(cellStream, obj, '|'))
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
	Vector2 p = { _x - MAP_SIZE_X / 2 , _y - MAP_SIZE_Y / 2 };	// 座標の調整
	Vector2 objPos = { p.x * TILE_SIZE_X, -(p.y * TILE_SIZE_Y) };	// オブジェクトの生成する位置

	if (_tileID == 1)	// タイル
	{
		obj = new Tile(game_manager_);
	}
	else if (_tileID == 2)	// アイテム
	{
		obj = new Item(game_manager_);
	}
	else if (_tileID == 3)
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
						endPos = { x * TILE_SIZE_X, y * TILE_SIZE_Y};
					}
				}
			}
		}
		obj = new Lift(Lift::MoveState::side, 50.0f, game_manager_);
		auto lift = dynamic_cast<Lift*>(obj);
		auto pendulum_ = new Pendulum(game_manager_, Vector3(objPos.x, objPos.y, 0.0f), false, 30.f);
		lift->SetPendulum(pendulum_);	// リフトと連動させたい振り子をセット
		
		
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