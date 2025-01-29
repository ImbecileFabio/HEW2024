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
// 8. �E������
// 9, ��������
// 2. �Ƃ��^�C��
// 3, 33, 333. �U��q
// 4. �S���̑���
// 5. �S���̉E��
// 6. �S���̍���
// 7. �r���ǂ̎n�_
// 10. �r���ǂ̏I�_
// 
// 100~109. ���t�g�̎n�_
// 110~119. ���t�g�̏I�_
// 
// 
// ����00000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000000
//=================================================================

/*----- �C���N���[�h -----*/
#include <fstream>
#include <sstream>
#include <iostream>
#include <format>

#include "GameObjects/GameObject.h"
#include "TileMapManager.h"

#include "GameObjects/GameObject/Tile.h"
#include "GameObjects/GameObject/Wall.h"
#include "GameObjects/GameObject/Gimmick/WeakFloor.h"
#include "GameObjects/GameObject/Pendulum.h"

#include "GameObjects/GameObject/Gimmick/SmokePipe.h"
#include "GameObjects/GameObject/Gimmick/SteePillarLeft.h"
#include "GameObjects/GameObject/Gimmick/SteePillarRight.h"
#include "GameObjects/GameObject/Gimmick/SteePillarFloor.h"
#include "GameObjects/GameObject/Gimmick/Pulley.h"

#include "GameObjects/GameObject/Lift.h"

#include "GameObjects/GameObject/Item.h"
#include "GameObjects/GameObject/Robot.h"

