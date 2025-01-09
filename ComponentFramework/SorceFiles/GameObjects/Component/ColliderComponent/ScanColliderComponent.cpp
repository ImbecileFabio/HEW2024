//==================================================
// [ScanColliderComponent.cpp] 
// 著者：有馬
//--------------------------------------------------
// 説明：
//==================================================

#include "../../../TileMapManager.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"
#include "ScanColliderComponent.h"
#include "CircleColliderComponent.h"
#include "BoxColliderComponent.h"

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
ScanColliderComponent::ScanColliderComponent(GameObject* _owner, int _updateOrder)
	: ColliderBaseComponent(_owner, _updateOrder)
{
	this->Init();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
ScanColliderComponent::~ScanColliderComponent()
{
	this->Uninit();
}
//--------------------------------------------------
// @brief 四角形の当たり判定の初期化処理
//--------------------------------------------------
void ScanColliderComponent::Init(void)
{
	SetSize(TILE_SIZE_X, TILE_SIZE_Y);
}
//--------------------------------------------------
// @brief 四角形の当たり判定の終了処理
//--------------------------------------------------
void ScanColliderComponent::Uninit(void)
{
}
//--------------------------------------------------
// @brief 四角形の当たり判定の更新処理
//--------------------------------------------------
void ScanColliderComponent::Update(void)
{
	auto pos = this->owner_->GetTransformComponent()->GetPosition();// 位置を取得
	this->SetWorldHitBox(pos);
}

bool ScanColliderComponent::CheckCollisionCollider(ColliderBaseComponent* _other)
{
	return  _other->CheckCollisionCollider(this);
}

//--------------------------------------------------
// @brief 四角形同士の当たり判定
//--------------------------------------------------
bool ScanColliderComponent::CheckCollisionCollider(BoxColliderComponent* _other)
{
	auto myHitbox = this->GetWorldHitBox();		// 自
	auto otherHitbox = _other->GetWorldHitBox();	// 他
	// x方向
	if (myHitbox.max_.x < otherHitbox.min_.x || myHitbox.min_.x > otherHitbox.max_.x) {
		this->hitFg_ = false;
		return false;
	}
	// y方向
	if (myHitbox.max_.y < otherHitbox.min_.y || myHitbox.min_.y > otherHitbox.max_.y) {
		this->hitFg_ = false;
		return false;
	}

	// x, yともに重なっている
	this->hitFg_ = true;
	return true;
}
//--------------------------------------------------
// @brief 四角形と円の当たり判定
//--------------------------------------------------
bool ScanColliderComponent::CheckCollisionCollider(CircleColliderComponent* _other)
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
// @param _position ownerの中心位置
// @brief 当たり判定の座標を決定
//--------------------------------------------------
void ScanColliderComponent::SetWorldHitBox(Vector3 _position)
{
	// オフセット適用
	_position += offset_;

	world_hit_box_ = AABB{
		Vector2(_position.x - size_.x / 2, _position.y - size_.y / 2),		// 左下
		Vector2(_position.x + size_.x / 2, _position.y + size_.y / 2)		// 右上
	};
}



