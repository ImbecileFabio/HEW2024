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
	, is_robot_(true)	// ロボットかどうか
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
	auto ownerVelocityCom = owner_->GetComponent<VelocityComponent>();
	if (!ownerVelocityCom) return;

	// 地面判定の更新
	bool wasGrounded = is_ground_;
	if (is_robot_)
	{
		CheckGroundCollision();
	}

	// 重力の適用
	if (use_gravity_)
	{
		if (!is_ground_)  //空中にいる場合
		{
			Vector3 currentVel = ownerVelocityCom->GetVelocity();

			// 落下速度制限
			const float maxFallSpeed = -10.0f;
			if (currentVel.y <= maxFallSpeed)
			{
				currentVel.y = maxFallSpeed;
			}
			else
			{
				currentVel.y += gravity_;
			}

			ownerVelocityCom->SetVelocity(currentVel);
		}
	}
}



//--------------------------------------------------
// @brief 地面との当たり判定
// @return 地面に接している: true, 地面に接していない: false
//--------------------------------------------------
bool GravityComponent::CheckGroundCollision()
{
    auto boxCollider = owner_->GetComponent<BoxColliderComponent>();
    if (!boxCollider) return false;

    auto hitbox = boxCollider->GetWorldHitBox();
    AABB groundCheckHitbox = hitbox;

    const float checkOffset = 0.1f;  // 地面判定のオフセット
    const float checkHeight = 4.0f;  // 地面判定の高さ範囲

    // 足元のスキャン範囲を正しく設定
    groundCheckHitbox.min_.y = hitbox.min_.y - checkOffset;  // 現在位置から少し下
    groundCheckHitbox.max_.y = hitbox.min_.y + checkHeight;  // 少し上まで

    auto objects = owner_->GetGameManager()->GetColliderManager()->GetColliderGameObjects();

    // 地面との当たり判定
    for (const auto& obj : objects)
    {
        // 判定除外
        if (obj == owner_) continue;
        if (obj->GetType() == GameObject::TypeID::Item) continue;

        auto otherCollider = obj->GetComponent<BoxColliderComponent>();
        if (!otherCollider) continue;

        auto otherHitbox = otherCollider->GetWorldHitBox();

        // AABB同士の衝突判定
        if (groundCheckHitbox.max_.x > otherHitbox.min_.x &&
            groundCheckHitbox.min_.x < otherHitbox.max_.x &&
            groundCheckHitbox.max_.y > otherHitbox.min_.y &&
            groundCheckHitbox.min_.y < otherHitbox.max_.y)
        {
            // Y軸方向の貫通深度を計算
            float penetrationDepth = otherHitbox.max_.y - groundCheckHitbox.min_.y;

            // 適切な接地判定
            if (penetrationDepth >= 0.0f && penetrationDepth <= checkOffset + checkHeight)
            {
                is_ground_ = true;

                // 接地時に速度をリセット
                if (auto vel = owner_->GetComponent<VelocityComponent>())
                {
                    Vector3 currentVel = vel->GetVelocity();
                    if (currentVel.y < 0)  // 下降中の場合のみ
                    {
                        vel->SetVelocity(Vector3(currentVel.x, 0.0f, currentVel.z));
                    }
                }

                return true;
            }
        }
    }

    is_ground_ = false;
    return false;
}