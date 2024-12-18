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
// @brief 衝突を解決する処理
// @param _other 衝突したオブジェクト
//-----------------------------------------------------------------
void PushOutComponent::ResolveCollision(GameObject* other) {
    auto myTransform = owner_->GetComponent<TransformComponent>();
    auto myCollider = owner_->GetComponent<BoxColliderComponent>();
    auto otherTransform = other->GetComponent<TransformComponent>();
    auto otherCollider = other->GetComponent<BoxColliderComponent>();

    // 必要なコンポーネントがなければ何もしない
    if (!myTransform || !myCollider || !otherTransform || !otherCollider)
    {
        return;
    }

    // 自分と相手の AABB を取得
    auto myBox = myCollider->GetBoxSize();
    auto myPos = myTransform->GetPosition();
    auto otherBox = otherCollider->GetBoxSize();
    auto otherPos = otherTransform->GetPosition();

    // ペネトレーション量を計算
    DirectX::SimpleMath::Vector3 penetration = CalculatePushOut(myPos, myBox, otherPos, otherBox);

    // 自分の位置を押し出し
    myTransform->SetPosition(myPos + penetration);
}


//-----------------------------------------------------------------
// @brief 押し出し量を計算する
// @param myPos 自分の位置, myBox 自分のAABB, otherPos 相手の位置, otherBox 相手のAABB
// @return 押し出し量
//-----------------------------------------------------------------
DirectX::SimpleMath::Vector3 PushOutComponent::CalculatePushOut(
    const DirectX::SimpleMath::Vector3& myPos, const DirectX::SimpleMath::Vector4& myBox,
    const DirectX::SimpleMath::Vector3& otherPos, const DirectX::SimpleMath::Vector4& otherBox
) {
    // 自分のAABB境界を計算
    DirectX::SimpleMath::Vector3 myMin = { myBox.y, myBox.x , 0.0f };    // 左下
	DirectX::SimpleMath::Vector3 myMax = { myBox.z, myBox.w , 0.0f };	// 右上

    // 相手のAABB境界を計算
    DirectX::SimpleMath::Vector3 otherMin = { otherBox.y, otherBox.x , 0.0f  };
    DirectX::SimpleMath::Vector3 otherMax = { otherBox.z, otherBox.w , 0.0f  };

    // 重なり量を計算
    float overlapX = min(myMax.x, otherMax.x) - max(myMin.x, otherMin.x);
    float overlapY = min(myMax.y, otherMax.y) - max(myMin.y, otherMin.y);

    // 最小の重なり量を押し出し方向として返す
    if (overlapX < overlapY) {return { overlapX * (myPos.x < otherPos.x ? -1.0f : 1.0f), 0.0f, 0.0f };
    }
    else {
        return { 0.0f, overlapY * (myPos.y < otherPos.y ? -1.0f : 1.0f), 0.0f };
    }
}
