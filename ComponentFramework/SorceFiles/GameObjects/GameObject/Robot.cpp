//==================================================
// [Robot.cpp] ���{�b�g�I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���{�b�g�̏������`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "Robot.h"

#include "../../GameManager.h"
#include "../../TileMapManager.h"
#include "../../AudioManager.h"
#include "Lift.h"
#include "Gimmick/Smoke.h"
#include "Gimmick/SmokePipe.h"

#include "../Component.h"
#include "../Component/TransformComponent.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/RenderComponent/AnimationComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ColliderComponent/BoxColliderComponent.h"
#include "../Component/RigidbodyComponent/VelocityComponent.h"
#include "../Component/GravityComponent.h"
#include "../Component/RobotMoveComponent.h"
#include "../Component/PushOutComponent.h"
#include "../Component/GimmickComponent/SmokeComponent.h"
#include "../Component/GimmickComponent/LiftInteractionComponent.h"
#include "../Component/GimmickComponent/SmokeInteractionComponent.h"


//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
Robot::Robot(GameManager* _gameManager)
	:GameObject(_gameManager, "Robot")
	, robot_state_(RobotState::Move)
{
	sprite_component_ = new SpriteComponent(this, "robot_walk", 50);	// �X�v���C�g
	animation_component_ = new AnimationComponent(this, sprite_component_);	// �A�j���[�V����
	velocity_component_ = new VelocityComponent(this, 5);	// ���x
	gravity_component_ = new GravityComponent(this, 6);	// �d��
	collider_component_ = new BoxColliderComponent(this, 10);	// �����蔻��
	collider_event_component_ = new ColliderEventComponent(this, 11);	// �����蔻��C�x���g
	robot_move_component_ = new RobotMoveComponent(this, 3);	// ���{�b�g�ړ�
	push_out_component_ = new PushOutComponent(this, 15);	// �����o��
	lift_interaction_component_ = new LiftInteractionComponent(this, 20);	// ���t�g�Ƃ̂����

	auto f = std::function<void(GameObject*)>(std::bind(&Robot::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);


	this->InitGameObject();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
Robot::~Robot(void)
{
	// �����ŃR���|�[�l���g���폜
	delete sprite_component_;
	delete collider_component_;
	delete collider_event_component_;
	delete velocity_component_;
	delete gravity_component_;
	delete robot_move_component_;
	delete push_out_component_;
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void Robot::InitGameObject(void)
{
	transform_component_->SetSize(TILE_SIZE_X * 2.0f, TILE_SIZE_Y * 2.0f);
	collider_component_->SetSize(transform_component_->GetSize().x * 0.7f, transform_component_->GetSize().y * 0.95f);
	collider_component_->SetLayer(ColliderBaseComponent::Robot);
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void Robot::UpdateGameObject(void)
{

	// ���͏���
	InputManager& input = InputManager::GetInstance();

	// �}�E�X�N���b�N�ňړ�
	if (input.GetMouseButtonPress(0)) {
		auto mousePos = input.GetMousePosition();
		transform_component_->SetPosition(
			static_cast<float>(mousePos.x) - (GameProcess::GetWidth() / 2),
			-(static_cast<float>(mousePos.y) - (GameProcess::GetHeight() / 2)));
	}




	// state�ɂ���ď�����ς���
	switch (robot_state_)
	{
	case RobotState::Idle:	// �ҋ@���
	{
		if (InputManager::GetInstance().GetKeyTrigger(VK_RETURN))
		{
			if (robot_state_ != RobotState::Move)
			{
				robot_state_ = RobotState::Move;
				sprite_component_->SetTexture("robot_walk");
			}
		}
		break;
	}
	case RobotState::Move:	// �ړ����
	{
		// �����Ă�����
		if (!gravity_component_->CheckGroundCollision()) {
			if (robot_state_ != RobotState::Fall)
			{
				robot_state_ = RobotState::Fall;
				sprite_component_->SetTexture("robot_drop");
			}
		}


		// �T�E���h���J��Ԃ�����
		if (!AudioManager::GetInstance()->GetPlayingState(SoundLabel_RobotMoveSE))
			AudioManager::GetInstance()->Play(SoundLabel_RobotMoveSE);
		break;
	}
	case RobotState::Fall:	// �������
	{
		// �n�ʂɂ�����
		if (gravity_component_->CheckGroundCollision()) {
			// �ړ���ԂɑJ��
			if (robot_state_ != RobotState::Move)
			{
				robot_state_ = RobotState::Move;
				sprite_component_->SetTexture("robot_walk");
			}
			AudioManager::GetInstance()->Play(SoundLabel_RobotLandingSE);
		}
		break;
	}
	case RobotState::OnLift:	// ���t�g�ɏ���Ă�����
	{
		if (lift_interaction_component_->GetLift() == nullptr)
		{
			robot_state_ = RobotState::Move;
			sprite_component_->SetTexture("robot_walk");
		}

		break;
	}
	}


	// ���{�b�g�̓�����؂�ւ���
	robot_move_component_->SetState(static_cast<RobotMoveComponent::RobotMoveState>(robot_state_));

	// �i�s�����ɍ��킹�ĉ摜�𔽓]����
	if (velocity_component_->GetVelocity().x > 0) {	// �E����
		sprite_component_->SetFlip(true, false);
	}
	else if (velocity_component_->GetVelocity().x < 0) {	// ������
		sprite_component_->SetFlip(false, false);
	}

}


void Robot::OnCollisionEnter(GameObject* _other)
{

	if (state_ == State::Paused) return;


	switch (_other->GetType())
	{
	case GameObject::TypeID::Tile:
	{
		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// �����o������
		}
		break;
	}
	case GameObject::TypeID::Lift:
	{
		auto lift = dynamic_cast<Lift*>(_other);

		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// �����o������
		}

		// ���t�g�������Ă��Ȃ��Ȃ�
		if (lift->GetLiftState() == Lift::LiftState::Stop) {
			robot_state_ = RobotState::Move;
			sprite_component_->SetTexture("robot_walk");
			return;
		}

		// �܂�OnLift�ł͂Ȃ����
		if(robot_state_ != RobotState::OnLift)
		{
			if (lift_interaction_component_->IsTouchingLiftCenter(lift))
			{
				lift_interaction_component_->SetLift(lift);
				robot_state_ = RobotState::OnLift;
				lift->SetLiftState(Lift::LiftState::Move);
				sprite_component_->SetTexture("robot_still");
			}
		}




		break;
	}
	case GameObject::TypeID::WeakFloor:
	{
		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// �����o������
		}
		break;
	}
	case GameObject::TypeID::Smoke:
	{
		auto pos = transform_component_->GetPosition();
		auto vel = velocity_component_->GetVelocity();

		auto smoke = dynamic_cast<Smoke*>(_other);
		auto smokepipe = dynamic_cast<SmokePipe*>(smoke->GetOwnerObj());

		if (smokepipe->GetBrakeFlg())
		{
			if (pos.y <= smoke->GetTransformComponent()->GetPosition().y + smoke->GetTransformComponent()->GetSize().y) {
				transform_component_->SetPosition({
					pos.x,
					pos.y + 10.0f,
					pos.z
					});
			}
		}
		break;
	}
	case GameObject::TypeID::SteePillarFloor:
	{
		if (push_out_component_)
		{
			push_out_component_->ResolveCollision(_other);	// �����o������
		}
		break;
	}
	default:

		break;
	}
}