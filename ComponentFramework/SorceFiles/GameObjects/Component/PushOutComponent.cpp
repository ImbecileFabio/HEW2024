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
       // 位置を取得
    auto myPos = myTransform->GetPosition();
    auto otherPos = otherTransform->GetPosition();

    // 自分と相手の AABB を取得
    auto myhitbox = myBoxCollider->GetWorldHitBox();
    auto otherhitbox = otherBoxCollider->GetWorldHitBox();



    // 衝突しているか判定
        if (myhitbox.max_.x > otherhitbox.min_.x &&
            myhitbox.min_.x < otherhitbox.max_.x &&
            myhitbox.max_.y > otherhitbox.min_.y &&
            myhitbox.min_.y < otherhitbox.max_.y)
        {
            // ownerのサイズを取得（高さのみを使用）
            float ownerHeight = myhitbox.max_.y - myhitbox.min_.y;

            // 新しい位置を計算 (現在位置の y をサイズの半分だけ上げる)
            auto myPos = myTransform->GetPosition();
            myTransform->SetPosition({ myPos.x, otherhitbox.max_.y + ownerHeight / 2.0f, myPos.z });
        }
}