#include "GameObjects/GameObject/Gimmick/Group/WeakFloorGroup.h"
#include "GameObjects/GameObject/Gimmick/Group/LiftGroup.h"
#include "GameObjects/GameObject/Gimmick/Group/SteePillarFloorGroup.h"
#include "GameObjects/GameObject/Gimmick/Group/SteePillarLeftGroup.h"
#include "GameObjects/GameObject/Gimmick/Group/SteePillarRightGroup.h"
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
	Vector3 objPos = { (op.x * TILE_SIZE_X) + (TILE_SIZE_X / 2), -((op.y * TILE_SIZE_Y) + (TILE_SIZE_Y / 2)), 0.0f };	// �I�u�W�F�N�g�̐�������ʒu�𒲐��i���艟���j

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
		obj = new WeakFloor(game_manager_);
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
					sprite->SetTexture("weakfloor_center");	// ����
					
				}
				else {
					sprite->SetTexture("weakfloor_right");	// �E
				}
			}
			// ���Ƀ^�C�����Ȃ�
			else if (right) {// �E�Ƀ^�C��������
				sprite->SetTexture("weakfloor_left");	// ��
			}
			// �����̃O���[�v��T��
			WeakFloorGroup* group = nullptr;
			if (IsTileInGroup(_x - 1, _y, group) || IsTileInGroup(_x + 1, _y, group) ||
				IsTileInGroup(_x, _y - 1, group) || IsTileInGroup(_x, _y + 1, group))
			{
				// �אڃO���[�v�����������ꍇ�A���̃O���[�v�ɒǉ�
				group->AddWeakFloorTile(obj);
			}
			else
			{
				// �V�����O���[�v���쐬
				group = new WeakFloorGroup(game_manager_);
				group->AddWeakFloorTile(obj);
				weak_floor_groups_.push_back(group); // �O���[�v���X�g�ɒǉ�
				// �U��q�𐶐� 
				auto pendulum_ = new Pendulum(game_manager_, objPos, false, 30.f, Pendulum::LangthState::Normal);
				auto weakFloorGroup = dynamic_cast<WeakFloorGroup*>(group);
				// �U��q�ƘA�����������U��q���Z�b�g
				weakFloorGroup->SetPendulumANDMovement(pendulum_);
			}

			// �^�C���̈ʒu�ƃO���[�v���֘A�t����
			weak_tile_to_group_[{_x, _y}] = group;
		}
	}

	else if (_tileID == 3)	// �U��q
	{
		obj = new Pendulum(game_manager_, objPos, false, 30.0f, Pendulum::LangthState::Short);
	}
	else if (_tileID == 33)	
	{
		obj = new Pendulum(game_manager_, objPos, false, 30.0f, Pendulum::LangthState::Normal);
	}
	else if (_tileID == 333)
	{
		obj = new Pendulum(game_manager_, objPos, false, 30.0f, Pendulum::LangthState::Long);
	}

	else if (_tileID == 4)	// �S���̑���
	{
		obj = new SteePillarFloor(game_manager_);
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
					sprite->SetTexture("steelpillar_floor_center");	// ����
					sprite->SetFlip(true, false);
				}
				else {
					sprite->SetTexture("steelpillar_floor_end_02");	// �E
				}
			}
			// ���Ƀ^�C�����Ȃ�
			else if (right) {// �E�Ƀ^�C��������
				sprite->SetTexture("steelpillar_floor_end_01");	// ��
			}
		}
		// �����̃O���[�v��T��
		SteePillarFloorGroup* group = nullptr;
		if (IsTileInGroup(_x - 1, _y, group) || IsTileInGroup(_x + 1, _y, group) ||
			IsTileInGroup(_x, _y - 1, group) || IsTileInGroup(_x, _y + 1, group))
		{
			// �אڃO���[�v�����������ꍇ�A���̃O���[�v�ɒǉ�
			group->AddSteePillarFloorTile(obj);
		}
		else
		{
			// �V�����O���[�v���쐬
			group = new SteePillarFloorGroup(game_manager_);
			group->AddSteePillarFloorTile(obj);
			stee_pillar_floor_groups_.push_back(group); // �O���[�v���X�g�ɒǉ�
			// �U��q�𐶐� 
			auto pendulum_ = new Pendulum(game_manager_, objPos, false, 30.f, Pendulum::LangthState::Normal);
			auto steePillarFloorGroup = dynamic_cast<SteePillarFloorGroup*>(group);
			// �U��q�ƘA�����������U��q���Z�b�g
			steePillarFloorGroup->SetPendulumANDMovement(pendulum_);
		}
		// �^�C���̈ʒu�ƃO���[�v���֘A�t����
		stee_pillar_to_group_[{_x, _y}] = group;
	}
	else if (_tileID == 5)	// �S���̉E��
	{
		obj = new SteePillarRight(game_manager_);
	}
	else if (_tileID == 6)	// �S���̍���
	{
		obj = new SteePillarLeft(game_manager_);
		obj->GetComponent<SpriteComponent>()->SetFlip(true, false);	// �����������]
		obj->GetComponent<SpriteComponent>()->SetUV();
	}
	else if (_tileID == 7)	// �r���ǂ̎n�_
	{
		bool New = false;
		// ���̏I�_��T��
		for (int i = 1; i < 10; i++) {
			bool up = GetAdjacentTile(10, _x, _y, 0, -i);
			if (up) {
				obj = new SmokePipe(game_manager_, i + 1);
				New = true;
				break;
			}
		}
		// �I�_��������Ȃ������ꍇ�A�f�t�H���g�i3�}�X�j
		if (!New) obj = new SmokePipe(game_manager_);
	}

	else if (_tileID == 8)	// �E������
	{
		obj = new Wall(game_manager_);
	}

	else if (_tileID == 9)	// ��������
	{
		obj = new Wall(game_manager_);
		obj->GetComponent<SpriteComponent>()->SetFlip(true, false);
	}

	else if (_tileID >= 100 && _tileID <= 109)	// ���t�g
	{
		// ���t�g�̏I�_��T��	������Ȃ�������Ƃ肠���������ʒu��
		Vector3 endPos = objPos;
		bool foundEndPos = false;
		for (int y = 0; y < map_data_.size(); ++y)
		{
			for (int x = 0; x < map_data_[y].size(); ++x)
			{
				for (int tileID : map_data_[y][x])
				{
					if (tileID == _tileID + 10) // ������ID+10�����t�g�̏I�_
					{
						Vector2 ep = { x - MAP_SIZE_X / 2 , y - MAP_SIZE_Y / 2 };	// ���W�̒���
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

		// �ړ�������ݒ�	�������������ɔ��肵�ĊJ�n���̈ړ����������߂Ă���������
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
		// ���t�g����
		obj = new Lift(game_manager_, direction, objPos, endPos);
		auto lift = dynamic_cast<Lift*>(obj);
		lift->GetTransformComponent()->SetPosition(objPos.x, objPos.y);

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
					sprite->SetTexture("lift_floor_center");	// ����
				}
				else {
					sprite->SetTexture("lift_floor_right");	// �E
				}
			}
			// ���Ƀ^�C�����Ȃ�
			else if (right) {// �E�Ƀ^�C��������
				sprite->SetTexture("lift_floor_left");	// ��
			}

			// �����̃O���[�v��T��
			LiftGroup* group = nullptr;
			if (IsTileInGroup(_x - 1, _y, group) || IsTileInGroup(_x + 1, _y, group) ||
				IsTileInGroup(_x, _y - 1, group) || IsTileInGroup(_x, _y + 1, group))
			{
				// �אڃO���[�v�����������ꍇ�A���̃O���[�v�ɒǉ�
				group->AddLiftTile(obj);
			}
			else
			{
				// �V�����O���[�v���쐬
				group = new LiftGroup(game_manager_);
				group->AddLiftTile(obj);
				lift_groups_.push_back(group); // �O���[�v���X�g�ɒǉ�
				// �U��q�𐶐� 
				auto pendulum_ = new Pendulum(game_manager_, Vector3(objPos.x, objPos.y, 0.0f), false, 30.f, Pendulum::LangthState::Normal);
				auto liftGroup = dynamic_cast<LiftGroup*>(group);
				// �U��q�ƘA�����������U��q���Z�b�g
				liftGroup->SetPendulumANDMovement(pendulum_);
			}

			// �^�C���̈ʒu�ƃO���[�v���֘A�t����
			lift_tile_to_group_[{_x, _y}] = group;
		}


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
		obj->GetComponent<TransformComponent>()->SetPosition(objPos.x, objPos.y);
	}
}

