//=================================================================
// [WeakFloor.cpp] �Ƃ����I�u�W�F�N�g�̒�`
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�Ƃ����I�u�W�F�N�g�̒�`
//=================================================================
/*----- �C���N���[�h -----*/
#include "WeakFloor.h"
#include "../../../GameManager.h"

#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/EventComponent/ColliderEventComponent.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../Component/PushOutComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
WeakFloor::WeakFloor(GameManager* _gameManager, int MaxFloor)
	:GameObject(_gameManager, "WeakFloor")
	, max_floor_(MaxFloor)
{
	if (max_floor_ <= 2) { max_floor_ = 3; }	// �ŒZ�R�}�X

	// Floor����Component��WeakFloorComponentList�ɓZ�߂āAWeakFloorList�ɓ����

	//// ���[
	//WeakFloorComponentList.push_back(std::make_shared<SpriteComponent>(this, "weakfloor_left"));
	//WeakFloorComponentList.push_back(std::make_shared<ColliderEventComponent>(this));
	//WeakFloorComponentList.push_back(std::make_shared<BoxColliderComponent>(this));
	//WeakFloorList.emplace_back(WeakFloorComponentList);
	//for(auto List:)
	//WeakFloorComponentList.clear();
	//// ����
	//for (int i = 0; i < (max_floor_ - 2); i++) {
	//	WeakFloorComponentList.push_back(std::make_shared<SpriteComponent>(this, "weakfloor_cnter"));
	//	WeakFloorComponentList.push_back(std::make_shared<ColliderEventComponent>(this));
	//	WeakFloorComponentList.push_back(std::make_shared<BoxColliderComponent>(this));
	//	WeakFloorList.emplace_back(WeakFloorComponentList);
	//	WeakFloorComponentList.clear();
	//}
	//// �E�[
	//WeakFloorComponentList.push_back(std::make_shared<SpriteComponent>(this, "weakfloor_right"));
	//WeakFloorComponentList.push_back(std::make_shared<ColliderEventComponent>(this));
	//WeakFloorComponentList.push_back(std::make_shared<BoxColliderComponent>(this));
	//WeakFloorList.emplace_back(WeakFloorComponentList);
	//WeakFloorComponentList.clear();

	this->InitGameObject();
}
//--------------------------------------------------
// brief �f�X�g���N�^
//--------------------------------------------------
WeakFloor::~WeakFloor(void)
{
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void WeakFloor::InitGameObject(void)
{
}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void WeakFloor::UpdateGameObject(void)
{
}