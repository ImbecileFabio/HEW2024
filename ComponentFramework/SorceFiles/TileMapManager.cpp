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

#include "GameObjects/GameObject/Gimmick/WeakFloorGroup.h"
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
	Vector3 objPos = { (op.x * TILE_SIZE_X) + (TILE_SIZE_X / 2), -((op.y * TILE_SIZE_Y) + (TILE_SIZE_Y / 2)), 0.0f };	// オブジェクトの生成する位置を調整（ごり押し）

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
		obj = new WeakFloor(game_manager_);
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
					sprite->SetTexture("weakfloor_center");	// 中央
				}
				else {
					sprite->SetTexture("weakfloor_right");	// 右
				}
			}
			// 左にタイルがない
			else if (right) {// 右にタイルがある
				sprite->SetTexture("weakfloor_left");	// 左
			}
			// 既存のグループを探す
			WeakFloorGroup* group = nullptr;
			if (IsTileInGroup(_x - 1, _y, group) || IsTileInGroup(_x + 1, _y, group) ||
				IsTileInGroup(_x, _y - 1, group) || IsTileInGroup(_x, _y + 1, group))
			{
				// 隣接グループが見つかった場合、そのグループに追加
				group->AddWeakFloorTile(obj);
			}
			else
			{
				// 新しいグループを作成
				group = new WeakFloorGroup(game_manager_);
				group->AddWeakFloorTile(obj);
				weak_floor_groups_.push_back(group); // グループリストに追加
				// 振り子を生成 
				auto pendulum_ = new Pendulum(game_manager_, objPos, false, 30.f);
				auto weakFloorGroup = dynamic_cast<WeakFloorGroup*>(group);
				// 振り子と連動させたい振り子をセット
				weakFloorGroup->SetPendulumANDMovement(pendulum_);
			}

			// タイルの位置とグループを関連付ける
			tile_to_group_[{_x, _y}] = group;
		}
	}
	else if (_tileID == 3)	// 振り子
	{
		obj = new Pendulum(game_manager_, objPos, false, 30.f);

	}
	else if (_tileID >= 100 && _tileID <= 109)	// リフト
	{
		// リフトの終点を探す	見つからなかったらとりあえず初期位置に
		Vector3 endPos = objPos;
		bool foundEndPos = false;
		for (int y = 0; y < map_data_.size(); ++y)
		{
			for (int x = 0; x < map_data_[y].size(); ++x)
			{
				for (int tileID : map_data_[y][x])
				{
					if (tileID == _tileID + 10) // 自分のID+10がリフトの終点
					{
						Vector2 ep = { x - MAP_SIZE_X / 2 , y - MAP_SIZE_Y / 2 };	// 座標の調整
						endPos = { (ep.x * TILE_SIZE_X) + (TILE_SIZE_X / 2), -((ep.y * TILE_SIZE_Y) + (TILE_SIZE_Y / 2)) };
						foundEndPos = true;
						break;
					}
				}
				if (foundEndPos) break;
			}
			if (foundEndPos) break;
		}

		float dx = endPos.x - objPos.x;
		float dy = endPos.y - objPos.y;

		Lift::MoveState direction{};

		// 移動方向を設定	もう少し厳密に判定して開始時の移動方向を決めてもいいかも
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

		auto pendulum_ = new Pendulum(game_manager_, objPos, false, 30.f);

		// リフト生成
		obj = new Lift(game_manager_, direction, objPos, endPos, pendulum_);
		auto lift = dynamic_cast<Lift*>(obj);
		lift->GetTransformComponent()->SetPosition(objPos.x, objPos.y);



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
		obj->GetComponent<TransformComponent>()->SetPosition(objPos.x, objPos.y);
	}
}

/*-----------------------------------------------------------------
// @param _tyleID タイルID, _x X座標, _y Y座標, _dx X方向, _dy Y方向
// @brief 座標位置にあるタイルが指定したタイルかどうかを取得
// @return 指定したタイルがある: true, ない: false
// 現状trueが返されないので要修正
-----------------------------------------------------------------*/
bool TileMapManager::GetAdjacentTile(int _tyleID, int _x, int _y, int _dx, int _dy)
{
	int nx = _x + _dx;
	int ny = _y + _dy;

	// 範囲内かチェック
	if (nx >= 0 && nx < map_data_[0].size() && ny >= 0 && ny < map_data_.size())
	{
		for (auto& id : map_data_[ny][nx]) // 順序を確認（行: y, 列: x）
		{
			if (id == _tyleID)
			{
				return true;
			}
		}
	}

	return false;
}

bool TileMapManager::IsTileInGroup(int x, int y, WeakFloorGroup*& group)
{
	auto it = tile_to_group_.find({ x, y });
	if (it != tile_to_group_.end())
	{
		group = it->second;
		return true;
	}
	group = nullptr;
	return false;
};