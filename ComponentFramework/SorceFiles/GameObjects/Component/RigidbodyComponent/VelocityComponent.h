//==================================================
// [VelocityComponent.h] 速度演算コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：速度演算をおこなうクラス
//		１．位置、速度
//		２．重力
//		５．制約
// 
//		Update();							処理の実行
//	・加速度
//		SetAcceleration(VECTOR3型);			加速度のセット
//		GetAcceleration() const;				加速度の取得
//		SetUseAcceleration(true　or false);	加速度の使用フラグ
//		GetUseAcceleration() const;			加速度の使用フラグの取得
//	・速度
//		SetVelocity(VECTOR3型);				速度のセット
//		UpdateVelocity();	
//		GetVelocity() const;					速度の取得
//		SetUseVelocity(true　or false);		速度の使用フラグ
//		GetUseVelocity() const;				速度の使用フラグの取得
//==================================================

#pragma once
#include "../RigidbodyComponent.h"
class VelocityComponent :
    public RigidbodyComponent
{
private:
	DirectX::SimpleMath::Vector3 position_;
	DirectX::SimpleMath::Vector3 acceleration_;
	bool	use_acceleration_;
	DirectX::SimpleMath::Vector3 velocity_;
	bool	use_velocity_;

	float speed_rate_;	// 速度倍率
	bool is_change_speed_rate_flg_ = false;	// このフレームで速度倍率が変更されたかどうか

public:
	VelocityComponent(GameObject* _owner, int _updateOrder = 28);
	~VelocityComponent();

	void Init();
	void Uninit();
	void Update();		// すべての更新を行う
	// 速度係数
	void    SetSpeedRate   (const float _speed_rate);
	float   GetSpeedRate   (void);

	void SetChangeSpeedRateFlg(bool _flg) { is_change_speed_rate_flg_ = _flg; }
	auto GetChangeSpeedRateFlg(void) { return is_change_speed_rate_flg_; }


	// 加速度
	void	SetAcceleration(const DirectX::SimpleMath::Vector3 _acceleration);
	DirectX::SimpleMath::Vector3 GetAcceleration() const;
	void	SetUseAcceleration(const bool _use_acceleration);
	bool	GetUseAcceleration() const;

	// 速度
	void	SetVelocity(const DirectX::SimpleMath::Vector3 _velocity);
	void	AddVelocity(Vector3 _velocity) { velocity_ += _velocity; }	// 加速度追加
	//void	UpdateVelocity();
	DirectX::SimpleMath::Vector3	GetVelocity() const;
	void	SetUseVelocity(const bool _use_velocity);
	bool	GetUseVelocity() const;

	void ResetVelocity() { velocity_ = DirectX::SimpleMath::Vector3::Zero; }

	virtual TypeID GetComponentType() const override { return TypeID::VelocityComponent; }
};