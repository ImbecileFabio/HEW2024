#include "TimeZone.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
TimeZone::TimeZone(GameManager* _gameManager)
	: GameObject(_gameManager, "TimeZone")
{
	std::cout << std::format("��TimeZone�� -> Constructor\n");
	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
TimeZone::~TimeZone()
{
	delete sprite_component_;
	delete collider_base_component_;
	delete event_base_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void TimeZone::InitGameObject(void)
{
	sprite_component_		 = new SpriteComponent(this, TEXTURE_PATH_"kouka/v01/kouka_01.png");
	this->transform_component_->SetScale(100.0f, 100.0f);
	collider_base_component_ = new CircleColliderComponent(this);
	event_base_component_	 = new ColliderEventComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&TimeZone::OnCollisionEnter, this, std::placeholders::_1));
	event_base_component_->AddEvent(5, f);

}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void TimeZone::UpdateGameObject(void)
{
}
//--------------------------------------------------
// @brief �^�C���]�[���̓����蔻��C�x���g����
//--------------------------------------------------
void TimeZone::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Robot:
		// �����Ń��{�b�g�ׂ̂낵�Ă����Ȃɂ��̃X�s�[�h��ύX�H

		break;
	case GameObject::TypeID::Lift:
		break;
	default:
		break;
	}
}

