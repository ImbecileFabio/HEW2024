//==================================================
// [AngularVelocityComponent.h] �p���x���Z�R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�������Z�������Ȃ��N���X
//		�S�D�p���x�A��]
// 
//	�E�p�����x
//		SetAngularAcceleration(VECTOR3�^);			�p�����x�̃Z�b�g
// 		GetAngularAcceleration() const;			�p�����x�̎擾
// 		SetUseAngularAcceleration(true�@or false);	�p�����x�̃t���O
// 		GetUseAngularAcceleration() const;			�p�����x�̃t���O�̎擾
//	�E�p���x
//		SetAngularVelocity(VECTOR3�^);				���x�̃Z�b�g
// 		GetAngularVelocity() const;				���x�̎擾
// 		SetUseAngularVelocity(true�@or false);		���x�̎g�p�t���O
// 		GetUseAngularVelocity() const;				���x�̎g�p�t���O�̎擾
//==================================================

#pragma once
#include "../RigidbodyComponent.h"
class AngularVelocityComponent :
    public RigidbodyComponent
{
private:
	DirectX::SimpleMath::Vector3 rotation_;
	DirectX::SimpleMath::Vector3 angularAcceleration_;		// -�p�����x
	bool use_angularAcceleration_;							// -�p�����x�̎g�p�t���O
	DirectX::SimpleMath::Vector3 angularVelocity_;			// -�p���x
	bool use_angularVelocity_;								// -�p���x�̎g�p�t���O
public:
	AngularVelocityComponent(GameObject* _owner, int _updateOrder = 50);
	~AngularVelocityComponent();

	void Init();
	void Uninit();
	void Updata();

	// �p�����x
	void	SetAngularAcceleration(const DirectX::SimpleMath::Vector3 _angularAcceleration);
	DirectX::SimpleMath::Vector3 GetAngularAcceleration() const;
	void	SetUseAngularAcceleration(const bool _use_angularAcceleration);
	bool	GetUseAngularAcceleration() const;

	// �p���x
	void	SetAngularVelocity(const DirectX::SimpleMath::Vector3 _angularVelocity);
	DirectX::SimpleMath::Vector3 GetAngularVelocity() const;
	void	SetUseAngularVelocity(const bool _use_angularVelocity);
	bool	GetUseAngularVelocity() const;

};

