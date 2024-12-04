//==================================================
// [PendulumMovementComponent.h] �U��q�^���R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̉^���̒�`
//
//		Update(float, VECTOR�^, float);	(�p�����x, �x�_�̍��W, �U��q�̒���)
//		SetPendulumAngle(float);			�U��q�̊p�x���Z�b�g�i�����l�p�j
//		GetPendulumAngle();				�U��q�̊p�x���擾
// 
// 
//	��AngularVelocityComponent����GameObject�ɒǉ�����
// 
//	�x�_�̎擾���@�𑊒k����i�x�_�̃Z�b�^�[�H�j�����Őݒ肷��̂�����H
//	�U��q��Î~���瓮�����n�߂����̊p�����x��0���̎��ɃQ�b�^�[�Ŏ擾����
//==================================================

#include "../Component.h"
#include "../GameObject.h"
#include "RigidbodyComponent/AngularVelocityComponent.h"
#include <iostream>
#include <SimpleMath.h>
#include <cmath>

#define PI 3.14f

class PendulumMovementComponent : public Component
{
private:
	DirectX::SimpleMath::Vector3 pemdulumPosition_;	// -�ʒu
	float pendulumAngle_;							// -�U��q�̊p�x
	float pendulumRadian_;							// -�U��q�̊p�x�i���W�A���j

public:
	PendulumMovementComponent(GameObject* _owner, int _updateOrder = 50);
	~PendulumMovementComponent();

	void Init();
	void Uninit();
	// Update(float, VECTOR�^, float);	(�p�����x, �x�_�̍��W, �U��q�̒���)
	void Update() {};
	void Update(float _angle, DirectX::SimpleMath::Vector3 _fulcrum, float _length);

	void PendulumPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length);
	void PendulumAcceleration(float _angularAcceleration);

	void PendulumVelocity();				// �U��q�̊p�x�Ɋp���x��K�p
	void ConversionRadian(float _angle);	// �p�x�����W�A���ɕϊ�

	void  SetPendulumAngle(float _pendulumAngle);
	float GetPendulumAngle();

	virtual TypeID GetComponentType() const override { return TypeID::PendulumMovementComponent; }
};