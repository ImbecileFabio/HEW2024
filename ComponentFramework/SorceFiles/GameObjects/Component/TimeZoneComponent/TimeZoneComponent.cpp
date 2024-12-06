#include "TimeZoneComponent.h"
#include "../../Component/ColliderComponent/ColliderBaseComponent.h"
#include "../../Component/RigidbodyComponent.h"
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
	this->colliderComponent_ = this->owner_->GetComponent<ColliderBaseComponent>();	
	this->rigidbodyComponent_ = this->owner_->GetComponent<RigidbodyComponent>();
}
//--------------------------------------------------
// @brief タイムゾーンの終了処理
//--------------------------------------------------
void TimeZoneComponent::Uninit(void)
{
	delete this->colliderComponent_;
	delete this->rigidbodyComponent_;
}
//--------------------------------------------------
// @brief タイムゾーンの更新処理
//--------------------------------------------------
void TimeZoneComponent::Update(void)
{
}
