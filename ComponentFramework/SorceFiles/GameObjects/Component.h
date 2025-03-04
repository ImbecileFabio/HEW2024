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
#include <string>
#include <SimpleMath.h>
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
		// �A�j���[�V����
		, AnimationComponent
		// �p������
		, TransformComponent
		// ���W�b�h�{�f�B
		, RigidBodyComponent
		, VelocityComponent
		, GravityComponent
		// �R���C�_�[
		, ColliderBaseComponent
		, BoxColliderComponent
		, CircleColliderComponent
		, ScanColliderComponent
		// �C�x���g
		, EventBaseComponent
		, ColliderEventComponent
		// ���{�b�g
		, RobotMoveComponent
		// �^�C���]�[��
		, TimeZoneComponent
		// �U��q�̓���
		, PendulumMovementComponent
		// �U��q�̖_�̓���
		, StickMoveComponent	// �U��q�̖_�̓���
		// �M�~�b�N
		, LiftComponent			// ���t�g�M�~�b�N
		, LiftInteractionComponent	// ���t�g�Ƃ̂����R���|�[�l���g
		, RailComponent			// ���t�g�̃��[��
		, PulleyComponent		// ���ԃM�~�b�N
		, WeakFloorComponent	// �Ƃ����M�~�b�N
		, SteePillarComponent	// �S���M�~�b�N
		, SteePillarFloorDown	// �S�������M�~�b�N
		, SteePillarFloorUp		// �S���㏸�M�~�b�N
		, SmokeComponent		// ���M�~�b�N
		, SmokeInteractionComponent	// ���M�~�b�N�Ƃ̂����
		// �f���^�^�C���֘A
		, TimerComponent
		// �J����
		, CameraComponent
		// �q�I�u�W�F�N�g
		, ChildrenComponent
		// �����o��
		, PushOutComponent

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

	void SetDeltaTime(float _deltaTime) { delta_time_ = _deltaTime; }	// �f���^�^�C���̐ݒ�
	auto GetDeltaTime(void) const { return delta_time_; }	// �f���^�^�C���̎擾

	// �R���|�[�l���g�̎p������̍X�V
	virtual void OnUpdateWorldTransform() {}; 

    auto GetOwner(void) { return owner_; }
	int GetUpdateOrder(void) const { return update_order_; }

	virtual TypeID GetComponentType() const = 0;

	// ���[�h, �Z�[�u
	virtual void LoadProperties(void);
	virtual void SaveProperties(void);

	std::string GetComponentName(void);
protected:
	float delta_time_{};			// �f���^�^�C��

	GameObject* owner_;				// �����i�R���|�[�l���g�j�̏��L��
	int update_order_{};			// �������g�̍X�V����

	std::unique_ptr<class AudioManager> audio_manager_;
};


#endif	// COMPONENT_H_