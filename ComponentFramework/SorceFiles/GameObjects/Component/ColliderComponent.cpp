#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
BoxColliderComponent::BoxColliderComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
BoxColliderComponent::~BoxColliderComponent()
{
}
//--------------------------------------------------
// @brief 四角形の当たり判定の初期化処理
//--------------------------------------------------
void BoxColliderComponent::Init(void)
{
	// とりあえず想定通りの図形がでるかどうかのテスト
	// 生成したオブジェクトから座標を持ってくる
	position_ = owner_->GetComponent<TransformComponent>()->GetPosition();
	DirectX::SimpleMath::Vector3 size = owner_->GetComponent<TransformComponent>()->GetScale();

	boxSize_.w = position_.y + size.y / 2;	// 上
	boxSize_.x = position_.y - size.y / 2;	// 下
	boxSize_.y = position_.x - size.x / 2;	// 左
	boxSize_.z = position_.x + size.x / 2;	// 右
}
//--------------------------------------------------
// @brief 四角形の当たり判定の終了処理
//--------------------------------------------------
void BoxColliderComponent::Uninit(void)
{
}
//--------------------------------------------------
// @brief 四角形の当たり判定の更新処理
//--------------------------------------------------
void BoxColliderComponent::Update(void)
{
}
//--------------------------------------------------
// @brief 四角形の当たり判定が重なっているかどうかの処理
// @param _collider 当たり判定を行う相手
// @return 重なっているかどうか
//--------------------------------------------------
bool BoxColliderComponent::CheckCollision(const BoxColliderComponent* _collider) const
{
	DirectX::SimpleMath::Vector4 other = _collider->boxSize();	// 相手の当たり判定のサイズを取得
	if (boxSize_.w < other.x || boxSize_.x > other.w || boxSize_.y > other.z || boxSize_.z < other.y)
	{	// 重なったら
		return true;
	}
	return false;
}
