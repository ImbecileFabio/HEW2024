//==================================================
// [AngularVelocityComponent.h] �p���x���Z�R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�������Z�������Ȃ��N���X
//		�S�D�p���x�A��]
// 
//		Update();								�����̎��s
//	�E�p�����x
//		SetAngularAcceleration(VECTOR3�^);			�p�����x�̃Z�b�g
// 		GetAngularAcceleration() const;			�p�����x�̎擾
// 		SetUseAngularAcceleration(true�@or false);	�p�����x�̃t���O
// 		GetUseAngularAcceleration() const;			�p�����x�̃t���O�̎擾
//	�E�p���x
//		SetAngularVelocity(VECTOR3�^);				�p���x�̃Z�b�g
// 		GetAngularVelocity() const;				�p���x�̎擾
// 		SetUseAngularVelocity(true�@or false);		�p���x�̎g�p�t���O
// 		GetUseAngularVelocity() const;				�p���x�̎g�p�t���O�̎擾
//==================================================

#pragma once
#include "../RigidbodyComponent.h"
class AngularVelocityComponent :
    public RigidbodyComponent
{
private:
	float rotation_;
	float angularAcceleration_;		// -�p�����x
	bool use_angularAcceleration_;							// -�p�����x�̎g�p�t���O
	float angularVelocity_;			// -�p���x
	bool use_angularVelocity_;								// -�p���x�̎g�p�t���O
public:
	AngularVelocityComponent(GameObject* _owner, int _updateOrder = 50);
	~AngularVelocityComponent();

	void Init();
	void Uninit();
	void Update();

	// �p�����x
	void	SetAngularAcceleration(const float _angularAcceleration);
	float GetAngularAcceleration() const;
	void	SetUseAngularAcceleration(const bool _use_angularAcceleration);
	bool	GetUseAngularAcceleration() const;

	// �p���x
	void	SetAngularVelocity(const float _angularVelocity);
	float GetAngularVelocity() const;
	void	SetUseAngularVelocity(const bool _use_angularVelocity);
	bool	GetUseAngularVelocity() const;

	virtual TypeID GetComponentType() const override { return TypeID::AngularVelocityComponent; }
};

