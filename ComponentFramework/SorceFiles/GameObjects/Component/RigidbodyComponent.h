//==================================================
// [RigidbodyComponent.h] �������Z�I�u�W�F�N�g
// ���ҁF���J����
//--------------------------------------------------
// �����F�������Z�������Ȃ��N���X
//		�P�D�ʒu�A���x
//		�Q�D�d��
//		�R�D�Փˌ��o
//		�S�D�p���x�A��]
//		�T�D����
//		�U�D�i�f�o�b�O�j
//==================================================

#pragma once
#include "../Component.h"
#include <iostream>
#include <format>
#include <SimpleMath.h>

using namespace DirectX;

class RigidbodyComponent :
    public Component
{
private:
	Vector3 position_;
	Vector3 acceleration_;
	bool use_acceleration_ = true;	// �g�p�t���O��true�Ȃ��p����
	Vector3 velocity_;
	bool use_velocity_ = true;

	//DirectX::XMFLOAT3 m_velocity;			// -���x
	//float m_gravity;						// -�d��
	//DirectX::XMFLOAT3 m_angularVelocity;		// -�p���x
	//bool m_useGravity;						// -�d�̗͂L��
	//bool m_isKinematic;						// -���̃t���O�������Ă���ƕ������Z�������ɂȂ�
	//bool m_freezePosition;					// -���̃t���O�������Ă���ƈʒu�̕ύX�������ɂȂ�
	//bool m_freezeRotation;					// -���̃t���O�������Ă���Ɖ�]�̕ύX�������ɂȂ�
	//bool m_collisionDetection;				// -�Փˌ��o�̗L��
	//bool m_constraints;						// -����̐ݒ�i���̃I�u�W�F�N�g�Ɋ����邩�ۂ��I�ȁj
public:
	RigidbodyComponent(GameObject* _owner, int _updateOrder = 50);
	~RigidbodyComponent();

	void Init();
	void Uninit();
	void Updata();		// ���ׂĂ̍X�V���s��

	// �����x
	void	SetAcceleration(const Vector3 _acceleration);
	Vector3 GetAcceleration() const;
	void	SetUseAcceleration(const bool _use_acceleration);
	bool	GetUseAcceleration() const;

	// ���x
	void	SetVelocity(const Vector3 _velocity);
	void	UpdateVelocity();
	Vector3	GetVelocity() const;
	void	SetUseVelocity(const bool _use_velocity);
	bool	GetUseVelocity() const;
	

	//void Init() {};
	//void Uninit() {};
	//void Update() {};
	//void Draw() {};
	//void SetVelocity(const DirectX::XMFLOAT3 velocity);				// ���x�̐ݒ�
	//DirectX::XMFLOAT3 GetVelocity() const;
	//void SetGravity(float gravity);									// �d�͂̐ݒ�
	//float GetGravity();
	//void SetAngularVelocity(const DirectX::XMFLOAT3 angularVelocity);	// �p���x�̐ݒ�
	//DirectX::XMFLOAT3 GetAngularVelocity() const;
	//void SetUseGravity(bool useGravity);								// �d�̗͂L��
	//bool GetUseGravity();
	//void SetIsKinematic(bool isKinematic);							// ���̃t���O�������Ă���ƕ������Z�������ɂȂ�
	//bool GetIsKinematic();
	//void SetFreezePosition(bool freezePosition);						// ���̃t���O�������Ă���ƈʒu�̕ύX�������ɂȂ�
	//bool GetFreezePosition();
	//void SetFreezeRotation(bool freezeRotation);						// ���̃t���O�������Ă���Ɖ�]�̕ύX�������ɂȂ�
	//bool GetFreezeRotation();
	//void SetCollisionDetection(bool collisionDetection);				// �Փˌ��o�̗L��
	//bool GetCollisionDetection();
	//void SetConstraints(bool constraints);							// ����̐ݒ�i���̃I�u�W�F�N�g�Ɋ����邩�ۂ��I�ȁj
	//bool GetConstraints();
};

