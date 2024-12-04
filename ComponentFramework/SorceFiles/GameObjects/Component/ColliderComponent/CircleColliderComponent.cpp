//==================================================
// [CircleColliderComponent.cpp] 円の当たり判定のCPPファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：円の当たり判定のコンポーネント
//==================================================
#include "CircleColliderComponent.h"
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
	DirectX::SimpleMath::Vector3 scale =
		this->owner_->GetComponent<TransformComponent>()->GetScale();
	this->circle_.radius = std::min<float>(scale.x, scale.y) / 2;
	this->circle_.position = 
		this->owner_->GetComponent<TransformComponent>()->GetPosition();
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
	float a = this->circle_.position.x - _other->GetCircleSize().position.x;
	float b = this->circle_.position.y - _other->GetCircleSize().position.y;
	float c = (a * a) + (b * b);
	float sumRadius = this->circle_.radius + _other->GetCircleSize().radius;

	if (c <= sumRadius * sumRadius)
	{
		return true;
	}
	return false;
}
//--------------------------------------------------
// @brief 円と四角の当たり判定をとる関数
// @param _other 四角の当たり判定コンポーネント
// @return 当たっているかどうか
//--------------------------------------------------
bool CircleColliderComponent::CheckCollisionCollider(BoxColliderComponent* _other)
{
	//// 右と左
		//if (boxSize_.z < _other.y)
		//{
		//	testFg = false; return false;
		//}
		//// 左と右
		//if (boxSize_.y > _other.z)
		//{
		//	testFg = false; return false;
		//}
		//// 下と上
		//if (boxSize_.x > _other.w)
		//{
		//	testFg = false; return false;
		//}
		//// 上と下
		//if (boxSize_.w < _other.x)
		//{
		//	testFg = false; return false;
		//}
		//return true;
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