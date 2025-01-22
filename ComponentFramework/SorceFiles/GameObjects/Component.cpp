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
	// �A�j���[�V����
	, "AnimationComponent"
	// �p������
	, "TransformComponent"
	// ���W�b�h�{�f�B
	, "RigidBodyComponent"
	, "VelocityComponent"
	, "GravityComponent"
	// �R���C�_�[
	, "ColliderBaseComponent"
	, "BoxColliderComponent"
	, "CircleColliderComponent"
	, "ScanColliderComponent"
	// �C�x���g
	, "EventBaseComponent"
	, "ColliderEventComponent"
	// ���{�b�g
	, "RobotMoveComponent"
	// �^�C���]�[��
	, "TimeZoneComponent"
	// �U��q
	, "PendulumMovementComponent"
	// �U��q�̖_�̓���
	, "StickMoveComponent"	// �U��q�̖_�̓���
	// �M�~�b�N
	, "LiftComponent"		// ���t�g�M�~�b�N
	, "PulleyComponent"		// ���ԃM�~�b�N
	, "WeakFloorComponent"	// �Ƃ����M�~�b�N
	, "SteePillarComponent"	// �S���M�~�b�N
	, "SmokeComponent"		// ���M�~�b�N
	// �f���^�^�C���֘A
	, "TimerComponent"
	// �J����
	, "CameraComponent"
	// �q�I�u�W�F�N�g�Ǘ�
	, "ChildrenComponent"
	// �����o��
	, "PushOutComponent"
};

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Component::Component(GameObject* _owner, int _updateOrder)
	: owner_(_owner)				// ���L��
	, update_order_(_updateOrder)	// �X�V��
{
	// updateOrder��0�ȏ�A100�ȉ��Őݒ�
	if (update_order_ < 0 || update_order_ > 100) { 
		std::cout << std::format("[Component]-> UpdateOrder ���͈͊O�Ŏw�肳��܂���\n");
		update_order_ = 0; 
	}
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

std::string Component::GetComponentName(void)
{
	std::string componentName = ComponentTypeNames[static_cast<int>(GetComponentType())];
	return componentName;
}
