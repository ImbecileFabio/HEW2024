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
	this->InitGameObject();
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
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"UI/gear/ver1/gear_01.png");
	collider_base_component_ = new BoxColliderComponent(this);
	event_base_component_ = new ColliderEventComponent(this);

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
		this->state_ = GameObject::State::ColliderOut;
		break;
	default:
		break;
	}
}
