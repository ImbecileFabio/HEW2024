//==================================================
// [BoxColliderComponent.h] 四角の当たり判定コンポーネントのヘッダファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：四角の当たり判定のコンポーネント
// 
// 24/12/21 arima AABB関連を追加してみた
//==================================================
#ifndef BOX_COLLIDER_COMPONENT_H_
#define BOX_COLLIDER_COMPONENT_H_
/*----- インクルード -----*/
#include <memory>
#include <SimpleMath.h>
#include "ColliderBaseComponent.h"

using namespace DirectX::SimpleMath;

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class TransformComponent;

//--------------------------------------------------
// 四角形の当たり判定
//--------------------------------------------------
class BoxColliderComponent :public ColliderBaseComponent
{
public:
	BoxColliderComponent(GameObject* _owner, int _updateOrder = 5);
	~BoxColliderComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;


	bool CheckCollisionCollider(ColliderBaseComponent* _other) override;
	bool CheckCollisionCollider(CircleColliderComponent* _other) override;
	bool CheckCollisionCollider(BoxColliderComponent* _other) override;

	TypeID GetComponentType(void) const override { return TypeID::BoxColliderComponent; }

	void SetAABB(const AABB& _hitbox) { hit_box_ = _hitbox; }

	// 当たり判定の位置を決定したり
	void SetWorldHitBox(Vector3 _position);
	void SetWorldHitBox(const AABB& _worldHitbox) { hit_box_ = _worldHitbox; }
	auto GetWorldHitBox(void) const { return hit_box_; }
	

private:
	
	AABB hit_box_{};	// 当たり判定の矩形
};

#endif // BOX_COLLIDER_COMPONENT_H_