//==================================================
// [CircleColliderComponent.cpp] 円の当たり判定のCPPファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：円の当たり判定のコンポーネント
//==================================================
#include "CircleColliderComponent.h"
#include "BoxColliderComponent.h"
#include "../TransformComponent.h"
#include "../../GameObject.h"
#include <iostream>
//--------------------------------------------------
// @brief 円の当たり判定のコンストラクタ
//--------------------------------------------------
CircleColliderComponent::CircleColliderComponent(GameObject* _owner, int _updateOrder)
	: ColliderBaseComponent(_owner, _updateOrder)
{
}
//--------------------------------------------------
// @brief  円の当たり判定のデストラクタ
//--------------------------------------------------
CircleColliderComponent::~CircleColliderComponent()
{
}
//--------------------------------------------------
// @brief  円の当たり判定の初期化処理
//--------------------------------------------------
void CircleColliderComponent::Init(void)
{

}
//--------------------------------------------------
// @brief 円の当たり判定の更新処理
//--------------------------------------------------
void CircleColliderComponent::Update(void)
{
	auto transform = this->owner_->GetTransformComponent();
	if(transform)
	{
		this->circle_.position = transform->GetPosition();
		DirectX::SimpleMath::Vector3 size = transform->GetSize();
		this->circle_.radius = std::min<float>(size.x, size.y) / 2.0f;
	}
}
//--------------------------------------------------
// @brief ポリフォーリズムを使って、コンポーネントで渡す関数を判別してくれる偉大なコード
// @param _other 基底クラスのコンポーネント
// @return 当たっているかどうか
//--------------------------------------------------
bool CircleColliderComponent::CheckCollisionCollider(ColliderBaseComponent* _other)
{
	return  _other->CheckCollisionCollider(this);
}
//--------------------------------------------------
// @brief 円と円の当たり判定をとる関数
// @param _other 円の当たり判定コンポーネント
// @return 当たっているかどうか
//--------------------------------------------------
bool CircleColliderComponent::CheckCollisionCollider(CircleColliderComponent* _other)
{
	float dx = this->circle_.position.x - _other->GetCircleSize().position.x;
	float dy = this->circle_.position.y - _other->GetCircleSize().position.y;
	float distanceSquared = (dx * dx) + (dy * dy);
	float combinedRadius = this->circle_.radius + _other->GetCircleSize().radius;

	this->hitFg_ = distanceSquared <= (combinedRadius * combinedRadius);
	return this->hitFg_;
}
//--------------------------------------------------
// @brief 円と四角の当たり判定をとる関数
// @param _other 四角の当たり判定コンポーネント
// @return 当たっているかどうか
//--------------------------------------------------
bool CircleColliderComponent::CheckCollisionCollider(BoxColliderComponent* _other)
{
	auto otherHitBox = _other->GetWorldHitBox();
	// 四角形内で円の中心に最も近い点を計算
	float closestX =
		max(otherHitBox.min_.x, min(circle_.position.x, otherHitBox.max_.x));	// 左と右
	float closestY =
		max(otherHitBox.min_.y, min(circle_.position.y, otherHitBox.max_.y));	// 下と上
	// 最近点と円の中心の距離を計算
	float distanceX = circle_.position.x - closestX;
	float distanceY = circle_.position.y - closestY;
	// 判定
	if ((distanceX * distanceX) + (distanceY * distanceY) < (circle_.radius * circle_.radius))
	{
		this->hitFg_ = true;
		return true;
	}
	return false;
}
//--------------------------------------------------
// @brief 円の当たり判定の終了処理
//--------------------------------------------------
void CircleColliderComponent::Uninit(void)
{
}
//--------------------------------------------------
// @brief 円の当たり判定をとる関数
// @param _other 円の座標と半径
//--------------------------------------------------
//void CircleColliderComponent::CheckCollision(const CIRCLE& _other)
//{
//	//float a = this->circle_.position.x - _other.position.x;
//	//float b = this->circle_.position.y - _other.position.y;
//	//float c = (a * a) + (b * b);
//	//float sumRadius = this->circle_.radius + _other.radius;
//
//	//if (c <= sumRadius * sumRadius)
//	//{
//	//	std::cout << std::format("[CircleColliderComponent] -> CheckCollision\n");
//	//	this->testFg = true;
//	//	return;
//	//}
//	//float a = std::pow((this->circle_.position.x - _other.position.x ), 2.0f);
//	//float b = std::pow((this->circle_.position.y - _other.position.y ), 2.0f);
//	//float c = a + b;	
//	//float sumRadius = std::pow((this->circle_.radius + _other.radius) , 2.0f);
//	//if (c < sumRadius)
//	//{
//	//	std::cout << std::format("[CircleColliderComponent] -> CheckCollision\n");
//	//	this->testFg = true;
//	//	return;
//	//}
//}