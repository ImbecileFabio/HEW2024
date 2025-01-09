//==================================================
// [ScanColliderComponent.h] 検知用の当たり判定
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ロボットに搭載するために作成
// 床や壁の情報をとるためのコライダー
// 
//==================================================
#ifndef SCAN_COLLIDER_COMPONENT_H_
#define SCAN_COLLIDER_COMPONENT_H_
/*----- インクルード -----*/
#include <memory>
#include <SimpleMath.h>
#include "ColliderBaseComponent.h"

using namespace DirectX::SimpleMath;


/*----- 前方宣言 -----*/
class TransformComponent;

//--------------------------------------------------
// 四角形の当たり判定
//--------------------------------------------------
class ScanColliderComponent :public ColliderBaseComponent
{
public:
	ScanColliderComponent(GameObject* _owner, int _updateOrder = 5);
	~ScanColliderComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;


	bool CheckCollisionCollider(ColliderBaseComponent* _other) override;
	bool CheckCollisionCollider(BoxColliderComponent* _other) override;
	bool CheckCollisionCollider(CircleColliderComponent* _other) override;


	TypeID GetComponentType(void) const override { return TypeID::ScanColliderComponent; }


	// AABBセッター
	void SetAABB(const AABB& _localHitbox) { local_hit_box_ = _localHitbox; }


	// 当たり判定の位置を決定したり
	void SetWorldHitBox(Vector3 _position);
	void SetWorldHitBox(const AABB& _worldHitbox) { world_hit_box_ = _worldHitbox; }
	auto GetWorldHitBox(void) const { return world_hit_box_; }


private:
	AABB local_hit_box_{};	// 当たり判定の矩形
	AABB world_hit_box_{};	// 当たり判定の矩形
};

#endif // SCAN_COLLIDER_COMPONENT_H_