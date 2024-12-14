//==================================================
// [PendulumMovementComponent.h] �U��q�^���R���|�[�l���g
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̉^���̒�`
// 
//		�����l�Ƃ��ĐU��q�̊p�x�A�p�����x�A�x�_�̍��W�A�x���̒�����ݒ肷��i�p���x�͐ݒ肵�Ȃ��j
// 
// 		PendulumInit(float, VECTOR3�^, float);	�U��q�̏����l�ݒ�i�p�����x�A�x�_�̍��W�A�x���̒����j
// 
//		SetPendulumAngle(float);				�U��q�̊p�x���Z�b�g�i�����l�p�j
//		GetPendulumAngle();					�U��q�̊p�x���擾
//		SetPemdulumVelocity(float);			�p���x���Z�b�g
//		GetPemdulumVelocity();				�p���x���擾
//		SetPendulumAcceleration(float);		�p�����x���Z�b�g
//		GetPendulumAcceleration();				�p�����x���擾
//		SetPemdulumFulcrum(VECTOR3�^);			�x�_�̍��W���Z�b�g
//		GetPemdulumFulcrum();					�x�_�̍��W���擾
//		SetPendulumLength(float);				�x���̒������Z�b�g
//		GetPendulumLength();					�x���̒������擾
// 
//	�x�_�̎擾���@�𑊒k����i�x�_�̃Z�b�^�[�H�j�����Őݒ肷��̂�����H
//	�U��q��Î~���瓮�����n�߂����̊p�����x��0���̎��ɃQ�b�^�[�Ŏ擾����
//==================================================

#include "../Component.h"
#include "../GameObject.h"
#include <iostream>
#include <SimpleMath.h>
#include <cmath>

#define PI 3.14f

class PendulumMovementComponent : public Component
{
private:
	DirectX::SimpleMath::Vector3 pemdulumPosition_;	// -�ʒu
	float isPendulumAngle_;							// -���݂̐U��q�̊p�x
	float wasPendulumAngle_;						// -���O�̐U��q�̊p�x
	float isPendulumVelocity_;						// -���݂̊p���x
	float wasPendulumVelocity_;						// -���O�̊p���x
	float pendulumAcceleration_;					// -�U��q�̊p�����x
	DirectX::SimpleMath::Vector3 fulcrumPosition_;	// -�x�_�̍��W
	float pendulumLength_;							// -�U��q�̒���
	float pendulumRadian_;							// -�U��q�̊p�x�i���W�A���j
	bool  turnPendulum_;							// -�U��q�̉����ŏ�����؂�ւ��邽�߂̃t���O�@true�F�E���獶�@false�F������E

	float InitAcceleration_;						// -�����̊p�����x
	DirectX::SimpleMath::Vector3 InitFulcrum_;		// -�����̎x�_�̍��W
	float InitLength_;								// -�����̐U��q�̒���

public:
	PendulumMovementComponent(GameObject* _owner, int _updateOrder = 50);
	~PendulumMovementComponent();

	void Init();
	void Uninit();
	void Update();

	void PendulumPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length);
	void PendulumAcceleration(float _angularAcceleration);

	void PendulumVelocity();				// �U��q�̊p�x�Ɋp���x��K�p
	void ConversionRadian(float _angle);	// �p�x�����W�A���ɕϊ�

	void PendulumInit(float _acceleration, DirectX::SimpleMath::Vector3 _fulcrum, float _length);	// �U��q�̏�����

	// �p�x
	void  SetPendulumAngle(float _pendulumAngle);
	float GetPendulumAngle();
	// �p���x
	void  SetPemdulumVelocity(float _angularVelocity);
	float GetPemdulumVelocity();
	// �p�����x
	void  SetPendulumAcceleration(float _pendulumAcceleration);
	float GetPendulumAcceleration();
	// �x�_�̍��W
	void  SetPemdulumFulcrum(DirectX::SimpleMath::Vector3 _fulcrumPosition);
	DirectX::SimpleMath::Vector3 GetPemdulumFulcrum();
	// �x���̒���
	void  SetPendulumLength(float _pendulumLength);
	float GetPendulumLength();

	virtual TypeID GetComponentType() const override { return TypeID::PendulumMovementComponent; }
};