/*-----------------------------------------------------------------
// @param _tyleID �^�C��ID, _x X���W, _y Y���W, _dx X����, _dy Y����
// @brief ���W�ʒu�ɂ���^�C�����w�肵���^�C�����ǂ������擾
// @return �w�肵���^�C��������: true, �Ȃ�: false
-----------------------------------------------------------------*/
bool TileMapManager::GetAdjacentTile(int _tyleID, int _x, int _y, int _dx, int _dy)
{
	int nx = _x + _dx;
	int ny = _y + _dy;

	// �͈͓����`�F�b�N
	if (nx >= 0 && nx < map_data_[0].size() && ny >= 0 && ny < map_data_.size())
	{
		for (auto& id : map_data_[ny][nx]) // �������m�F�i�s: y, ��: x�j
		{
			if (id == _tyleID)
			{
				return true;
			}
		}
	}

	return false;
}

bool TileMapManager::IsTileInGroup(int x, int y, WeakFloorGroup*& _group)
{
	auto it = weak_tile_to_group_.find({ x, y });
	if (it != weak_tile_to_group_.end())
	{
		_group = it->second;
		return true;
	}
	_group = nullptr;
	return false;
}

bool TileMapManager::IsTileInGroup(int x, int y, LiftGroup*& _group)
{
	auto it = lift_tile_to_group_.find({ x, y });
	if (it != lift_tile_to_group_.end())
	{
		_group = it->second;
		return true;
	}
	_group = nullptr;
	return false;
}
;
bool TileMapManager::IsTileInGroup(int x, int y, SteePillarFloorGroup*& _group)
{
	auto it = stee_pillar_to_group_.find({ x, y });
	if (it != stee_pillar_to_group_.end())
	{
		_group = it->second;
		return true;
	}
	_group = nullptr;
	return false;
}