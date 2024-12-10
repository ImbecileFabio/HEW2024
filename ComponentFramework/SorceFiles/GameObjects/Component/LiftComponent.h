////==================================================
//// [LiftComponent.cpp] ���t�g�w�b�_
//// ���ҁF����仓�
////--------------------------------------------------
//// �����F���t�g�R���|�[�l���g
////==================================================
//#ifndef LIFT_COMPONENT_H_
//#define LIFT_COMPONENT_H_
///*----- �C���N���[�h -----*/
//#include "../Component.h"
//#include <SimpleMath.h>
///*----- �O���錾 -----*/
//class ColliderBaseComponent;
//class VelocityComponent;
///*----- enum class -----*/
//enum class MoveState
//{
//	length,	// �c�ړ�
//	side,	// ���ړ�
//};
////--------------------------------------------------
//// ���t�g�N���X
////--------------------------------------------------
//class LiftComponent : public Component
//{
//public:
//	LiftComponent(DirectX::SimpleMath::Vector2 _maxPos, DirectX::SimpleMath::Vector2 _minPos,
//		MoveState _moveState, GameObject* _owner, int _updateOrder = 50);
//	~LiftComponent();
//
//	void Init  (void) override;
//	void Uninit(void) override;
//	void Update(void) override;
//	
//	TypeID GetComponentType(void) const override { return TypeID::LiftComponent; }
//private:
//	// ���t�g���g���Q�Ɨp�̃R���|�[�l���g
//	ColliderBaseComponent* colliderComponent_  = {};
//	VelocityComponent*	   velocityComponent_ = {};
//
//	DirectX::SimpleMath::Vector2 maxPos_ = {};
//	DirectX::SimpleMath::Vector2 minPos_ = {};
//	float direction_ = 1.0f;	// �ړ����� �����P�A�����|�P
//	bool switchFg_ = false;		// �ړ������̐؂�ւ��t���O
//
//	MoveState state_ = MoveState::length;
//};
//#endif // _LIFT_COMPONENT_H_