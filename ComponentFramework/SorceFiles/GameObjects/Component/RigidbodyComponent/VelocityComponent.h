//==================================================
// [VelocityComponent.h] ���x���Z�R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F���x���Z�������Ȃ��N���X
//		�P�D�ʒu�A���x
//		�Q�D�d��
//		�T�D����
// 
//		Update();							�����̎��s
//	�E�����x
//		SetAcceleration(VECTOR3�^);			�����x�̃Z�b�g
//		GetAcceleration() const;				�����x�̎擾
//		SetUseAcceleration(true�@or false);	�����x�̎g�p�t���O
//		GetUseAcceleration() const;			�����x�̎g�p�t���O�̎擾
//	�E���x
//		SetVelocity(VECTOR3�^);				���x�̃Z�b�g
//		UpdateVelocity();	
//		GetVelocity() const;					���x�̎擾
//		SetUseVelocity(true�@or false);		���x�̎g�p�t���O
//		GetUseVelocity() const;				���x�̎g�p�t���O�̎擾
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

	float speed_rate_;	// ���x�{��
	bool is_change_speed_rate_flg_ = false;	// ���̃t���[���ő��x�{�����ύX���ꂽ���ǂ���

public:
	VelocityComponent(GameObject* _owner, int _updateOrder = 28);
	~VelocityComponent();

	void Init();
	void Uninit();
	void Update();		// ���ׂĂ̍X�V���s��
	// ���x�W��
	void    SetSpeedRate   (const float _speed_rate);
	float   GetSpeedRate   (void);

	void SetChangeSpeedRateFlg(bool _flg) { is_change_speed_rate_flg_ = _flg; }
	auto GetChangeSpeedRateFlg(void) { return is_change_speed_rate_flg_; }


	// �����x
	void	SetAcceleration(const DirectX::SimpleMath::Vector3 _acceleration);
	DirectX::SimpleMath::Vector3 GetAcceleration() const;
	void	SetUseAcceleration(const bool _use_acceleration);
	bool	GetUseAcceleration() const;

	// ���x
	void	SetVelocity(const DirectX::SimpleMath::Vector3 _velocity);
	void	AddVelocity(Vector3 _velocity) { velocity_ += _velocity; }	// �����x�ǉ�
	//void	UpdateVelocity();
	DirectX::SimpleMath::Vector3	GetVelocity() const;
	void	SetUseVelocity(const bool _use_velocity);
	bool	GetUseVelocity() const;

	void ResetVelocity() { velocity_ = DirectX::SimpleMath::Vector3::Zero; }

	virtual TypeID GetComponentType() const override { return TypeID::VelocityComponent; }
};