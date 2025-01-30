//==================================================
// [Pendulum.cpp] �U��q�I�u�W�F�N�g
// ���ҁF���J����
//--------------------------------------------------
// �����F�U��q�̏������`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "Pendulum.h"
#include "TimeZone.h"
#include "Stick.h"
#include "../../GameManager.h"
#include "../../TileMapManager.h"
#include "../../PemdulumManager.h"

#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ChildrenComponent.h"
#include "../Component/StickMoveComponent.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Pendulum::Pendulum(GameManager* _gameManager, Vector3 _fulcrum, bool _movement, float _pendulumAngle, LangthState _langthState)
	:GameObject(_gameManager, "Pendulum")
{
	// �X�v���C�g�R���|�[�l���g
	sprite_component_ = new SpriteComponent(this, "ball");
	// �����蔻��R���|�[�l���g
	collider_component_ = new CircleColliderComponent(this);
	// �U��q�R���|�[�l���g
	pendulum_component_ = new PendulumMovementComponent(this);
	// �q�^�C���]�[��
	time_zone_ = new TimeZone(game_manager_, this);
	// �q�X�e�B�b�N
	stick_ = new Stick(game_manager_, this);

	// �q�I�u�W�F�N�g�Ǘ��R���|�[�l���g
	children_component_ = new ChildrenComponent(this, this);
	children_component_->AddChild(time_zone_);
	children_component_->AddChild(stick_);
	// �C�x���g�ǉ�����
	collider_event_component_ = new ColliderEventComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&Pendulum::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	pendulum_component_->PendulumInit(_fulcrum, _movement, _pendulumAngle);
	pendulum_component_->SetLangthState(static_cast<PendulumMovementComponent::LangthState>(_langthState));
	this->InitGameObject();

	transform_component_->SetSize(TILE_SIZE_X * 1.3, TILE_SIZE_Y * 1.3);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Pendulum::~Pendulum(void)
{
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete collider_component_;
	delete pendulum_component_;
	delete children_component_;
	delete collider_event_component_;
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Pendulum::InitGameObject(void)
{

}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Pendulum::UpdateGameObject(void)
{
	// �^�C���]�[���ɐU��q�������Ă��邩�ǂ�����n��
	DirectX::SimpleMath::Vector3 fulcrumPos = pendulum_component_->GetPendulumFulcrum();	// �U��q�̎x�_���W���擾
	float length = pendulum_component_->GetPendulumLength();								// �U��q�̒������擾
	StickMoveComponent* stickMoveComponent = stick_->GetComponent<StickMoveComponent>();
	// �^�C���]�[���̍��W��U��q�̎x�_�ɍ��킹��
	time_zone_->GetTransformComponent()->SetPosition(fulcrumPos.x, fulcrumPos.y);
	time_zone_->GetTransformComponent()->SetSize((length + transform_component_->GetSize().x) * 2, (length + transform_component_->GetSize().y) * 2);	// �U��q�̒����𔼌a�Ƃ��ă^�C���]�[���̃T�C�Y��ς���

	// �^�C���]�[���̏�Ԃ�ݒ�
	time_zone_->SetTimeZoneState(static_cast<TimeZone::TimeZoneState>(pendulum_component_->GetLangthState()));	
	// �_�̏�Ԃ�ݒ�
	stick_->SetStickLengthState(static_cast<Stick::StickLengthState>(pendulum_component_->GetLangthState()));

	//// �U��q�̖_�̓����𔽉f
	//stickMoveComponent->SetStickFulcrum({ fulcrumPos.x, fulcrumPos.y, 0.0f });
	//float pendulumAngle = pendulum_component_->GetPendulumAngle();
	//stickMoveComponent->SetStickAngle(pendulumAngle);
	////// �U��q�̖_�̍��W���v�Z
	//stickMoveComponent->StickPosition(fulcrumPos, stickMoveComponent->GetStickLength());
}
//--------------------------------------------------
// �����蔻��̎��s����
//--------------------------------------------------
void Pendulum::OnCollisionEnter(GameObject* _other)
{
	bool moveFg = false;
	switch (_other->GetType())
	{
	case GameObject::TypeID::Pendulum:
		moveFg = _other->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
		// �U��q���~�܂��Ă�����
		if ((!moveFg)&&_other->GetComponent<PendulumMovementComponent>()->GetPendulumAngle() == 0)
		{
			// �U��q�̓������J�n
			_other->GetComponent<PendulumMovementComponent>()->SetPendulumMovement(true);
			_other->GetComponent<PendulumMovementComponent>()->StartPendulumMovement();
		}
		break;
	default:
		break;
	}
}
//--------------------------------------------------
// @brief �U��q�̕`��ƍX�V��Ԃ��ꊇ�ŕύX
//--------------------------------------------------
void Pendulum::NotDrawAndStopPendulum(void)
{
	game_manager_->GetPendulumManager()->RemoveGameObject(this);	// �U��q�}�l�[�W���[����U��q���폜
	//game_manager_->GetPendulumManager()->PendulumSearch();

	state_ = State::Dead;
	time_zone_->SetState(State::Dead);
	stick_->SetState(State::Dead);
	sprite_component_->SetState(RenderComponent::State::notDraw);
	time_zone_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	stick_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
}
