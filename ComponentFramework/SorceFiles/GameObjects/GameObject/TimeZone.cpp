#include "TimeZone.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
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
{	// �f��Ȃ��@�ǂ�����
	//sprite_component_		 = new SpriteComponent(this, TEXTURE_PATH_"kouka/v01/kouka_01.png");
	sprite_component_		 = new SpriteComponent(this, TEXTURE_PATH_"zako.png", 60);
	this->transform_component_->SetScale(200.0f, 200.0f);
	collider_base_component_ = new CircleColliderComponent(this);
	event_base_component_	 = new ColliderEventComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&TimeZone::OnCollisionEnter, this, std::placeholders::_1));
	event_base_component_->AddEvent(f);
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
		_other->GetComponent<VelocityComponent>()->SetSpeedRate(0.5f);
		break;
	case GameObject::TypeID::Lift:
		_other->GetComponent<VelocityComponent>()->SetSpeedRate(0.5f);
		break;
	default:
		break;
	}
}

