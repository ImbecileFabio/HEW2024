//=================================================================
// [WeakFloor.cpp] 脆い床オブジェクトの定義
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：脆い床オブジェクトの定義
//=================================================================
/*----- インクルード -----*/
#include "WeakFloor.h"
#include "../../../GameManager.h"

#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/EventComponent/ColliderEventComponent.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../Component/PushOutComponent.h"

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
WeakFloor::WeakFloor(GameManager* _gameManager, int MaxFloor)
	:GameObject(_gameManager, "WeakFloor")
	, max_floor_(MaxFloor)
{
	if (max_floor_ <= 2) { max_floor_ = 3; }
	class RenderComponent* sprite_component_{};
	class ColliderBaseComponent* collider_component_{};
	class ColliderEventComponent* collider_event_component_{};

	// 左端
	sprite_component_ = new SpriteComponent(this, "tile_center");
	collider_event_component_ = new ColliderEventComponent(this);
	collider_component_ = new BoxColliderComponent(this);
	// 中央
	for (int i = 0; i < (max_floor_ - 2); i++) {

	}
	// 右端


	this->InitGameObject();
}
//--------------------------------------------------
// brief デストラクタ
//--------------------------------------------------
WeakFloor::~WeakFloor(void)
{
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

