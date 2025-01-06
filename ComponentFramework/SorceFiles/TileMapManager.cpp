//=================================================================
// [TileMapManager.cpp] �^�C���}�b�v�}�l�[�W��
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�I�u�W�F�N�g���}�X�ڏ�ɔz�u���邽�߂̃}�l�[�W��
// �Ƃ͂����Ă��������̂̓V�[�����Ő������Ȃ��Ɠ����ɍ������Ȃ������ǂ����悤
// 999. ���{�b�g
// 1. �^�C��
// 2. ����
// 3. �U��q
// 4. 
// 
// 100~109. ���t�g�̎n�_
// 110~119. ���t�g�̏I�_
//=================================================================

/*----- �C���N���[�h -----*/
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
// �R���X�g���N�^
//-----------------------------------------------------------------
TileMapManager::TileMapManager(GameManager* _gameManager)
	: game_manager_(_gameManager)
{
}
//-----------------------------------------------------------------
// @param _mapData �}�b�v�f�[�^
// @brief �}�b�v�f�[�^��ǂݍ���
//-----------------------------------------------------------------
void TileMapManager::LoadTileMap(const std::vector<std::vector<std::vector<int>>>& _mapData)
{
	map_data_ = _mapData;
	GenerateGameObjects();
}

//-----------------------------------------------------------------
// @param _fileName �t�@�C����
// @brief CSV�t�@�C����ǂݍ���
//-----------------------------------------------------------------
std::vector<std::vector<std::vector<int>>> TileMapManager::LoadCSV(const std::string& _fileName)
{
	std::vector<std::vector<std::vector<int>>> map;
	std::ifstream file(_fileName);

	if (!file.is_open())
	{
		std::cerr << std::format("��TileMapManager�� -> Failed to open CSV file : {}", _fileName);
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
// @brief �Q�[���I�u�W�F�N�g�𐶐�
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
// @param _x X���W, _y Y���W, _tileID �^�C��ID
// @brief ID�ɉ����ăI�u�W�F�N�g�𐶐�
//-----------------------------------------------------------------
void TileMapManager::CreateGameObject(int _x, int _y, int _tileID)
{
	GameObject* obj = nullptr;
	Vector2 p = { _x - MAP_SIZE_X / 2 , _y - MAP_SIZE_Y / 2 };	// ���W�̒���
	Vector2 objPos = { p.x * TILE_SIZE_X, -(p.y * TILE_SIZE_Y) };	// �I�u�W�F�N�g�̐�������ʒu

	if (_tileID == 1)	// �^�C��
	{
		obj = new Tile(game_manager_);
	}
	else if (_tileID == 2)	// �A�C�e��
	{
		obj = new Item(game_manager_);
	}
	else if (_tileID == 3)
	{
		obj = new Pendulum(game_manager_, Vector3(objPos.x, objPos.y, 0), false, 30.f);

	}
	else if (_tileID >= 100 && _tileID <= 109)	// ���t�g
	{
		// ���t�g�̏I�_��T��
		Vector2 endPos;
		for (int y = 0; y < map_data_.size(); ++y)
		{
			for (int x = 0; x < map_data_[y].size(); ++x)
			{
				for (int tileID : map_data_[y][x])
				{
					if (tileID == _tileID + 10) // ������ID+10�����t�g�̏I�_
					{
						endPos = { x * TILE_SIZE_X, y * TILE_SIZE_Y};
					}
				}
			}
		}
		obj = new Lift(Lift::MoveState::side, 50.0f, game_manager_);
		auto lift = dynamic_cast<Lift*>(obj);
		auto pendulum_ = new Pendulum(game_manager_, Vector3(objPos.x, objPos.y, 0.0f), false, 30.f);
		lift->SetPendulum(pendulum_);	// ���t�g�ƘA�����������U��q���Z�b�g
		
		
	}
	else if (_tileID == 999)	// ���{�b�g
	{
		obj = new Robot(game_manager_);
	}
	else
	{
		return;
	}




	if (obj != nullptr)
	{
		// �I�u�W�F�N�g�̈ʒu��ݒ�
		obj->GetComponent<TransformComponent>()->SetPosition(objPos.x , objPos.y);
	}
}