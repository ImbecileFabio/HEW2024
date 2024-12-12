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
//void ColliderEventComponent::Update(GameObject* _other)
//{
//
//}
//--------------------------------------------------
// @brief イベントの終了処理
//--------------------------------------------------
void ColliderEventComponent::Uninit(void)
{
}
void ColliderEventComponent::AllUpdate(GameObject* _other)
{
	for (int idx = 0; idx < functions_.size(); idx++)
	{
		functions_.at(idx)(_other);
	}
}
//--------------------------------------------------
// @brief イベントの追加処理
//--------------------------------------------------
void ColliderEventComponent::AddEvent(std::function<void(GameObject* _other)> _event)
{
	this->functions_.emplace_back(_event);

	std::cout << std::format("＜ColliderEventComponent＞ -> イベント追加？\n");
}