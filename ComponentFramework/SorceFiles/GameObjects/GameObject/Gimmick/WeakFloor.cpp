//=================================================================
// [WeakFloor.cpp] �Ƃ����I�u�W�F�N�g�̒�`
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�Ƃ����I�u�W�F�N�g�̒�`
//=================================================================
/*----- �C���N���[�h -----*/
#include "WeakFloor.h"
#include "../../Component/TransformComponent.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/EventComponent/ColliderEventComponent.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../Component/GimmickComponent/WeakFloorComponent.h"
#include "../../GameObject/Gimmick/Group/WeakFloorGroup.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
WeakFloor::WeakFloor(GameManager* _gameManager)
	:GameObject(_gameManager, "WeakFloor")
{
	sprite_component_		  = new SpriteComponent(this, "weakfloor_center");
	collider_component_		  = new BoxColliderComponent(this);			// �����蔻��
	collider_event_component_ = new ColliderEventComponent(this);		// �����蔻��C�x���g
	auto f = std::function<void(GameObject*)>(std::bind(&WeakFloor::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	this->InitGameObject();
}
//--------------------------------------------------
// brief �f�X�g���N�^
//--------------------------------------------------
WeakFloor::~WeakFloor(void)
{
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete collider_component_;
	delete collider_event_component_;
	delete weak_floor_component_;
}
//--------------------------------------------------
// @brief �O���[�v�̎Q�Ƃ�ݒ�
// @param _weak_floor_group[�Ƃ����O���[�v]
//--------------------------------------------------
void WeakFloor::SetWeakFloorGroup(WeakFloorGroup* _weak_floor_group)
{
	weak_floor_group_ = _weak_floor_group;
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
//--------------------------------------------------
// @brief �����蔻����s����
//--------------------------------------------------
void WeakFloor::OnCollisionEnter(GameObject* _other)
{
	if (state_ == State::Paused) return;
	if (_other->GetType() == TypeID::Robot)	// �^�C���ƃ��{�b�g���ڐG������
	{
		weak_floor_group_->SetWeakFloorBreak(true);	// �O���[�v�ɒʒm
	}
}

