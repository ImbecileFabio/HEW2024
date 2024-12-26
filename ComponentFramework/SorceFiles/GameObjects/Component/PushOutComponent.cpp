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
PushOutComponent::PushOutComponent(GameObject* _owner, int _updateOrder) :
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
		std::cout << "PushOutComponent::ResolveCollision -> BoxColliderComponent Not Found\n";
        return;
    }
       // 位置を取得
    auto myPos = myTransform->GetPosition();
    auto otherPos = otherTransform->GetPosition();

    // 自分と相手の AABB を取得
    auto myhitbox = myBoxCollider->GetWorldHitBox();
    auto otherhitbox = otherBoxCollider->GetWorldHitBox();

    // ペネトレーション量
    DirectX::SimpleMath::Vector3 penetration;

    // 重なり量を計算
    float overlapX = min(myhitbox.max_.x, otherhitbox.max_.x) - max(myhitbox.min_.x, otherhitbox.min_.x);
    float overlapY = min(myhitbox.max_.y, otherhitbox.max_.y) - max(myhitbox.min_.y, otherhitbox.min_.y);

    if (overlapX <= 0.0f || overlapY <= 0.0f) { return; }


    // 最小の重なり量を押し出し方向として返す
    if (overlapX < overlapY) {
        penetration = { overlapX * (myhitbox.min_.x < otherhitbox.min_.x ? -1.0f : 1.0f), 0.0f, 0.0f };
    }
    else {
        penetration = { 0.0f, overlapY * (myhitbox.min_.y < otherhitbox.min_.y ? -1.0f : 1.0f), 0.0f };
    }


    // 自分の位置を押し出し
    myTransform->SetPosition(myPos + penetration);
}