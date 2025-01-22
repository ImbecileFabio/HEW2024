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
#include "../RenderComponent/SpriteComponent.h"
#include "../RenderComponent.h"
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
	owner_sprite_ = owner_->GetComponent<RenderComponent>();
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
	if (!owner_transform_ || !owner_collider_ || !owner_sprite_)
	{
		std::cout << std::format("＜WeakFloorComponent＞ -> Update Error\n");
		return;
	}
}
//--------------------------------------------------
// @brief 画像を描画しないように変える
//--------------------------------------------------
void WeakFloorComponent::NotSpriteDraw(void)
{
	owner_sprite_->SetState(RenderComponent::State::notDraw);
}
