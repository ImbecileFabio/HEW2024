//==================================================
// [Component.cpp] �R���|�[�l���g�̃x�[�X
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�R���|�[�l���g�̑匳�̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include <cassert>

#include "Component.h"
#include "GameObject.h"

// �R���|�[�l���g�̃��X�g
const char* Component::ComponentTypeNames[static_cast<int>(TypeID::MAX)] =
{
	// �������g
	"Component"

	//�����ɒǉ������R���|�[�l���g��ǉ����Ă���
	// �����_�����O
	, "RenderComponent"
	, "SpriteComponent"
	
	// �p������
	, "TransformComponent"
	// ���W�b�h�{�f�B
	, "RigidBodyComponent"
	, "VelocityComponent"
	, "AngularVelocityComponent"
	// �R���C�_�[
	, "ColliderComponent"
	, "BoxColliderComponent"
	, "CircleColliderComponent"

	// �J����
	, "CameraComponent"
	// �U��q
	, "PendulumComponent"

};

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Component::Component(GameObject* _owner, int _updateOrder)
	: owner_(_owner)
	, update_order_(_updateOrder)
{
	// updateOrder��0�ȏ�A100�ȉ��Őݒ�
	assert(update_order_ <= 100 && update_order_ >= 0);
	owner_->AddComponent(this);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Component::~Component()
{
	owner_->RemoveComponent(this);
}


//--------------------------------------------------
// �R���|�[�l���g�̏�Ԃ̓ǂݍ���
//--------------------------------------------------
void Component::LoadProperties(void)
{
}

//--------------------------------------------------
// �R���|�[�l���g�̏�Ԃ̕ۑ�
//--------------------------------------------------
void Component::SaveProperties(void)
{
}
