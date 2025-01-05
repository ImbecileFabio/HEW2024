#include "LiftComponent.h"
#include "../GameObject/Pendulum.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
LiftComponent::LiftComponent(Pendulum* _pendulum, MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos, GameObject* _owner, int _updateOrder)
	:Component	(_owner, _updateOrder)
	, maxPos_	(_maxPos)	// �������̍ő���W
	, minPos_	(_minPos)	// �������̍ő���W
	, pendulum_	(_pendulum)	// ���t�g�̓����ƘA��������U��q�̎Q��
	, switchFg_	(false)		// �X�C�b�`�t���O
	, moveState_(_moveState)// �ړ����
{
	this->Init();
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
LiftComponent::~LiftComponent(void)
{
	this->Uninit();
}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void LiftComponent::Init()
{
}
//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void LiftComponent::Update()
{
}
//--------------------------------------------------
// �I������
//--------------------------------------------------
void LiftComponent::Uninit()
{
}
