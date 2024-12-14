//==================================================
// [BoxColliderComponent.cpp] 四角の当たり判定のCPPファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：四角の当たり判定のコンポーネント
//==================================================
#include "BoxColliderComponent.h"
#include "../TransformComponent.h"
#include "../../GameObject.h"

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
BoxColliderComponent::BoxColliderComponent(GameObject* _owner, int _updateOrder)
	: ColliderBaseComponent(_owner, _updateOrder)
{
	this->Init();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
BoxColliderComponent::~BoxColliderComponent()
{
	this->Uninit();
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
	DirectX::SimpleMath::Vector3 pos = this->owner_->GetComponent<TransformComponent>()->GetPosition();	// 位置を取得
	DirectX::SimpleMath::Vector3 size = this->owner_->GetComponent<TransformComponent>()->GetScale();	// サイズを取得
	this->boxSize_.w = pos.y + size.y / 2;	// 上	// 当たり判定を更新
	this->boxSize_.x = pos.y - size.y / 2;	// 下
	this->boxSize_.y = pos.x - size.x / 2;	// 左
	this->boxSize_.z = pos.x + size.x / 2;	// 右
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
		this->hitFg_ = false;  return false;
	}
	// 左と右
	if (boxSize_.y > _other->GetBoxSize().z)
	{
		this->hitFg_ = false; return false;
	}
	// 下と上
	if (boxSize_.x > _other->GetBoxSize().w)
	{
		this->hitFg_ = false; return false;
	}
	// 上と下
	if (boxSize_.w < _other->GetBoxSize().x)
	{
		this->hitFg_ = false; return false;
	}
	this->hitFg_ = true; return true;
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
