//==================================================
// [StickMoveComponent.h] �U��q�̖_�̓����R���|�[�l���g
// ���ҁF����仓�
//--------------------------------------------------
// �����F���e�I�ɂ͐U��q�̓����R���|�[�l���g�ƈꏏ
//==================================================
#ifndef STICK_MOVE_COMPONENT_H_
#define STICK_MOVE_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../Component.h"
#include <SimpleMath.h>
/*----- �O���錾 -----*/
class TransformComponent;
//--------------------------------------------------
// �U��q�̖_�̓����R���|�[�l���g
//--------------------------------------------------
class StickMoveComponent : public Component
{
public:
	enum class LengthState
	{
		shortLength,
		normalLength,
		longLength
	};

    StickMoveComponent(GameObject* _owner, int _updateOrder = 50);
    ~StickMoveComponent();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::StickMoveComponent; }

	void SetPendulumTransform(TransformComponent* _pendulumTransform) { pendulum_transform_component_ = _pendulumTransform; }

    void StickInit(DirectX::SimpleMath::Vector3 _fulcrum, bool _movement, float _stickAngle);	// �U��q�̏�����
	void StickPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length);
	void StickAcceleration(float _angularAcceleration);

	void StickVelocity();					// �U��q�̊p�x�Ɋp���x��K�p
	void ConversionRadian(float _angle);	// �p�x�����W�A���ɕϊ�

	// �p�x
	void  SetStickAngle(float _stickAngle);
	float GetStickAngle();
	// �p���x
	void  SetStickVelocity(float _angularVelocity);
	float GetStickVelocity();
	// �p�����x
	void  SetStickAcceleration(float _stickAcceleration);
	float GetStickAcceleration();
	// �x�_�̍��W
	void  SetStickFulcrum(DirectX::SimpleMath::Vector3 _fulcrumPosition);
	DirectX::SimpleMath::Vector3 GetStickFulcrum();
	// �x���̒���
	void  SetStickLength(float _stickLength);
	float GetStickLength();

	// �U��q�̒�~�A�n��
	void StartStickMovement();
	void StopStickMovement();

	void SetStickMovement(bool _stickMovement) { stickMovement_ = _stickMovement; }
	bool GetStickMovement() { return stickMovement_; }
private:
	DirectX::SimpleMath::Vector3 stickPosition_;	// -�ʒu
	float isStickAngle_;							// -���݂̐U��q�̊p�x
	float wasStickAngle_;							// -���O�̐U��q�̊p�x
	float isStickVelocity_;							// -���݂̊p���x
	float wasStickVelocity_;						// -���O�̊p���x
	float stickAcceleration_;						// -�U��q�̊p�����x
	DirectX::SimpleMath::Vector3 fulcrumPosition_;	// -�x�_�̍��W
	float stickLength_;								// -�U��q�̒���
	float stickRadian_;								// -�U��q�̊p�x�i���W�A���j
	bool  turnStick_;								// -�U��q�̉����ŏ�����؂�ւ��邽�߂̃t���O�@true�F�E���獶�@false�F������E
	float maxStickAngle_;							// -�U��q�̍ő�p�x
	float maxStickVelocity_;						// -�U��q�̍ő呬�x

	// -�_�������Ă��邩�ǂ���
	bool stickMovement_;

	// -�U��q�̖_�̏��
	LengthState lengthState_;

	TransformComponent* pendulum_transform_component_;	// �U��q�̍��W���Q�Ƃ���R���|�[�l���g
};
#endif // HOGE_COMPONENT_H_
