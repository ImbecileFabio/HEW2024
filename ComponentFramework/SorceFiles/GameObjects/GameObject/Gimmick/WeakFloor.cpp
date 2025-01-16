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
	if (max_floor_ <= 2) { max_floor_ = 3; }	// 最短３マス

	// Floor毎のComponentをWeakFloorComponentListに纏めて、WeakFloorListに入れる

	//// 左端
	//WeakFloorComponentList.push_back(std::make_shared<SpriteComponent>(this, "weakfloor_left"));
	//WeakFloorComponentList.push_back(std::make_shared<ColliderEventComponent>(this));
	//WeakFloorComponentList.push_back(std::make_shared<BoxColliderComponent>(this));
	//WeakFloorList.emplace_back(WeakFloorComponentList);
	//for(auto List:)
	//WeakFloorComponentList.clear();
	//// 中央
	//for (int i = 0; i < (max_floor_ - 2); i++) {
	//	WeakFloorComponentList.push_back(std::make_shared<SpriteComponent>(this, "weakfloor_cnter"));
	//	WeakFloorComponentList.push_back(std::make_shared<ColliderEventComponent>(this));
	//	WeakFloorComponentList.push_back(std::make_shared<BoxColliderComponent>(this));
	//	WeakFloorList.emplace_back(WeakFloorComponentList);
	//	WeakFloorComponentList.clear();
	//}
	//// 右端
	//WeakFloorComponentList.push_back(std::make_shared<SpriteComponent>(this, "weakfloor_right"));
	//WeakFloorComponentList.push_back(std::make_shared<ColliderEventComponent>(this));
	//WeakFloorComponentList.push_back(std::make_shared<BoxColliderComponent>(this));
	//WeakFloorList.emplace_back(WeakFloorComponentList);
	//WeakFloorComponentList.clear();

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