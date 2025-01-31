//==================================================
// [GravityComponent.h] 重力コンポーネント
// 著者：有馬啓太
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
    GravityComponent(GameObject* _owner, int _updateOrder = 6);
    ~GravityComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

	// 足元に地面があるかどうかの確認
	bool CheckGroundCollision();

	void SetUseGravityFlg(bool _flg) { use_gravity_ = _flg; }	// 重力使用フラグセッター
	void SetIsRobot(bool _flg) { is_robot_ = _flg; }			// ロボットフラグセッター
	void SetGravity(float _gravity) { gravity_ = _gravity; }	// 重力セッター
	bool GetIsGround() const { return is_ground_; }

    TypeID GetComponentType(void) const override { return TypeID::GravityComponent; }
private:

	bool is_ground_;	// 地面に接地しているか
	bool is_robot_;		// ロボットかどうか
	bool use_gravity_;  // 重力の使用

	float gravity_;     // 重力
};
#endif // GRAVITY_COMPONENT_H_
