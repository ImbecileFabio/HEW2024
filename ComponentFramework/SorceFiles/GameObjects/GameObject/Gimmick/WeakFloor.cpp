//=================================================================
// [WeakFloor.cpp] 脆い床オブジェクトの定義
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：脆い床オブジェクトの定義
//=================================================================
/*----- インクルード -----*/
#include "WeakFloor.h"
#include "../../Component/TransformComponent.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/EventComponent/ColliderEventComponent.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../Component/GimmickComponent/WeakFloorComponent.h"
#include "../../GameObject/Gimmick/Group/WeakFloorGroup.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
WeakFloor::WeakFloor(GameManager* _gameManager)
	:GameObject(_gameManager, "WeakFloor")
{
	sprite_component_		  = new SpriteComponent(this, "weakfloor_center");
	collider_component_		  = new BoxColliderComponent(this);			// 当たり判定
	collider_event_component_ = new ColliderEventComponent(this);		// 当たり判定イベント
	auto f = std::function<void(GameObject*)>(std::bind(&WeakFloor::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	this->InitGameObject();
}
//--------------------------------------------------
// brief デストラクタ
//--------------------------------------------------
WeakFloor::~WeakFloor(void)
{
	// ここでコンポーネントを削除
	delete sprite_component_;
	delete collider_component_;
	delete collider_event_component_;
	delete weak_floor_component_;
}
//--------------------------------------------------
// @brief グループの参照を設定
// @param _weak_floor_group[脆い床グループ]
//--------------------------------------------------
void WeakFloor::SetWeakFloorGroup(WeakFloorGroup* _weak_floor_group)
{
	weak_floor_group_ = _weak_floor_group;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void WeakFloor::InitGameObject(void)
{

}

//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void WeakFloor::UpdateGameObject(void)
{
}
//--------------------------------------------------
// @brief 当たり判定実行処理
//--------------------------------------------------
void WeakFloor::OnCollisionEnter(GameObject* _other)
{
	if (state_ == State::Paused) return;
	if (_other->GetType() == TypeID::Robot)	// タイルとロボットが接触したら
	{
		weak_floor_group_->SetWeakFloorBreak(true);	// グループに通知
	}
}

