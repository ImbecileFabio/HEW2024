//=================================================================
// [TileMapManager.cpp] タイルマップマネージャ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：オブジェクトをマス目状に配置するためのマネージャ
// とはいっても動くものはシーン内で生成しないと動きに差を作れないかも
// 1.タイル
// 2.壁
// 3.アイテム
// 4.
// 5.
// 6.
//=================================================================

/*----- インクルード -----*/
#include "GameObjects/GameObject.h"
#include "TileMapManager.h"

#include "GameObjects/GameObject/Tile.h"
//#include "GameObjects/GameObject/Wall.h"	// 今後追加するかな
#include "GameObjects/GameObject/Item.h"



//-----------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------
TileMapManager::TileMapManager()
{
}
//-----------------------------------------------------------------
// @param _mapData マップデータ
// @brief マップデータを読み込む
//-----------------------------------------------------------------
void TileMapManager::LoadTileMap(const std::vector<std::vector<int>>& _mapData)
{
	map_data_ = _mapData;
	GenerateGameObjects();
}

//-----------------------------------------------------------------
// @brief ゲームオブジェクトを生成
//-----------------------------------------------------------------
void TileMapManager::GenerateGameObjects()
{
	for (int y = 0; y < map_data_.size(); ++y) {
		for (int x = 0; x < map_data_[y].size(); ++x) {
			int tileID = map_data_[y][x];
			// タイルIDが0の場合は何もしない
			if (tileID == 0) continue;
			CreateGameObject(x, y, tileID);
		}
	}
}

//-----------------------------------------------------------------
// @param _x X座標, _y Y座標, _tileID タイルID
// @brief ゲームオブジェクトを作成
//-----------------------------------------------------------------
void TileMapManager::CreateGameObject(int _x, int _y, int _tileID)
{
	GameObject* obj = nullptr;

	switch (_tileID) {
	case 1:		// タイル
		obj = new Tile(game_manager_);
		break;
	case 2:		// 壁
		//obj = new Wall(game_manager_);
		break;
	case 3:		// アイテム
		obj = new Item(game_manager_);
		break;
	case 4:		//

		break;
	}
}