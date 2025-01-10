//==================================================
// [GravityComponent.h] 重力コンポーネント
// 著者：
//--------------------------------------------------
// 説明：重力の処理をおこなう
//  それプラス、地面に接地しているかどうかの判定もとる
//==================================================
#ifndef GRAVITY_COMPONENT_H_
#define GRAVITY_COMPONENT_H_
/*----- インクルード -----*/
#include "../Component.h"

/*----- 前方宣言 -----*/
//--------------------------------------------------
// 重力コンポーネント
//--------------------------------------------------
class GravityComponent : public Component
{
public:
    GravityComponent(GameObject* _owner, int _updateOrder = 1);
    ~GravityComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::GravityComponent; }

	bool GetIsGround() const { return is_ground_; }

private:
	bool CheckGroundCollishion();

	// ownerのコンポーネントをキャッシュ
	class VelocityComponent* velocity_;
	class BoxColliderComponent* collider_;

	bool is_ground_; // 地面に接地しているか
	bool use_gravity_; // 重力の使用

	float gravity_;     // 重力
};
#endif // GRAVITY_COMPONENT_H_
