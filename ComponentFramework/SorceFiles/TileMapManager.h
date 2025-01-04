//=================================================================
// [TileMapManager.h] �^�C���}�b�v�}�l�[�W��
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�I�u�W�F�N�g���}�X�ڏ�ɔz�u���邽�߂̃}�l�[�W��
//=================================================================
#ifndef TILEMAP_MANAGER_H_
#define TILEMAP_MANAGER_H_
/*----- �C���N���[�h -----*/
#include <vector>
#include "GameManager.h"

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/

//-----------------------------------------------------------------
// �^�C���}�b�v�}�l�[�W��
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