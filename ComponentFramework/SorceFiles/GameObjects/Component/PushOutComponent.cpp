//=================================================================
// [PushOutComponent.cpp] 押し出しコンポーネント
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：コライダーを持っている者同士を押し出す処理を行う
// 
//=================================================================
#include "PushOutComponent.h"

#include "../Component.h"
#include "../GameObject.h"

#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/TransformComponent.h"


//-----------------------------------------------------------------
// コンストラクタ
//-----------------------------------------------------------------
PushOutComponent::PushOutComponent(GameObject* _owner, int _updateOrder):
	Component(_owner, _updateOrder)
{
    this->Init();
}

//-----------------------------------------------------------------
// デストラクタ
//-----------------------------------------------------------------
PushOutComponent::~PushOutComponent()
{
	this->Uninit();
}

//-----------------------------------------------------------------
// 初期化処理
//-----------------------------------------------------------------
void PushOutComponent::Init(void)
{
}

//-----------------------------------------------------------------
// 終了処理
//-----------------------------------------------------------------
void PushOutComponent::Uninit(void)
{
}

//-----------------------------------------------------------------
// @param _other 衝突したオブジェクト
// @brief 押し出し量を計算する処理
//-----------------------------------------------------------------
void PushOutComponent::ResolveCollision(GameObject* _other) {

    auto myTransform = owner_->GetTransformComponent();
    auto myCollider = owner_->GetComponent<ColliderBaseComponent>();
    auto otherTransform = _other->GetTransformComponent();
    auto otherCollider = _other->GetComponent<ColliderBaseComponent>();

    auto myBoxCollider = dynamic_cast<BoxColliderComponent*>(myCollider);
    auto otherBoxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider);

    if (!myBoxCollider || !otherBoxCollider) {
        return;
    }

    // AABB を取得
    auto myhitbox = myBoxCollider->GetWorldHitBox();
    auto otherhitbox = otherBoxCollider->GetWorldHitBox();

    // 衝突判定
    if (myhitbox.max_.x > otherhitbox.min_.x &&
        myhitbox.min_.x < otherhitbox.max_.x &&
        myhitbox.max_.y > otherhitbox.min_.y &&
        myhitbox.min_.y < otherhitbox.max_.y)
    {
        // 衝突の深さを計算
        float overlapX = min(myhitbox.max_.x - otherhitbox.min_.x, otherhitbox.max_.x - myhitbox.min_.x);
        float overlapY = min(myhitbox.max_.y - otherhitbox.min_.y, otherhitbox.max_.y - myhitbox.min_.y);

        // XとYどちらの衝突が深いかを判定
        if (overlapX < overlapY) {
            // 横方向の補正（左右の押し出し）
            if (myhitbox.min_.x < otherhitbox.min_.x) {
                myTransform->SetPosition({ otherhitbox.min_.x - (myhitbox.max_.x - myhitbox.min_.x) / 2.0f, myTransform->GetPosition().y, myTransform->GetPosition().z });
            }
            else {
                myTransform->SetPosition({ otherhitbox.max_.x + (myhitbox.max_.x - myhitbox.min_.x) / 2.0f, myTransform->GetPosition().y, myTransform->GetPosition().z });
            }
        }
        else {
            // 縦方向の補正（上または下からの押し出し）
            if (myhitbox.min_.y < otherhitbox.min_.y) {
                // 上から当たっている場合 → 床の上に補正
                myTransform->SetPosition({ myTransform->GetPosition().x, otherhitbox.min_.y - (myhitbox.max_.y - myhitbox.min_.y) / 2.0f, myTransform->GetPosition().z });
            }
            else {
                // 下から当たっている場合 → 床の下に補正
                myTransform->SetPosition({ myTransform->GetPosition().x, otherhitbox.max_.y + (myhitbox.max_.y - myhitbox.min_.y) / 2.0f, myTransform->GetPosition().z });
            }
        }
    }
}
