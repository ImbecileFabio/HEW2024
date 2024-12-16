#include "TimeZone.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
TimeZone::TimeZone(GameManager* _gameManager)
	: GameObject(_gameManager, "TimeZone")
{
	std::cout << std::format("＜TimeZone＞ -> Constructor\n");
	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
TimeZone::~TimeZone()
{
	delete sprite_component_;
	delete collider_base_component_;
	delete event_base_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void TimeZone::InitGameObject(void)
{	// 映らない　どうして
	//sprite_component_		 = new SpriteComponent(this, TEXTURE_PATH_"kouka/v01/kouka_01.png");
	sprite_component_		 = new SpriteComponent(this, TEXTURE_PATH_"zako.png");
	this->transform_component_->SetScale(100.0f, 100.0f);
	this->transform_component_->SetPosition(100.0f, 0.0f);
	collider_base_component_ = new CircleColliderComponent(this);
	event_base_component_	 = new ColliderEventComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&TimeZone::OnCollisionEnter, this, std::placeholders::_1));
	event_base_component_->AddEvent(f);
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void TimeZone::UpdateGameObject(void)
{
}
//--------------------------------------------------
// @brief タイムゾーンの当たり判定イベント処理
//--------------------------------------------------
void TimeZone::OnCollisionEnter(GameObject* _other)
{
	switch (_other->GetType())
	{
	case GameObject::TypeID::Robot:
		// タイムゾーンの方で一括管理しておいた方が散らばりにくいかも
		std::cout << std::format("＜TimeZone＞ -> ＜Robot＞ -> OnCollisionEnter\n");
		break;
	case GameObject::TypeID::Lift:
		break;
	default:
		break;
	}
}

