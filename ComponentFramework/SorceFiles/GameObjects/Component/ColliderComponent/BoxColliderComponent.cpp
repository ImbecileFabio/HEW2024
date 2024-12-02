#include "BoxColliderComponent.h"
#include "../TransformComponent.h"
#include "../../GameObject.h"

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
BoxColliderComponent::BoxColliderComponent(GameObject* _owner, int _updateOrder)
	: ColliderBaseComponent(_owner, _updateOrder)
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
	this->position_ = this->owner_->GetComponent<TransformComponent>()->GetPosition();	// 位置を取得
	DirectX::SimpleMath::Vector3 size = this->owner_->GetComponent<TransformComponent>()->GetScale();	// サイズを取得
	this->boxSize_.w = position_.y + size.y / 2;	// 上	// 当たり判定を更新
	this->boxSize_.x = position_.y - size.y / 2;	// 下
	this->boxSize_.y = position_.x - size.x / 2;	// 左
	this->boxSize_.z = position_.x + size.x / 2;	// 右
}
bool BoxColliderComponent::CheckCollisionCollider(ColliderBaseComponent* _other)
{
	return  _other->CheckCollisionCollider(this);
}
bool BoxColliderComponent::CheckCollisionCollider(CircleColliderComponent* _other)
{
	return false;
}
bool BoxColliderComponent::CheckCollisionCollider(BoxColliderComponent* _other)
{
	// 右と左
	if (boxSize_.z < _other->GetBoxSize().y)
	{
		return false;
	}
	// 左と右
	if (boxSize_.y > _other->GetBoxSize().z)
	{
		return false;
	}
	// 下と上
	if (boxSize_.x > _other->GetBoxSize().w)
	{
		return false;
	}
	// 上と下
	if (boxSize_.w < _other->GetBoxSize().x)
	{
		return false;
	}
	return true;
}
//--------------------------------------------------
// @brief 四角形の当たり判定が重なっているかどうかの処理
// @param _other 当たり判定を行う相手
// @return 重なっているかどうか
//--------------------------------------------------
//void BoxColliderComponent::CheckCollision(const DirectX::SimpleMath::Vector4& _other)
//{
//	// 右と左
//	if (boxSize_.z < _other.y)
//	{
//		testFg = false; return;
//	}
//	// 左と右
//	if (boxSize_.y > _other.z)
//	{
//		testFg = false; return;
//	}
//	// 下と上
//	if (boxSize_.x > _other.w)
//	{
//		testFg = false; return;
//	}
//	// 上と下
//	if (boxSize_.w < _other.x)
//	{
//		testFg = false; return;
//	}
//	testFg = true;
//}
