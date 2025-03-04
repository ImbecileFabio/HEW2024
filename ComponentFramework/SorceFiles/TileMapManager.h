//=================================================================
// [TileMapManager.h] タイルマップマネージャ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：オブジェクトをマス目状に配置するためのマネージャ
// タイルのサイズの変更はここ
// 現状CSVの読み込みの処理も自分で持つ
//=================================================================
#ifndef TILEMAP_MANAGER_H_
#define TILEMAP_MANAGER_H_
/*----- インクルード -----*/
#include <vector>
#include <string>
#include <map>
#include "GameProcess.h"
#include "GameManager.h"
#include "TextureManager.h"

/*----- 定数定義 -----*/
// タイルのサイズ
constexpr float TILE_SIZE_X = 60.0f;
constexpr float TILE_SIZE_Y = 60.0f;

// スクリーンに入るタイルの数
constexpr float MAP_SIZE_X = 32.0f;// ( 1920pixel / タイルのサイズ)
constexpr float MAP_SIZE_Y = 18.0f;// ( 1080pixel / タイルのサイズ)

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class WeakFloorGroup;
class LiftGroup;
class SteePillarFloorGroup;
class SteePillarRightGroup;
class SteePillarLeftGroup;
//-----------------------------------------------------------------
// タイルマップマネージャ
//-----------------------------------------------------------------
class TileMapManager
{
public:
	TileMapManager(GameManager* _gameManager);
	void LoadTileMap(const std::vector<std::vector<std::vector<int>>>& _mapData);

	std::vector<std::vector<std::vector<int>>> LoadCSV(const std::string& _fileName);

private:
	void GenerateGameObjects();
	void CreateGameObject(int _x, int _y, int tileID);

	bool GetAdjacentTile(int _typeID, int _x, int _y, int _dx, int _dy);


	bool IsTileInGroup(int x, int y, WeakFloorGroup*& _group);
	bool IsTileInGroup(int x, int y, LiftGroup*& _group);
	bool IsTileInGroup(int x, int y, SteePillarFloorGroup*& _group);
	bool IsTileInGroup(int x, int y, SteePillarRightGroup*& _group);
	bool IsTileInGroup(int x, int y, SteePillarLeftGroup*& _group);

	void hogehoge();
private:
	GameManager* game_manager_{};
	std::vector<std::vector<std::vector<int>>> map_data_;
	std::map<std::pair<int, int>, WeakFloorGroup*>		 weak_tile_to_group_;	 // タイル座標とグループの対応
	std::map<std::pair<int, int>, LiftGroup*>			 lift_tile_to_group_;
	std::map<std::pair<int, int>, SteePillarFloorGroup*> stee_pillar_to_group_;
	std::map<std::pair<int, int>, SteePillarRightGroup*> stee_pillar_right_to_group_;
	std::map<std::pair<int, int>, SteePillarLeftGroup*>  stee_pillar_left_to_group_;
	std::vector<WeakFloorGroup*> weak_floor_groups_;					// 脆い床グループ一覧
	std::vector<LiftGroup*> lift_groups_;								// リフトグループ一覧
	std::vector<SteePillarFloorGroup*> stee_pillar_floor_groups_;		// 鉄柱床グループ一覧
	std::vector<SteePillarRightGroup*> stee_pillar_right_groups_;		// 鉄柱床グループ一覧
	std::vector<SteePillarLeftGroup*>  stee_pillar_left_groups_;		// 鉄柱床グループ一覧
};


#endif //TILEMAP_MANAGER_H_