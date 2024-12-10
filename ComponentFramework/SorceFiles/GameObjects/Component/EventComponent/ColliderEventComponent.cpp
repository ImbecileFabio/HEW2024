#include "ColliderEventComponent.h"
//--------------------------------------------------
// @brief イベントのコンストラクタ
//--------------------------------------------------
ColliderEventComponent::ColliderEventComponent(GameObject* _owner, int _updateOrder)
	:EventBaseComponent(_owner, _updateOrder)
{
	this->Init();
}
//--------------------------------------------------
// @brief イベントのデストラクタ
//--------------------------------------------------
ColliderEventComponent::~ColliderEventComponent()
{
}
//--------------------------------------------------
// @brief イベントの初期化処理
//--------------------------------------------------
void ColliderEventComponent::Init(void)
{
}
//--------------------------------------------------
// @brief イベントの更新処理
//--------------------------------------------------
void ColliderEventComponent::Update(void)
{
}
//--------------------------------------------------
// @brief イベントの終了処理
//--------------------------------------------------
void ColliderEventComponent::Uninit(void)
{
}
//--------------------------------------------------
// @brief イベントの追加処理
//--------------------------------------------------
void ColliderEventComponent::AddEvent(std::function<void(GameObject* collidedObject)> _event)
{
	this->functions_.emplace_back(_event);
}