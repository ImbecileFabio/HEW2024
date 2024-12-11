//==================================================
// [Component.h] �R���|�[�l���g�x�[�X�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�R���|�[�l���g�̑匳
//==================================================
#ifndef COMPONENT_H_
#define COMPONENT_H_

/*----- �C���N���[�h -----*/
#include <memory>

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameObject;

//--------------------------------------------------
// �R���|�[�l���g�N���X
//--------------------------------------------------
class Component 
{
public:
	enum class TypeID
	{
		None = -1
		// �x�[�X�N���X
		, Component

		// �����ɒǉ������R���|�[�l���g�������Ă���
		// �����_�����O
		, RenderComponent
		, SpriteComponent

		// �p������
		, TransformComponent
		// ���W�b�h�{�f�B
		, RigidBodyComponent
		, VelocityComponent
		, AngularVelocityComponent
		// �R���C�_�[
		, ColliderBaseComponent
		, BoxColliderComponent
		, CircleColliderComponent
		// �C�x���g
		, EventBaseComponent
		, ColliderEventComponent
		// �^�C���]�[��
		, TimeZoneComponent
		// �U��q�̓���
		, PendulumMovementComponent
		// ���t�g
		, LiftComponent
		// �J����
		, CameraComponent
		// �U��q
		, PendulumComponent
		// ����m�F�p
		, EventDebugComponent
		// �R���|�[�l���g�̍ő�l
		, MAX
	};

	static const char* ComponentTypeNames[static_cast<int>(TypeID::MAX)];

public:
	// updateOrder��0�ȏ�A100�ȉ��Őݒ�
	Component(GameObject* _owner, int updateOrder = 50);
	virtual ~Component();

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;

	// �R���|�[�l���g�̎p������̍X�V
	virtual void OnUpdateWorldTransform() {}; 

    auto GetOwner(void) { return owner_; }
	int GetUpdateOrder(void) const { return update_order_; }

	virtual TypeID GetComponentType() const = 0;

	// ���[�h, �Z�[�u
	virtual void LoadProperties(void);
	virtual void SaveProperties(void);


protected:
	GameObject* owner_;	// �����i�R���|�[�l���g�j�̏��L��
	int update_order_{};			// �������g�̍X�V����
};


#endif	// COMPONENT_H_