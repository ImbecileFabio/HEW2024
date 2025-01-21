//==================================================
// [StickMoveComponent.cpp] �U��q�̖_�̓����R���|�[�l���g
// ���ҁFHOGE���Y
//--------------------------------------------------
// �����F�U��q�̖_�̓����R���|�[�l���g�̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include "StickMoveComponent.h"
#include "../../TileMapManager.h"

#include "../GameObject.h"
#include "../GameObject/Pendulum.h"

#include "../Component/TransformComponent.h"
#include "../Component/PendulumMovementComponent.h"

#define PI 3.14f


//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
StickMoveComponent::StickMoveComponent(GameObject* _owner, Pendulum* _pendulum, int _updateOrder)
	:Component(_owner, _updateOrder)
	, owner_pendulum_(_pendulum)
	, length_state_(LengthState::Middle)
	, stick_length_{}
{
	std::cout << std::format("��StickMoveComponent�� -> Constructor\n");

	owner_transform_ = owner_->GetTransformComponent();
	pendulum_transform_ = owner_pendulum_->GetTransformComponent();
	this->Init();
}

//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
StickMoveComponent::~StickMoveComponent()
{
	std::cout << std::format("��StickMoveComponent�� -> Destructor\n");
	this->Uninit();
}

//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void StickMoveComponent::Init()
{

}

//--------------------------------------------------
// @brief �I������
//--------------------------------------------------
void StickMoveComponent::Uninit()
{
}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void StickMoveComponent::Update()
{
	// �x�_�̈ʒu
	auto startPos = owner_pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumFulcrum();
	// �U��q�̊p�x
	float stickAngle = owner_pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumAngle();
	// �I�_���v�Z
	auto endPos = CalculateEndPoint(startPos, stick_length_, stickAngle);

	// �I�_�̌v�Z
	Vector3 stickPos = {
		(startPos.x + endPos.x) / 2.0f,
		(startPos.y + endPos.y) / 2.0f,
		(startPos.z + endPos.z) / 2.0f
	};

	owner_transform_->SetPosition(stickPos);
	owner_transform_->SetRotation(stickAngle);
	owner_transform_->SetSize(TILE_SIZE_X, stick_length_);
}

void StickMoveComponent::ChangeStickLength()
{
	switch (length_state_)
	{
	case LengthState::Short:
		stick_length_ = normalLangth - langthChange;
		break;
	case LengthState::Middle:
		stick_length_ = normalLangth;
		break;
	case LengthState::Long:
		stick_length_ = normalLangth + langthChange;
		break;
	}
}


//--------------------------------------------------
// @param _sPos�F �x�_, _length�F �_�̒���, _angle�F �_�̊p�x
// @brief �`�悷�钆�S�ʒu���v�Z����
// @return Vector3: �v�Z���ꂽ���W
//--------------------------------------------------
Vector3 StickMoveComponent::CalculateEndPoint(Vector3& _sPos, float _length, float _angle)
{
	return {
		_sPos.x + _length * std::cos(_angle),
		_sPos.y + _length * std::sin(_angle),
		_sPos.z
	};
}





























