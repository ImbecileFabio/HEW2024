#include "Item.h"
#include "../../GameManager.h"
#include "../../ColliderManager.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
Item::Item(GameManager* _gameManager)
	: GameObject(_gameManager, "Item")
{
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"UI/gear/ver1/gear_01.png");
	collider_base_component_ = new BoxColliderComponent(this);
	event_base_component_ = new ColliderEventComponent(this);
	state_ = State::Active;
	auto f = std::function<void(GameObject*)>(std::bind(&Item::OnCollisionEnter, this, std::placeholders::_1));
	event_base_component_->AddEvent(f);
	this->InitGameObject();

	sound_.Init();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
Item::~Item()
{
	delete sprite_component_;
	delete collider_base_component_;
	delete event_base_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void Item::InitGameObject(void)
{
	sprite_component_->SetState(SpriteComponent::State::draw);
	this->state_ = GameObject::State::Active;
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void Item::UpdateGameObject(void)
{
}
//--------------------------------------------------
// @brief �����������̏���
//--------------------------------------------------
void Item::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Robot:
		// ���{�b�g���ڐG������
		std::cout << "Item -> Robot -> OnCollisionEnter\n" << std::endl;
		this->GetGameManager()->itemCountUp();
		this->event_base_component_->RemoveEvent();
		this->sprite_component_->SetState(SpriteComponent::State::notDraw);
		this->state_ = GameObject::State::ColliderOut;

		// �T�E���h�Đ�
		sound_.Play(SoundLabel_ItemGet);
		break;
	default:
		break;
	}
}
