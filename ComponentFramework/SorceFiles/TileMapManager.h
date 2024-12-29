//=================================================================
// [TileMapManager.h] タイルマップマネージャ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：オブジェクトをマス目状に配置するためのマネージャ
//=================================================================
#ifndef TILEMAP_MANAGER_H_
#define TILEMAP_MANAGER_H_
/*----- インクルード -----*/
#include <vector>
#include "GameManager.h"

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//-----------------------------------------------------------------
// タイルマップマネージャ
//-----------------------------------------------------------------
class TileMapManager
{
public:
	TileMapManager();
	void LoadTileMap(const std::vector<std::vector<int>>& _mapData);

private:
	void GenerateGameObjects();
	void CreateGameObject(int _x, int _y, int tileID);


private:
	GameManager* game_manager_{};
	std::vector<std::vector<int>> map_data_;
	float tileSize_ = 64.0f;
};


#endif //TILEMAP_MANAGER_H_