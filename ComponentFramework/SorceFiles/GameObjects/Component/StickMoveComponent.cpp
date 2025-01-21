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
	// �_�̒����̕ύX
	this->ChangeStickLength();

	// �x�_�̈ʒu
	auto startPos = owner_pendulum_->GetComponent<PendulumMovementComponent>()->GetPendulumFulcrum();
	// �I�_���v�Z
	auto endPos = owner_pendulum_->GetTransformComponent()->GetPosition();
	// �_�̉�]�p�x���v�Z
	float stickAngle = std::atan2(endPos.y - startPos.y,endPos.x - startPos.x) - DirectX::XM_PIDIV2;

	// �I�_�̌v�Z
	Vector3 stickPos = {
		(startPos.x + endPos.x) / 2.0f,
		(startPos.y + endPos.y) / 2.0f,
		0.0f
	};

	// �U��q�̈ʒu��ݒ�
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