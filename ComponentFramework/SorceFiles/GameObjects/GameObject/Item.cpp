#include "Item.h"
#include "../../GameManager.h"
#include "../../ColliderManager.h"
#include "../../AudioManager.h"
#include "../../TileMapManager.h"

#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
Item::Item(GameManager* _gameManager)
	: GameObject(_gameManager, "Item")
{
	sprite_component_ = new SpriteComponent(this,"gear");
	collider_base_component_ = new BoxColliderComponent(this);
	event_base_component_ = new ColliderEventComponent(this);
	state_ = State::Active;
	auto f = std::function<void(GameObject*)>(std::bind(&Item::OnCollisionEnter, this, std::placeholders::_1));
	event_base_component_->AddEvent(f);
	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
Item::~Item()
{
	event_base_component_->ResetID();
	delete sprite_component_;
	delete collider_base_component_;
	delete event_base_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void Item::InitGameObject(void)
{
	transform_component_->SetSize(TILE_SIZE_X * 1.5f, TILE_SIZE_Y * 1.5f);


	sprite_component_->SetState(SpriteComponent::State::draw);
	this->state_ = GameObject::State::Active;
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
		this->sprite_component_->SetState(SpriteComponent::State::notDraw);
		this->state_ = GameObject::State::Dead;

		// サウンド再生
		AudioManager::GetInstance()->Play(SoundLabel_ItemGet);
		break;
	default:
		break;
	}
}
