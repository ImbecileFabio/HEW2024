//==================================================
// [Component.cpp] �R���|�[�l���g�̃x�[�X
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�R���|�[�l���g�̑匳�̒�`
//==================================================

/*----- �C���N���[�h -----*/
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

	// �J����
	, "CameraComponent"

};

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Component::Component(std::shared_ptr<GameObject> _owner, int _updateOrder)
	: owner_(_owner)
	, update_order_(_updateOrder)
{
	owner_->AddComponent(this);
}

Component::~Component()
{
	GetOwner()->RemoveComponent(this);

}

//--------------------------------------------------
// �R���|�[�l���g�̎p������̍X�V
//--------------------------------------------------
void Component::OnUpdateWorldTransform()
{
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