//constexpr float normalLangth = TILE_SIZE_Y * 4;
//constexpr float langthChange = TILE_SIZE_Y;
//constexpr float pendulumAcceleration = 0.1f;
////--------------------------------------------------
//// @brief �R���X�g���N�^
////--------------------------------------------------
//StickMoveComponent::StickMoveComponent(GameObject* _owner, int _updateOrder)
//	:Component(_owner, _updateOrder)
//	, stickPosition_{}
//	, isStickAngle_{ 0 }
//	, wasStickAngle_{ 0 }
//	, isStickVelocity_{ 0 }
//	, wasStickVelocity_{ 0 }
//	, stickAcceleration_{ 0 }
//	, fulcrumPosition_{}
//	, stickLength_{ 0 }
//	, stickRadian_{ 0 }
//	, turnStick_{ true }
//	, maxStickAngle_{ 0 }
//	, maxStickVelocity_{ 0 }
//	, stickMovement_{ false }
//	, pendulum_transform_component_{}
//{
//	std::cout << std::format("��StickMoveComponent�� -> Constructor\n");
//	this->Init();
//}
//
//
////--------------------------------------------------
//// @brief �f�X�g���N�^
////--------------------------------------------------
//StickMoveComponent::~StickMoveComponent()
//{
//	std::cout << std::format("��StickMoveComponent�� -> Destructor\n");
//	this->Uninit();
//}
//
////--------------------------------------------------
//// @brief ����������
////--------------------------------------------------
//void StickMoveComponent::Init()
//{
//}
////--------------------------------------------------
//// @brief �I������
////--------------------------------------------------
//void StickMoveComponent::Uninit()
//{
//
//}
////--------------------------------------------------
//// @brief �X�V����
////--------------------------------------------------
//void StickMoveComponent::Update()
//{
//	// �U��q�̏�ԑJ��
//	switch (lengthState_)
//	{
//	case LengthState::Short:
//		SetStickLength(normalLangth - langthChange);
//		break;
//	case LengthState::Middle:
//		SetStickLength(normalLangth);
//		break;
//	case LengthState::Long:
//		SetStickLength(normalLangth + langthChange);
//		break;
//	default:
//		break;
//	}
//	if (stickMovement_ && GetStickAngle() == 0)
//	{
//		StartStickMovement();
//		StickVelocity();
//	}
//
//	StickAcceleration(stickAcceleration_);			// �p�����x��ݒ�, �p���x��K�p
//	StickPosition(fulcrumPosition_, stickLength_);	// ���W���v�Z
//}
////--------------------------------------------------
//// @brief �U��q�̖_�̏����ݒ�
////--------------------------------------------------
//void StickMoveComponent::StickInit(DirectX::SimpleMath::Vector3 _fulcrum, bool _movement, float _stickAngle)
//{
//	fulcrumPosition_ = _fulcrum;
//	stickMovement_ = _movement;
//	maxStickAngle_ = _stickAngle;
//	SetStickAngle(0.0f);
//}
////--------------------------------------------------
//// �U��q�̍��W���v�Z
////--------------------------------------------------
//void StickMoveComponent::StickPosition(DirectX::SimpleMath::Vector3 _fulcrum, float _length)
//{
//	//if (isStickAngle_ > 0) {		// -�p�x�����̏ꍇ
//	//	stickPosition_.x = _fulcrum.x + _length * cos(stickRadian_);
//	//	stickPosition_.y = _fulcrum.y - _length * sin(stickRadian_);
//	//}
//	//else if (isStickAngle_ < 0) {	// -�p�x�����̏ꍇ
//	//	stickPosition_.x = _fulcrum.x + _length * cos(stickRadian_);
//	//	stickPosition_.y = _fulcrum.y - _length * sin(stickRadian_);
//	//}
//	//else {					// -�p�x��0�̏ꍇ
//	//	stickPosition_.x = _fulcrum.x;
//	//	stickPosition_.y = _fulcrum.y - _length;
//	//}
//
//	// �U��q�̊p�x�̌v�Z���C�����Ă݂܂��� by arima
//	// ��肪�Ȃ���Ώ�̃R�[�h�������Ƃ��Ă��������B
//	// �p�x��0�x�t�߂̎��Ɂu�K�N�b�v���Ƃ��銴�G������̂ŗv�C�������B
//
//	ConversionRadian(isStickAngle_);
//
//	stickPosition_.x = _fulcrum.x + _length * cos(stickRadian_);
//	stickPosition_.y = _fulcrum.y - _length * sin(stickRadian_);
//
//	auto pendulumPos = pendulum_transform_component_->GetPosition();
//	float deltaX = pendulumPos.x - fulcrumPosition_.x;
//	float deltaY = pendulumPos.y - fulcrumPosition_.y;
//
//	float angle = atan2(deltaX, deltaY);
//
//	this->owner_->GetTransformComponent()->SetPosition({ stickPosition_.x, stickPosition_.y , 0.0f});
//	this->owner_->GetTransformComponent()->SetRotation(-angle);
//}
//
////--------------------------------------------------
//// �U��q�̊p�x�̐��ڂ��v�Z
////--------------------------------------------------
//void StickMoveComponent::StickAcceleration(float _angularAcceleration) 
//{
//	if (turnStick_) 
//	{
//		if (isStickAngle_ > 0) {
//			SetStickAcceleration(-_angularAcceleration);
//			StickVelocity();			// -�p���x��K�p 
//			if (isStickAngle_ <= 0) {	// -�p�x��0���ׂ��ł��܂�����
//				SetStickAngle(-wasStickAngle_);
//				if (!stickMovement_) { StopStickMovement(); }
//			}
//		}
//		else if (isStickAngle_ < 0) {
//			SetStickAcceleration(_angularAcceleration);
//			StickVelocity();			// -�p���x��K�p 
//			// �ō����B�_�Ɏ������甽�]
//			if (GetStickVelocity() >= 0) {
//				turnStick_ = false;
//			}
//		}
//	}
//	else {
//		if (isStickAngle_ < 0) {
//			SetStickAcceleration(_angularAcceleration);
//			StickVelocity();			// -�p���x��K�p 
//			if (isStickAngle_ >= 0) {	// -�p�x��0���ׂ��ł��܂�����
//				SetStickAngle(-wasStickAngle_);
//				if (!stickMovement_) { StopStickMovement(); }
//			}
//		}
//		else if (isStickAngle_ > 0) {
//			SetStickAcceleration(-_angularAcceleration);
//			StickVelocity();			// -�p���x��K�p 
//			// �ō����B�_�Ɏ������甽�]
//			if (GetStickVelocity() <= 0) {
//				turnStick_ = true;
//			}
//		}
//	}
//}
//
////--------------------------------------------------
//// �U��q�̊p�x�Ɋp���x��K�p
////--------------------------------------------------
//void StickMoveComponent::StickVelocity()
//{
//	SetStickVelocity(std::round((GetStickVelocity() + GetStickAcceleration()) * 1000) / 1000);
//	SetStickAngle(std::round((GetStickAngle() + GetStickVelocity()) * 1000) / 1000);
//}
////--------------------------------------------------
//// �p�x�����W�A���ɕϊ�
////--------------------------------------------------
//void StickMoveComponent::ConversionRadian(float _angle)
//{
//	stickRadian_ = (90 - _angle) * (PI / 180.0f);
//}
////--------------------------------------------------
//// �U��q�̊p�x�̃Z�b�^�[�Q�b�^�[
////--------------------------------------------------
//void StickMoveComponent::SetStickAngle(float _stickAngle) 
//{
//	wasStickAngle_ = isStickAngle_;
//	isStickAngle_ = _stickAngle;
//}
//float StickMoveComponent::GetStickAngle()
//{
//	return isStickAngle_;
//}
////--------------------------------------------------
//// �U��q�̊p���x�̃Z�b�^�[�Q�b�^�[
////--------------------------------------------------
//void StickMoveComponent::SetStickVelocity(float _angularVelocity)
//{
//	wasStickVelocity_ = isStickVelocity_;
//	isStickVelocity_ = _angularVelocity;
//}
//float StickMoveComponent::GetStickVelocity()
//{
//	return isStickVelocity_;
//}
//
////--------------------------------------------------
//// �U��q�̊p�����x�̃Z�b�^�[�Q�b�^�[
////--------------------------------------------------
//void StickMoveComponent::SetStickAcceleration(float _stickAcceleration) 
//{
//	stickAcceleration_ = _stickAcceleration;
//}
//float StickMoveComponent::GetStickAcceleration() {
//	return stickAcceleration_;
//}
//
////--------------------------------------------------
//// �x�_�̍��W�̃Z�b�^�[�Q�b�^�[
////--------------------------------------------------
//void StickMoveComponent::SetStickFulcrum(DirectX::SimpleMath::Vector3 _fulcrumPosition)
//{
//	fulcrumPosition_ = _fulcrumPosition;
//}
//DirectX::SimpleMath::Vector3 StickMoveComponent::GetStickFulcrum() 
//{
//	return fulcrumPosition_;
//}
//
////--------------------------------------------------
//// �x���̒����̃Z�b�^�[�Q�b�^�[
////--------------------------------------------------
//void StickMoveComponent::SetStickLength(float _stickLength) 
//{
//	stickLength_ = _stickLength;
//}
//float StickMoveComponent::GetStickLength() 
//{
//	return stickLength_;
//}
//
////--------------------------------------------------
//// �U��q�̒�~�A�n��
////--------------------------------------------------
//void StickMoveComponent::StartStickMovement() 
//{
//	maxStickVelocity_ = 0;
//	for (int i = 1;; i++) {
//		maxStickVelocity_ += stickAcceleration_ * i;
//		if (maxStickVelocity_ >= maxStickAngle_) {
//			SetStickVelocity(stickAcceleration_ * i);
//			break;
//		}
//	}
//}
//void StickMoveComponent::StopStickMovement() 
//{
//	SetStickAngle(0);
//	SetStickVelocity(0);
//	SetStickAcceleration(0);
//}