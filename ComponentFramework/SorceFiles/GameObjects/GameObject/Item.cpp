#include "Item.h"
#include "../../GameManager.h"
#include "../../ColliderManager.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
Item::Item(GameManager* _gameManager)
	: GameObject(_gameManager, "Item")
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
Item::~Item()
{
	delete sprite_component_;
	delete collider_base_component_;
	delete event_base_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void Item::InitGameObject(void)
{
	sprite_component_ = new SpriteComponent(this, TEXTURE_PATH_"UI/gear/ver1/gear_01.png");
	collider_base_component_ = new BoxColliderComponent(this);
	event_base_component_ = new ColliderEventComponent(this);

}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void Item::UpdateGameObject(void)
{
}
//--------------------------------------------------
// @brief 当たった時の処理
//--------------------------------------------------
void Item::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Robot:
		// ロボットが接触したら
		std::cout << "Item -> Robot -> OnCollisionEnter\n" << std::endl;
		this->GetGameManager()->itemCountUp();
		this->event_base_component_->RemoveEvent();
		this->state_ = GameObject::State::ColliderOut;
		break;
	default:
		break;
	}
}
