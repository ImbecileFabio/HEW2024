//==================================================
// [GravityComponent.cpp] 重力コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：重力を制御するコンポーネント
//==================================================
/*----- インクルード -----*/
#include "../../GameManager.h"
#include "../../ColliderManager.h"
#include "../GameObject.h"
#include "RigidbodyComponent/VelocityComponent.h"
#include "ColliderComponent/BoxColliderComponent.h"
#include "GravityComponent.h"

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
GravityComponent::GravityComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
	, gravity_(-1.0f)	// 重力
{
	this->Init();
}


//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
GravityComponent::~GravityComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void GravityComponent::Init()
{
	velocity_ = nullptr;
	collider_ = nullptr;
	is_ground_ = false;
	use_gravity_ = true;
}
//--------------------------------------------------
// @brief 終了処理
//--------------------------------------------------
void GravityComponent::Uninit()
{

}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void GravityComponent::Update()
{
	if (!velocity_ || !collider_)	//	一度だけ取得
	{
	velocity_ = this->owner_->GetComponent<VelocityComponent>();
	collider_ = this->owner_->GetComponent<BoxColliderComponent>();
	}

	// 地上に居てるか
	is_ground_ = CheckGroundCollishion();

	use_gravity_ = !is_ground_;

	// 重力適用
	if (use_gravity_)	
	{
		velocity_->SetVelocity(Vector3(0.0f, gravity_, 0.0f));
	}

}



//--------------------------------------------------
// @brief 地面との当たり判定
// @return 地面に接している: true, 地面に接していない: false
//--------------------------------------------------
bool GravityComponent::CheckGroundCollishion()
{
	auto robotHitbox = collider_->GetWorldHitBox();
	AABB groundCheckHitbox = robotHitbox;

	// 足元にチェック判定を作成
	groundCheckHitbox.min_.y -= 1.0f;
	groundCheckHitbox.max_.y = robotHitbox.min_.y;

	auto objects = owner_->GetGameManager()->GetColliderManager()->GetColliderGameObjects();

	// 地面との当たり判定
	for (const auto& obj : objects)
	{
		auto otherCollider = obj->GetComponent<ColliderBaseComponent>();
		if (auto otherBoxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider))
		{
			auto otherHitbox = otherBoxCollider->GetWorldHitBox();

			if (groundCheckHitbox.max_.x > otherHitbox.min_.x && groundCheckHitbox.min_.x < otherHitbox.max_.x &&
				groundCheckHitbox.max_.y > otherHitbox.min_.y && groundCheckHitbox.min_.y < otherHitbox.max_.y) {
				return true; // 地面に接している
			}
		}
	}

	return false; // 地面に接していない
}
