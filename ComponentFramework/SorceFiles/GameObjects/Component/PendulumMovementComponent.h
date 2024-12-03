//==================================================
// [PendulumMovementComponent.h] �U��q�^���R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̉^���̒�`
//
//		PendulumPosition(VECTOR3�^, float);	�U��q�̎x�_�̍��W�ƐU��q�̒��S����̒������Z�b�g�E�E�E�U��q�̈ʒu�Ɗp�x���v�Z
//		PendulumAngle(float);					�p�����x����́E�E�E�U��q�̉���������
// 
// �\��F�U��q�^���i�U��q�̎x�_, �p�x, �U��q�^���̒��S����̒����j�E�E�E�U��q�̈ʒu���v�Z
// �@�@�@�p�x�i�ő�p�x, �p�����x�j�E�E�E�U��q�̊p�x���v�Z�i�p���x�Ƃ����Ȃ�₩��₷��j
// 
// �x�_�̎擾���@�𑊒k����i�x�_�̃Z�b�^�[�H�j�����Őݒ肷��̂�����H
// �U��q��Î~���瓮�����n�߂����̊p�����x��0���̎��ɃQ�b�^�[�Ŏ擾����
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
	float angle_;									// -�U��q�̊p�x
	//float length_;									// -�U��q�̒��S����̒���
	float pendulumRadian_;							// -�U��q�̊p�x�i���W�A���j

public:
	PendulumMovementComponent(GameObject* _owner, int _updateOrder = 50);
	~PendulumMovementComponent();

	void Init();
	void Uninit();
	void Update();

	void PendulumPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length);
	void PendulumAngle(float _angularAcceleration);

	void ConversionRadian(float _angle);	// �p�x�����W�A���ɕϊ�

	//virtual TypeID GetComponentType() const override { return TypeID::PendulumMovementComponent; }
};