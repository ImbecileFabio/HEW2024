//#include "LiftComponent.h"
//#include "../Component.h"
//#include "../GameObject.h"
//#include "../Component/RigidbodyComponent/VelocityComponent.h"
//#include "../Component/ColliderComponent/BoxColliderComponent.h"
////--------------------------------------------------
//// @brief �R���X�g���N�^
//// @param _maxPos ���t�g�̐܂�Ԃ��n�_�i�{�j���̏ꍇ��X�����A�c�̏ꍇ��Y�����ݒ肷��
//// @param _minPos ���t�g�̐܂�Ԃ��n�_�i�[�j
//// @param _moveState ���t�g���c�����Ɉړ����邩�̐ݒ�
////--------------------------------------------------
//LiftComponent::LiftComponent(DirectX::SimpleMath::Vector2 _maxPos, DirectX::SimpleMath::Vector2 _minPos, 
//	MoveState _moveState, GameObject* _owner, int _updateOrder) : Component(_owner, _updateOrder), maxPos_(_maxPos), minPos_(_minPos), state_(_moveState)
//{
//	this->Init();
//}
////--------------------------------------------------
//// @brief �f�X�g���N�^
////--------------------------------------------------
//LiftComponent::~LiftComponent()
//{
//
//}
////--------------------------------------------------
//// @brief ����������
////--------------------------------------------------
//void LiftComponent::Init(void)
//{
//	// ���t�g�����R���C�_�[���擾
//	colliderComponent_  = owner_->GetComponent<ColliderBaseComponent>();
//	velocityComponent_  = owner_->GetComponent<VelocityComponent>();
//}
////--------------------------------------------------
//// @brief �I������
////--------------------------------------------------
//void LiftComponent::Uninit(void)
//{
//	delete velocityComponent_;
//	delete colliderComponent_;
//}
////--------------------------------------------------
//// @brief �X�V����
////--------------------------------------------------
//void LiftComponent::Update(void)
//{
//	// ���t�g�̈ړ�����
//	switch (state_)
//	{
//	case MoveState::length:
//		// �c�ړ�
//		break;
//	case MoveState::side:
//		// ���ړ�
//		DirectX::SimpleMath::Vector3 pos = this->owner_->GetTransformComponent()->GetPosition();
//		if (pos.x < maxPos_.x && switchFg_ == false)
//		{
//			pos.x += 2.0f;
//			if (pos.x >= maxPos_.x)
//				switchFg_ = true;
//		}
//		if (pos.x > minPos_.x && switchFg_ == true)
//		{
//			pos.x -= 2.0f;
//			if (pos.x <= minPos_.x)
//				switchFg_ = false;
//		}
//		this->owner_->GetTransformComponent()->SetPosition(pos.x, pos.y, pos.z);
//		break;
//	}
//}
