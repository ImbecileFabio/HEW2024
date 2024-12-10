#include "TimeZoneComponent.h"
#include "../../Component/ColliderComponent/ColliderBaseComponent.h"
#include "../../Component/RigidbodyComponent/VelocityComponent.h"
#include "../../GameObject.h"

//--------------------------------------------------
// @brief タイムゾーンのコンストラクタ
//--------------------------------------------------
TimeZoneComponent::TimeZoneComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	this->Init();
}
//--------------------------------------------------
// @brief タイムゾーンのデストラクタ
//--------------------------------------------------
TimeZoneComponent::~TimeZoneComponent()
{
	this->Uninit();
}
//--------------------------------------------------
// @brief タイムゾーンの初期化
//--------------------------------------------------
void TimeZoneComponent::Init(void)
{	// オブジェクトのコライダーを参照で持つ
	this->collider_component_ = this->owner_->GetComponent<ColliderBaseComponent>();	
	this->velocity_component_ = this->owner_->GetComponent<VelocityComponent>();
}
//--------------------------------------------------
// @brief タイムゾーンの終了処理
//--------------------------------------------------
void TimeZoneComponent::Uninit(void)
{
	delete this->collider_component_;
	delete this->velocity_component_;
}
//--------------------------------------------------
// @brief タイムゾーンの更新処理
//--------------------------------------------------
void TimeZoneComponent::Update(void)
{
}
