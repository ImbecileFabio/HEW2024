//==================================================
// [RigidbodyComponent.h] �������Z�I�u�W�F�N�g
// ���ҁF���J����
//--------------------------------------------------
// �����F�������Z�������Ȃ��N���X
//==================================================

#pragma once
#include "../Component.h"
class RigidbodyComponent :
    public Component
{
public:
	void Init() {};
	void Uninit() {};
	void Update() {};
	void Draw() {};
	void SetVelocity(D3DXVECTOR3 velocity);					// ���x�̐ݒ�
	D3DXVECTOR3 GetVelocity();
	void SetGravity(float gravity);							// �d�͂̐ݒ�
	float GetGravity();
	void SetAngularVelocity(D3DXVECTOR3 angularVelocity);	// �p���x�̐ݒ�
	D3DXVECTOR3 GetAngularVelocity();
	void SetUseGravity(bool useGravity);					// �d�̗͂L��
	bool GetUseGravity();
	void SetIsKinematic(bool isKinematic);					// ���̃t���O�������Ă���ƕ������Z�������ɂȂ�
	bool GetIsKinematic();
	void SetFreezePosition(bool freezePosition);			// ���̃t���O�������Ă���ƈʒu�̕ύX�������ɂȂ�
	bool GetFreezePosition();
	void SetFreezeRotation(bool freezeRotation);			// ���̃t���O�������Ă���Ɖ�]�̕ύX�������ɂȂ�
	bool GetFreezeRotation();
	void SetCollisionDetection(bool collisionDetection);	// �Փˌ��o�̗L��
	bool GetCollisionDetection();
	void SetConstraints(bool constraints);					// ����̐ݒ�i���̃I�u�W�F�N�g�Ɋ����邩�ۂ��I�ȁj
	bool GetConstraints();
};

