//==================================================
// [ColliderBaseComponent.h] 当たり判定の基底クラスコンポーネントのヘッダファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：当たり判定のベースコンポーネント
// オブジェクトにColliderBaseComponentを追加して、
// インスタンス生成するときはBox||CircleComponentを使ってください
//==================================================
#ifndef COLLIDER_BASE_COMPONENT_H_
#define COLLIDER_BASE_COMPONENT_H_
/*----- インクルード -----*/
#include <memory>
#include <SimpleMath.h>
#include "../../Component.h"

using namespace DirectX::SimpleMath;
/*----- 構造体宣言 -----*/
struct AABB {
	Vector2 min_;		// 矩形の左下
	Vector2 max_;		// 矩形の右上
};

/*----- 前方宣言 -----*/
class CircleColliderComponent;
class BoxColliderComponent;
//--------------------------------------------------
// 当たり判定ベースクラス
//--------------------------------------------------
class ColliderBaseComponent :public Component
{
public:
	ColliderBaseComponent(GameObject* _owner, int _updateOrder = 50);
	virtual ~ColliderBaseComponent();

	void Init(void) override {};
	void Uninit(void) override {};
	void Update(void) override {};

	virtual bool CheckCollisionCollider(ColliderBaseComponent* _other) = 0;
	virtual bool CheckCollisionCollider(CircleColliderComponent* _other)= 0;
	virtual bool CheckCollisionCollider(BoxColliderComponent* _other) = 0;

	bool GetHitFg(void) { return hitFg_; }
	void SetHitFg(bool _hitFg) { hitFg_ = _hitFg; }
	// ほぼ矩形用
	void SetSize(const float& _x, const float& _y) { SetSize(Vector3(_x, _y, 1.0f)); }
	void SetSize(const Vector3& _size) { size_ = _size; }
	auto GetSize(void) { return size_; }

	void SetOffset(const float _x, const float _y) { SetOffset(Vector3(_x, _y, 0.0f)); }
	void SetOffset(const Vector3 _offset) { offset_ = _offset; }
	auto GetOffset(void) { return offset_; }

	TypeID GetComponentType(void) const override { return TypeID::ColliderBaseComponent; }
protected:
	bool hitFg_ = false;	// 当たっているかどうか
	Vector3 size_{ 100.0f, 100.0f, 0.0f };		// サイズ
	Vector3 offset_{0.0f, 0.0f, 0.0f};		// オフセット
};
#endif // COLLIDER_BASE_COMPONENT_H_