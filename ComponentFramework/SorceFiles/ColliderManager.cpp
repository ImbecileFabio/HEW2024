//=================================================================
// [ColliderManager.cpp] �R���C�_�[�}�l�[�W���[���W���[�� 
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F�R���C�_�[�̊Ǘ����s��
//=================================================================
/*----- �C���N���[�h -----*/
#include "ColliderManager.h"
#include "GameObjects/GameObject.h"
#include "GameObjects/Component/ColliderComponent/CircleColliderComponent.h"
#include "GameObjects/Component/ColliderComponent/BoxColliderComponent.h"
#include "GameObjects/Component/EventComponent/ColliderEventComponent.h"
#include "GameObjects/Component/RobotMoveComponent.h"
#include "GameObjects/Component/RigidbodyComponent/VelocityComponent.h"
#include "ImGuiManager.h"
//----------------------------------------------------------------
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
	collider_out_objects_.clear();
	pending_game_objects_.clear();

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
	collider_game_objects_.clear();	// �����蔻��p�R���e�i�̃N���A
	collider_out_objects_.clear();
	pending_game_objects_.clear();
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
		collider_game_objects_.emplace_back(_gameObject);	// �ғ��R���e�i
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
	for (auto it1 = collider_game_objects_.begin(); it1 != collider_game_objects_.end(); ++it1) 
	{
		auto collider1 = (*it1)->GetComponent<ColliderBaseComponent>();
		auto event1 = (*it1)->GetComponent<EventBaseComponent>();

		// collider1 �܂��� event1 �� nullptr �̏ꍇ�̓X�L�b�v
		if (collider1 == nullptr || event1 == nullptr) continue;

		for (auto it2 = collider_game_objects_.begin(); it2 != collider_game_objects_.end(); ++it2)
		{
			// ���Ȕ�����X�L�b�v
			if (it1 == it2) continue;

			auto collider2 = (*it2)->GetComponent<ColliderBaseComponent>();
			if (collider2 == nullptr) continue;

			// �Փ˔���
			if (collider1->CheckCollisionCollider(collider2))
			{
				// �C�x���g����
				size_t id = event1->GetId();
				event1->AllUpdate(*it2, id);
			}
			else
			{
			}
		}
	}
	updating_game_objects_ = false;
	// �����蔻������Ȃ��Ȃ����I�u�W�F�N�g�̈ړ�
	for (auto it = collider_game_objects_.begin(); it != collider_game_objects_.end(); ) 
	{

		//if ((*it)->GetState() == GameObject::State::Paused)
		//{
		//	collider_out_objects_.emplace_back(std::move(*it));
		//	it = collider_game_objects_.erase(it); // �v�f���폜�����̗v�f��
		//}
		//else 
		//{
		//	++it;
		//}
		if ((*it)->GetState() == GameObject::State::Dead)
		{
			collider_out_objects_.emplace_back(std::move(*it));
			it = collider_game_objects_.erase(it); // �v�f���폜�����̗v�f��
		}
		else 
		{
			++it;
		}
	}
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


//#include <functional>
//
//int TestFunc() {
//	return 100;
//}
//
//class FuncClass {
//public:
//	int operator+ (int a) {
//		return a * rate;
//	}
//	void operator() (int i) {
//
//	}
//	int rate;
//};
//
//class MyVector {
//public:
//	MyVector();
//	MyVector(float x, float y, float z) {
//		this->x = x:
//		this->x = x :
//			this->x = x :
//	}
//	MyVector(XMFLOAT3 src) {
//		MyVector(src.x, src.y, src.z);
//	}
//
//	static MyVector operator+(MyVector left, MyVector right) {
//		MyVector result;
//		result.x = -100.0f:
//		exit();
//		new int[100];
//		result.x = left.x + right.x;
//		result.y = left.y + right.y;
//		result.z = left.z + right.z;
//		return result;
//	}
//	float x, y, z;
//
//
//
//};
//FuncClass funcInst;
//funcInst.operator()(100);
//funcInst(100);
//
//int ret = funcInst.operator+(10);
//ret = funcInst + 10;
//
//
//std::list<std::function<int>> funcs;
//
//funcs.push_back(funcInst);
//
//funcs.push_back(TestFunc);
//for (int idx = 0; idx < func.size(); idx++) {
//	funcs[idx]();
//}