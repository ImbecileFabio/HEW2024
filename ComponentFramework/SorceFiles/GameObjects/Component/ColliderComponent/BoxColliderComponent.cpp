//==================================================
// [BoxColliderComponent.cpp] 四角の当たり判定のCPPファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：四角の当たり判定のコンポーネント
//==================================================
#include "BoxColliderComponent.h"
#include "CircleColliderComponent.h"
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
	auto pos = this->owner_->GetTransformComponent()->GetPosition();// 位置を取得
	this->SetWorldHitBox(pos);
}

bool BoxColliderComponent::CheckCollisionCollider(ColliderBaseComponent* _other)
{
	return  _other->CheckCollisionCollider(this);
}
//--------------------------------------------------
// @brief 四角形と円の当たり判定
//--------------------------------------------------
bool BoxColliderComponent::CheckCollisionCollider(CircleColliderComponent* _other)
{
	auto myHitBox = this->GetWorldHitBox();			// 自
	auto circleSize = _other->GetCircleSize();	// 他
	// 四角形内で円の中心に最も近い点を計算
	float closestX =
		max(myHitBox.min_.x, min(circleSize.position.x, myHitBox.max_.x));	// 左と右
	float closestY =
		max(myHitBox.min_.y, min(circleSize.position.y, myHitBox.max_.y));	// 下と上
	// 最近点と円の中心の距離を計算
	float distanceX = circleSize.position.x - closestX;
	float distanceY = circleSize.position.y - closestY;
	// 判定
	if ((distanceX * distanceX) + (distanceY * distanceY) < (circleSize.radius * circleSize.radius))
	{
		this->hitFg_ = true;
		return true;
	}
	return false;
}

//--------------------------------------------------
// @brief 四角形同士の当たり判定
//--------------------------------------------------
bool BoxColliderComponent::CheckCollisionCollider(BoxColliderComponent* _other)
{
	auto myHitbox    = this->GetWorldHitBox();		// 自
	auto otherHitbox = _other->GetWorldHitBox();	// 他
	// x方向
	if ( myHitbox.max_.x < otherHitbox.min_.x || myHitbox.min_.x > otherHitbox.max_.x) {
		this->hitFg_ = false;
		return false;
	}
	// y方向
	if(myHitbox.max_.y < otherHitbox.min_.y || myHitbox.min_.y > myHitbox.max_.y){
		this->hitFg_ = false;
		return false;
	}

	// x, yともに重なっている
	this->hitFg_ = true;
	return true;
}

//--------------------------------------------------
// @param _position ownerの中心位置
// @brief 当たり判定の座標を決定
//--------------------------------------------------
void BoxColliderComponent::SetWorldHitBox(Vector3 _position)
{
	// オフセット適用
	_position += offset_;

	hit_box_ = AABB{
		Vector2(_position.x - size_.x / 2, _position.y - size_.y / 2),		// 左下
		Vector2(_position.x + size_.x / 2, _position.y + size_.y / 2)		// 右上
	};
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
