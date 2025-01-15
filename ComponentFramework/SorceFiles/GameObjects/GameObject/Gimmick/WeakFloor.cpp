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
	if (max_floor_ <= 2) { max_floor_ = 3; }
	class RenderComponent* sprite_component_{};
	class ColliderBaseComponent* collider_component_{};
	class ColliderEventComponent* collider_event_component_{};

	// ���[
	sprite_component_ = new SpriteComponent(this, "tile_center");
	collider_event_component_ = new ColliderEventComponent(this);
	collider_component_ = new BoxColliderComponent(this);
	// ����
	for (int i = 0; i < (max_floor_ - 2); i++) {

	}
	// �E�[


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

