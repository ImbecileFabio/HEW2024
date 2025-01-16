//==================================================
// [WeakFloorComponent.cpp] 脆い床ギミックコンポーネントソース
// 著者：有馬啓太
//--------------------------------------------------
// 説明：脆い床ギミックコンポーネントの定義
//==================================================
/*----- インクルード -----*/
#include "WeakFloorComponent.h"
#include "../../GameObject.h"
#include "../ColliderComponent/BoxColliderComponent.h"
#include "../RigidbodyComponent/VelocityComponent.h"
#include "../GravityComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
WeakFloorComponent::WeakFloorComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{

	this->Init();
}


//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
WeakFloorComponent::~WeakFloorComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void WeakFloorComponent::Init()
{
	owner_transform_ = owner_->GetTransformComponent();
	owner_collider_ = owner_->GetComponent<BoxColliderComponent>();
}
//--------------------------------------------------
// @brief 終了処理
//--------------------------------------------------
void WeakFloorComponent::Uninit()
{
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void WeakFloorComponent::Update()
{
	if (!owner_transform_ || !owner_collider_)	//	一度だけ取得
	{
		owner_transform_ = owner_->GetTransformComponent();
		owner_collider_ = owner_->GetComponent<BoxColliderComponent>();
	}

	if (!owner_transform_ || !owner_collider_)
	{
		std::cout << std::format("＜WeakFloorComponent＞ -> Update Error\n");
		return;
	}
}
