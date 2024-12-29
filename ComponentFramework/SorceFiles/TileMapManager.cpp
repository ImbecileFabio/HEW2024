//=================================================================
// [TileMapManager.cpp] �^�C���}�b�v�}�l�[�W��
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�I�u�W�F�N�g���}�X�ڏ�ɔz�u���邽�߂̃}�l�[�W��
// �Ƃ͂����Ă��������̂̓V�[�����Ő������Ȃ��Ɠ����ɍ������Ȃ�����
// 1.�^�C��
// 2.��
// 3.�A�C�e��
// 4.
// 5.
// 6.
//=================================================================

/*----- �C���N���[�h -----*/
#include "GameObjects/GameObject.h"
#include "TileMapManager.h"

#include "GameObjects/GameObject/Tile.h"
//#include "GameObjects/GameObject/Wall.h"	// ����ǉ����邩��
#include "GameObjects/GameObject/Item.h"



//-----------------------------------------------------------------
// �R���X�g���N�^
//-----------------------------------------------------------------
TileMapManager::TileMapManager()
{
}
//-----------------------------------------------------------------
// @param _mapData �}�b�v�f�[�^
// @brief �}�b�v�f�[�^��ǂݍ���
//-----------------------------------------------------------------
void TileMapManager::LoadTileMap(const std::vector<std::vector<int>>& _mapData)
{
	map_data_ = _mapData;
	GenerateGameObjects();
}

//-----------------------------------------------------------------
// @brief �Q�[���I�u�W�F�N�g�𐶐�
//-----------------------------------------------------------------
void TileMapManager::GenerateGameObjects()
{
	for (int y = 0; y < map_data_.size(); ++y) {
		for (int x = 0; x < map_data_[y].size(); ++x) {
			int tileID = map_data_[y][x];
			// �^�C��ID��0�̏ꍇ�͉������Ȃ�
			if (tileID == 0) continue;
			CreateGameObject(x, y, tileID);
		}
	}
}

//-----------------------------------------------------------------
// @param _x X���W, _y Y���W, _tileID �^�C��ID
// @brief �Q�[���I�u�W�F�N�g���쐬
//-----------------------------------------------------------------
void TileMapManager::CreateGameObject(int _x, int _y, int _tileID)
{
	GameObject* obj = nullptr;

	switch (_tileID) {
	case 1:		// �^�C��
		obj = new Tile(game_manager_);
		break;
	case 2:		// ��
		//obj = new Wall(game_manager_);
		break;
	case 3:		// �A�C�e��
		obj = new Item(game_manager_);
		break;
	case 4:		//

		break;
	}
}