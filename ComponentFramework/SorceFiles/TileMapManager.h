//=================================================================
// [TileMapManager.h] �^�C���}�b�v�}�l�[�W��
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�I�u�W�F�N�g���}�X�ڏ�ɔz�u���邽�߂̃}�l�[�W��
// �^�C���̃T�C�Y�̕ύX�͂���
// ����CSV�̓ǂݍ��݂̏����������Ŏ���
//=================================================================
#ifndef TILEMAP_MANAGER_H_
#define TILEMAP_MANAGER_H_
/*----- �C���N���[�h -----*/
#include <vector>
#include <string>
#include <map>
#include "GameProcess.h"
#include "GameManager.h"
#include "TextureManager.h"

/*----- �萔��` -----*/
// �^�C���̃T�C�Y
constexpr float TILE_SIZE_X = 60.0f;
constexpr float TILE_SIZE_Y = 60.0f;

// �X�N���[���ɓ���^�C���̐�
constexpr float MAP_SIZE_X = 32.0f;// ( 1920pixel / �^�C���̃T�C�Y)
constexpr float MAP_SIZE_Y = 18.0f;// ( 1080pixel / �^�C���̃T�C�Y)

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class WeakFloorGroup;
//-----------------------------------------------------------------
// �^�C���}�b�v�}�l�[�W��
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


	bool IsTileInGroup(int x, int y, WeakFloorGroup*& group);
private:
	GameManager* game_manager_{};
	std::vector<std::vector<std::vector<int>>> map_data_;
	std::map<std::pair<int, int>, WeakFloorGroup*> tile_to_group_; // �^�C�����W�ƃO���[�v�̑Ή�
	std::vector<WeakFloorGroup*> weak_floor_groups_;               // �O���[�v�ꗗ
};


#endif //TILEMAP_MANAGER_H_