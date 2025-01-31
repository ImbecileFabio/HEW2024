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
	functions_.clear();
}
//--------------------------------------------------
// @brief イベントの終了処理
//--------------------------------------------------
void ColliderEventComponent::Uninit(void)
{
	for (auto& func : functions_)
	{
		func.second = nullptr;
	}
}
//--------------------------------------------------
// @brief 追加されたイベントの実行処理
// @param _other 当たり判定を取るオブジェクト
//--------------------------------------------------
void ColliderEventComponent::AllUpdate(GameObject* _other, size_t _id)
{

	auto it = functions_.find(_id);
	if (it != functions_.end()) 
	{
		it->second(_other);  // 関数を呼び出す
	}
	else {
	}

}
//--------------------------------------------------
// @brief イベントの追加処理
//--------------------------------------------------
void ColliderEventComponent::AddEvent(std::function<void(GameObject* _other)>&_event)
{
	generalId_++;
	id_ = generalId_;
	this->functions_[id_] = _event;
}

void ColliderEventComponent::RemoveEvent()
{	
	// 自身のIDをキーとして、渡されたイベントを削除
	auto it = functions_.find(id_);
	if (it != functions_.end())
	{
		functions_.erase(it);
	}
	else
	{
	}
}
