#include "ColliderComponent.h"
#include "TransformComponent.h"
#include "../GameObject.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
BoxColliderComponent::BoxColliderComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	testFg = false;
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
	this->position_ = this->owner_->	// GameObjectの座標を取得
		GetTransformComponent()->GetPosition();
	DirectX::SimpleMath::Vector3 size = this->owner_->	// サイズを取得
		GetTransformComponent()->GetScale();
	this->boxSize_.w = position_.y + size.y / 2;	// 上	// 当たり判定を更新
	this->boxSize_.x = position_.y - size.y / 2;	// 下
	this->boxSize_.y = position_.x - size.x / 2;	// 左
	this->boxSize_.z = position_.x + size.x / 2;	// 右
}
//--------------------------------------------------
// @brief 四角形の当たり判定が重なっているかどうかの処理
// @param _other 当たり判定を行う相手
// @return 重なっているかどうか
//--------------------------------------------------
void BoxColliderComponent::CheckCollision(const DirectX::SimpleMath::Vector4& _other)
{	
	// 右と左
	if (boxSize_.z < _other.y)
	{
		testFg = false; return;
	}
	// 左と右
	if (boxSize_.y > _other.z)
	{
		testFg = false; return;
	}
	// 下と上
	if (boxSize_.x > _other.w)
	{
		testFg = false; return;
	}
	// 上と下
	if (boxSize_.w < _other.x)
	{
		testFg = false; return;
	}
	std::cout << std::format("[BoxColliderComponent] -> CheckCollision\n");
	testFg = true;
}
//--------------------------------------------------
// @brief 円のコンストラクタ
//--------------------------------------------------
CircleColliderComponent::CircleColliderComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
{
	testFg = false;
}
//--------------------------------------------------
// @brief 円のデストラクタ
//--------------------------------------------------
CircleColliderComponent::~CircleColliderComponent()
{
}
//--------------------------------------------------
// @brief 円の当たり判定の初期化処理
//--------------------------------------------------
void CircleColliderComponent::Init(void)
{
}
//--------------------------------------------------
// @brief 円の当たり判定の更新処理
//--------------------------------------------------
void CircleColliderComponent::Update(void)
{
	DirectX::SimpleMath::Vector3 scale = this->owner_->GetTransformComponent()->GetScale();
	//this->circle_.radius = std::min<float>(scale.x, scale.y) / 2;
	this->circle_.radius = 16.0f / 2.0f;
	this->circle_.position = this->owner_->GetTransformComponent()->GetPosition();
}
//--------------------------------------------------
// @brief 円の当たり判定の終了処理
//--------------------------------------------------
void CircleColliderComponent::Uninit(void)
{
}
//--------------------------------------------------
// @brief 円の当たり判定が重なっているかどうかの処理
// @param _other 当たり判定を行う相手
// @return 重なっているかどうか
//--------------------------------------------------
void CircleColliderComponent::CheckCollision(const CIRCLE& _other)
{
	float a = this->circle_.position.x - _other.position.x;
	float b = this->circle_.position.y - _other.position.y;
	float c = (a * a) + (b * b);	
	float sumRadius = this->circle_.radius + _other.radius;

	if (c <= sumRadius * sumRadius)
	{
		std::cout << std::format("[CircleColliderComponent] -> CheckCollision\n");
		this->testFg = true;
		return;
	}
	//float a = std::pow((this->circle_.position.x - _other.position.x ), 2.0f);
	//float b = std::pow((this->circle_.position.y - _other.position.y ), 2.0f);
	//float c = a + b;	
	//float sumRadius = std::pow((this->circle_.radius + _other.radius) , 2.0f);
	//if (c < sumRadius)
	//{
	//	std::cout << std::format("[CircleColliderComponent] -> CheckCollision\n");
	//	this->testFg = true;
	//	return;
	//}
}
