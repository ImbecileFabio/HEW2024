//=================================================================
// [TileMapManager.cpp] �^�C���}�b�v�}�l�[�W��
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�I�u�W�F�N�g���}�X�ڏ�ɔz�u���邽�߂̃}�l�[�W��
// �Ƃ͂����Ă��������̂̓V�[�����Ő������Ȃ��Ɠ����ɍ������Ȃ������ǂ����悤
//-----------------------------------------------------------------
// 998. ����
// 999. ���{�b�g
// 1. �^�C��
// 2. �Ƃ��^�C��
// 3. �U��q
// 4. 
// 
// 100~109. ���t�g�̎n�_
// 110~119. ���t�g�̏I�_
// 
// 200. ���ނ�̎n�_ / 201. ���ނ�̏I�_
// 
// ���ԁA�S���A
//=================================================================

/*----- �C���N���[�h -----*/
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
// @return �}�b�v�f�[�^ map�A���s����Ƌ��map��Ԃ�
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
			while (std::getline(cellStream, obj, '|'))	// �I�u�W�F�N�g����������ꍇ
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
	Vector2 op = { _x - MAP_SIZE_X / 2 , _y - MAP_SIZE_Y / 2 };	// ���S��0�ɂȂ�悤��
	Vector2 objPos = { (op.x * TILE_SIZE_X) + (TILE_SIZE_X / 2), -((op.y * TILE_SIZE_Y) + (TILE_SIZE_Y / 2)) };	// �I�u�W�F�N�g�̐�������ʒu�𒲐��i���艟���j

	if (_tileID == 1)	// �^�C��
	{
		obj = new Tile(game_manager_);
		if (auto sprite = obj->GetComponent<SpriteComponent>())
		{
			// ���͂̃^�C�����擾
			bool up = GetAdjacentTile(_tileID, _x, _y, 0, 1);
			bool down = GetAdjacentTile(_tileID, _x, _y, 0, -1);
			bool left = GetAdjacentTile(_tileID, _x, _y, -1, 0);
			bool right = GetAdjacentTile(_tileID, _x, _y, 1, 0);

			// �e�N�X�`����ݒ�
			if (left) {// ���Ƀ^�C��������
				if (right) {// �E�Ƀ^�C��������
					sprite->SetTexture("tile_center");	// ����
				}
				else {
					sprite->SetTexture("tile_right");	// �E
				}
			}
			// ���Ƀ^�C�����Ȃ�
			else if (right) {// �E�Ƀ^�C��������
				sprite->SetTexture("tile_left");	// ��
			}
		}

	}
	else if (_tileID == 2)	// �Ƃ��^�C��
	{
	}
	else if (_tileID == 3)	// �U��q
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
						Vector2 ep = {x - MAP_SIZE_X / 2 , y - MAP_SIZE_Y / 2 };	// ���W�̒���
						endPos = { (ep.x * TILE_SIZE_X) + (TILE_SIZE_X / 2), -((ep.y * TILE_SIZE_Y) + (TILE_SIZE_Y / 2)) };
						break;
					}
				}
			}
		}

		float dx = endPos.x - objPos.x;
		float dy = endPos.y - objPos.y;

		Lift::MoveState direction{};

		// �ړ�������ݒ�
		if (dy == 0 && dx != 0) {	// ���E
			direction = Lift::MoveState::side;
		}
		else if (dx == 0 && dy != 0) {	// �㉺
			direction = Lift::MoveState::length;
		}
		else if (dx > 0 && dy > 0) {	// �΂�(�E)
			direction = Lift::MoveState::diagonalRight;
		}
		else if (dx < 0 && dy > 0) {	// �΂�(��)
			direction = Lift::MoveState::diagonalLeft;
		}

		// �ړ��������v�Z
		float distance = std::sqrt(dx * dx + dy * dy);

		// ���t�g����
		obj = new Lift(direction, distance, game_manager_);
		auto lift = dynamic_cast<Lift*>(obj);
		lift->GetTransformComponent()->SetPosition(objPos.x, objPos.y);

		auto pendulum_ = new Pendulum(game_manager_, Vector3(objPos.x, objPos.y, 0.0f), false, 30.f);
		lift->SetPendulum(pendulum_);	// ���t�g�ƘA�����������U��q���Z�b�g
		
		
	}
	else if (_tileID == 200)	// ���ނ�
	{

	}
	else if (_tileID == 998)	// ����
	{
		obj = new Item(game_manager_);
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

bool TileMapManager::GetAdjacentTile(int _tyleID ,int _x, int _y, int _dx, int _dy)
{
	// �͈͓����`�F�b�N
	if (_x + _dx >= 0 && _x + _dx < map_data_.size() && _y + _dy >= 0 && _y + _dy < map_data_[0].size()) {
		// �͈͓��Ȃ�
		for (auto& map : map_data_[_x + _dx][_y + _dy])
		{
			if (map == _tyleID)
			{
				return true;
			}
		}
	}
	// �͈͊O�Ȃ�
	return false;
}
