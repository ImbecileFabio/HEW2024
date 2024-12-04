//=================================================================
// [ColliderManager.cpp] �R���C�_�[�}�l�[�W���[���W���[�� 
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F�R���C�_�[�̊Ǘ����s��
//=================================================================
/*----- �C���N���[�h -----*/
#include "ColliderManager.h"
#include "GameObjects/GameObject/ColliderTestObject.h"
#include "GameObjects/Component/ColliderComponent/CircleColliderComponent.h"
//-----------------------------------------------------------------
// @brief  �R���X�g���N�^
//-----------------------------------------------------------------
ColliderManager::ColliderManager(void)
	:updating_game_objects_(false)
{
	this->InitAll();	// ������
}
//-----------------------------------------------------------------
// @brief  �f�X�g���N�^
//-----------------------------------------------------------------
ColliderManager::~ColliderManager(void)
{
}
//-----------------------------------------------------------------
// @brief  ����������
//-----------------------------------------------------------------
void ColliderManager::InitAll(void)
{
	collider_game_objects_.clear();	// �����蔻��p�R���e�i�̃N���A
}
//-----------------------------------------------------------------
// @brief  �X�V����
//-----------------------------------------------------------------
void ColliderManager::UpdateAll(void)
{
	this->UpdateGameObjects();
}
//-----------------------------------------------------------------
// @brief  �I������
//-----------------------------------------------------------------
void ColliderManager::UninitAll(void)
{
}
//-----------------------------------------------------------------
// @brief  �I�u�W�F�N�g��ǉ�
// @param  _gameObject �ǉ�����Q�[���I�u�W�F�N�g
//-----------------------------------------------------------------
void ColliderManager::AddGameObject(GameObject* _gameObject)
{
	// �Q�[���I�u�W�F�N�g�̍X�V�����œo�^���ύX
	if (updating_game_objects_)
	{
		collider_game_objects_.emplace_back(_gameObject);	// �ҋ@�R���e�i
	}
	else
	{
		collider_game_objects_.emplace_back(_gameObject);			// �ғ��R���e�i
	}
}
//-----------------------------------------------------------------
// @brief  �I�u�W�F�N�g���폜
// @param  _gameObject �폜����Q�[���I�u�W�F�N�g
//-----------------------------------------------------------------
void ColliderManager::RemoveGameObject(GameObject* _gameObject)
{
	// �ҋ@�R���e�i
	auto iter = std::find(pending_game_objects_.begin(), pending_game_objects_.end(), _gameObject);
	if (iter != pending_game_objects_.end())
	{
		std::iter_swap(iter, pending_game_objects_.end() - 1);	// �R���e�i�̍Ō���Ɠ���ւ�
		pending_game_objects_.pop_back();						// �ҋ@�R���e�i����폜

	}
	// �ғ��R���e�i
	iter = std::find(collider_game_objects_.begin(), collider_game_objects_.end(), _gameObject);
	if (iter != collider_game_objects_.end())
	{
		std::iter_swap(iter, collider_game_objects_.end() - 1);	// �R���e�i�̍Ō���Ɠ���ւ�
		collider_game_objects_.pop_back();						// �ғ��R���e�i����폜
	}
}
//-----------------------------------------------------------------
// @brief  �I�u�W�F�N�g��Update�����ׂČĂт�������
//-----------------------------------------------------------------
void ColliderManager::UpdateGameObjects(void)
{
	// ���ׂẴQ�[���I�u�W�F�N�g�̍X�V
	updating_game_objects_ = true;
	//collider_game_objects_.clear();	// Clear���Ȃ��Ə�����������
	for (auto& gameObject : collider_game_objects_)
	{
		gameObject->Update();		// �X�V����
	}
	// �����蔻��̏���
	for (int i = 0; i < collider_game_objects_.size(); i++)
	{
		for (int j = i + 1; j < collider_game_objects_.size(); j++)
		{	// �Փ˂������A���Ă��Ȃ���
			if (collider_game_objects_[i]->GetComponent<ColliderBaseComponent>()->
				CheckCollisionCollider(collider_game_objects_[j]->GetComponent<ColliderBaseComponent>()))
			{	
				// �����������̏������Ăт���
				std::cout << std::format("����������\n");
				collider_game_objects_[i]->OnCollisionEnter2D(*collider_game_objects_[j]);
			}
		}
	}
	updating_game_objects_ = false;

	// �ҋ@���X�g�̃Q�[���I�u�W�F�N�g�̑���
	for (auto& pendingGameObject : pending_game_objects_)
	{
		pendingGameObject->Update();
		collider_game_objects_.emplace_back(pendingGameObject);
	}
	pending_game_objects_.clear();

	// �Q�[���I�u�W�F�N�g���j����Ԃ��`�F�b�N
	std::vector<GameObject*> dead_game_objects;
	for (auto& gameObject : collider_game_objects_)
	{
		if (gameObject->GetState() == GameObject::State::Dead)
		{
			dead_game_objects.emplace_back(gameObject);
		}
	}
}