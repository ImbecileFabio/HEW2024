//==================================================
// [VelocityComponent.h] 速度演算コンポーネント
// 著者：中谷凌也
//--------------------------------------------------
// 説明：速度演算をおこなうクラス
//		１．位置、速度
//		２．重力
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
	DirectX::SimpleMath::Vector3 gravity_;
	bool	use_gravity_;

public:
	VelocityComponent(GameObject* _owner, int _updateOrder = 50);
	~VelocityComponent();

	void Init();
	void Uninit();
	void Updata();		// すべての更新を行う

	// 加速度
	void	SetAcceleration(const DirectX::SimpleMath::Vector3 _acceleration);
	DirectX::SimpleMath::Vector3 GetAcceleration() const;
	void	SetUseAcceleration(const bool _use_acceleration);
	bool	GetUseAcceleration() const;

	// 速度
	void	SetVelocity(const DirectX::SimpleMath::Vector3 _velocity);
	//void	UpdateVelocity();
	DirectX::SimpleMath::Vector3	GetVelocity() const;
	void	SetUseVelocity(const bool _use_velocity);
	bool	GetUseVelocity() const;

	// 重力
	void	SetUseGravity(const bool _use_gravity);
	bool	GetUseGravity() const;
};