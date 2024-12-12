#include "ColliderEventComponent.h"

int ColliderEventComponent::hoge = 0;
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
	functions_.clear();
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
	for (auto& it : functions_)
	{
		it(_other);
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