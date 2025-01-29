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
	, is_ground_(false)	// 地面に接地しているか
	, is_robot_ (true)	// ロボットかどうか
	, use_gravity_(true)	// 重力の使用
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
	if (auto ownerVelocityCom = owner_->GetComponent<VelocityComponent>())
	{
		if (!is_robot_ && use_gravity_)
		{
			// 速度が一定以上にならないように制限
			if (ownerVelocityCom->GetVelocity().y < -10.0f)
			{
				ownerVelocityCom->SetVelocity({ 0.0f, -10.0f, 0.0f });
			}
			else
			{
				ownerVelocityCom->SetVelocity({ 0.0f, ownerVelocityCom->GetVelocity().y + gravity_, 0.0f });
			}
			return;
		}
		if (is_robot_)
		{
			CheckGroundCollision();
		}
		// 重力適用
		if (use_gravity_ && !is_ground_ && is_robot_)
		{
			// 速度が一定以上にならないように制限
			if (ownerVelocityCom->GetVelocity().y < -10.0f)
			{
				ownerVelocityCom->SetVelocity({ 0.0f, -10.0f, 0.0f });
			}
			else
			{
				ownerVelocityCom->SetVelocity({ 0.0f, ownerVelocityCom->GetVelocity().y + gravity_, 0.0f });
			}
		}
	}
}



//--------------------------------------------------
// @brief 地面との当たり判定
// @return 地面に接している: true, 地面に接していない: false
//--------------------------------------------------
bool GravityComponent::CheckGroundCollision()
{
	auto robotHitbox = owner_->GetComponent<BoxColliderComponent>()->GetWorldHitBox();
	AABB groundCheckHitbox = robotHitbox;

	// 足元のスキャン範囲を設定（キャラクターサイズに応じて調整）
	float groundCheckHeight = (robotHitbox.max_.y - robotHitbox.min_.y) * 0.02;
	groundCheckHitbox.min_.y -= groundCheckHeight; // 足元少し下に範囲を作成
	groundCheckHitbox.max_.y = robotHitbox.min_.y;
	auto objects = owner_->GetGameManager()->GetColliderManager()->GetColliderGameObjects();

	// 地面との当たり判定
	for (const auto& obj : objects)
	{
		if (obj == owner_) continue; // 自分自身との判定はスキップ
		else if (obj->GetType() == GameObject::TypeID::Item) continue; // 歯車でも浮いちゃうので無視
		//else if (obj->GetType() == GameObject::TypeID::Smoke) continue; // 歯車でも浮いちゃうので無視
		//else if (obj->GetType() == GameObject::TypeID::SmokePipe) continue; // 歯車でも浮いちゃうので無視

		auto otherCollider = obj->GetComponent<ColliderBaseComponent>();
		if (auto otherBoxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider))
		{
			auto otherHitbox = otherBoxCollider->GetWorldHitBox();

			if (groundCheckHitbox.max_.x > otherHitbox.min_.x && groundCheckHitbox.min_.x < otherHitbox.max_.x &&
				groundCheckHitbox.max_.y > otherHitbox.min_.y && groundCheckHitbox.min_.y < otherHitbox.max_.y) {
				is_ground_ = true; // 地面に接している
				return true; // 地面に接している
			}
		}
	}

	is_ground_ = false; // 地面に接していない
	return false; // 地面に接していない
}
