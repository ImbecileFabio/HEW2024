//==================================================
// [RobotMoveComponent.cpp] ���{�b�g�ړ��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���{�b�g�̋����𐧌䂷��R���|�[�l���g�̒�`
// �����ŉ��ɕ���
// �ǂɓ��������甽�]����
// �n�ʂ��Ȃ��ꍇ�͔��]����
// 
// �����̏�����p�����Ƃɂ�����������ł܂��A�R���|�[�l���g�w���Ƃ͂�������
// �����Ⴎ����R�[�h�ł��߂�Ȃ���
//==================================================

/*----- �C���N���[�h -----*/
#include <memory>

#include "RobotMoveComponent.h"

#include "../../GameManager.h"
#include "../../TileMapManager.h"
#include "../../ColliderManager.h"

#include "../GameObject.h"

#include "RigidbodyComponent/VelocityComponent.h"
#include "ColliderComponent/BoxColliderComponent.h"
#include "ColliderComponent/ScanColliderComponent.h"
#include "GravityComponent.h"


#include "RenderComponent/SpriteComponent.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
RobotMoveComponent::RobotMoveComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
	, speed_(2.0f)
	, direction_(Vector2(1.0f, 0.0f))
	, scan_distance_(1.0f)
	, step_up_height_(TILE_SIZE_Y)
{
	
	this->Init();
}


//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
RobotMoveComponent::~RobotMoveComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void RobotMoveComponent::Init()
{
	direction_ = Vector2(1.0f, 0.0f);

	if (!wall_scan_object_) {
		// �X�L�����p�I�u�W�F�N�g�𐶐�
		wall_scan_object_ = new GameObject(owner_->GetGameManager(), "WallScanObject");
		wall_scan_collider_ = new ScanColliderComponent(wall_scan_object_);
	}
	if (!step_scan_object_)
	{
		// �X�e�b�v�A�b�v�p�I�u�W�F�N�g�𐶐�
		step_scan_object_ = new GameObject(owner_->GetGameManager(), "StepScanObject");
		step_scan_collider_ = new ScanColliderComponent(step_scan_object_);

	}
	if (!ground_scan_object_)
	{
		// �n�ʃX�L�����p�I�u�W�F�N�g�𐶐�
		ground_scan_object_ = new GameObject(owner_->GetGameManager(), "GroundScanObject");
		ground_scan_collider_ = new ScanColliderComponent(ground_scan_object_);
	}
	owner_transform_ = owner_->GetTransformComponent();
	owner_velocity_ = owner_->GetComponent<VelocityComponent>();
	owner_collider_ = owner_->GetComponent<BoxColliderComponent>();
	owner_gravity_ = owner_->GetComponent<GravityComponent>();


}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void RobotMoveComponent::Uninit()
{
}


//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void RobotMoveComponent::Update()
{
	if (!owner_transform_ || !owner_velocity_ || !owner_collider_ || !owner_gravity_)	//	��x�����擾
	{
		owner_transform_ = owner_->GetTransformComponent();
		owner_velocity_ = owner_->GetComponent<VelocityComponent>();
		owner_collider_ = owner_->GetComponent<BoxColliderComponent>();
		owner_gravity_ = owner_->GetComponent<GravityComponent>();

	}

	if (!owner_transform_ || !owner_velocity_ || !owner_collider_ || !owner_gravity_)
	{
		std::cout << std::format("��RobotMoveComponent�� -> Update Error\n");
		return;
	}


	// �����蔻��̍X�V
	this->UpdateWallScanCollider();
	this->UpdateStepScanCollider();
	this->UpdateGroundScanCollider();

	// �ǂ̏Փ˔���
	if (CheckWallCollision())	// �ǂɓ������Ă���
	{
		// �X�e�b�v�A�b�v����
		if (!CheckStepUp())	// �o���i��
		{
			// ���
			owner_transform_->SetPosition(owner_transform_->GetPosition() + Vector3(0.0f, step_up_height_, 0.0f));
		}
		else				// �o��Ȃ��i��
		{
			direction_ = { -direction_.x, direction_.y };	// �ړ������𔽓]
			owner_velocity_->SetVelocity({ 0.0f, owner_velocity_->GetVelocity().y, 0.0f });	// ���̑��x�����Z�b�g
		}
	}
	// ���̏Փ˔���
	else if (!CheckGround())	//�i�s�����ɒn�ʂ��Ȃ�
	{
		direction_ = { -direction_.x, direction_.y };	// �ړ������𔽓]
		owner_velocity_->SetVelocity({ 0.0f, owner_velocity_->GetVelocity().y, 0.0f });	// ���̑��x�����Z�b�g
	}

	// �󒆂łȂ���Έړ�
	if(owner_gravity_->GetIsGround())
	owner_velocity_->SetVelocity({ speed_ * direction_.x, owner_velocity_->GetVelocity().y, 0.0f});
}

//--------------------------------------------------
// �E�H�[���X�L�����p�q�b�g�{�b�N�X�̍X�V
//--------------------------------------------------
void RobotMoveComponent::UpdateWallScanCollider()
{
	auto robotPos = owner_transform_->GetPosition();
	auto robotSize = owner_collider_->GetSize();

	wall_scan_object_->GetTransformComponent()->SetSize(scan_distance_, owner_transform_->GetSize().y - 5.0f);
	wall_scan_collider_->SetSize(wall_scan_object_->GetTransformComponent()->GetSize());

	Vector3 offset = { 0.0f, 0.0f, 0.0f };
	if (direction_.x > 0)
		offset = { ( robotSize.x+ scan_distance_) / 2, 0.0f, 0.0f };
	else
		offset = { (-robotSize.x - scan_distance_) / 2, 0.0f, 0.0f };
	wall_scan_collider_->SetOffset(offset);
	wall_scan_collider_->SetWorldHitBox(robotPos);

	wall_scan_object_->GetTransformComponent()->SetPosition(robotPos + offset);
}

//--------------------------------------------------
// �i���X�L�����p�̃q�b�g�{�b�N�X�̍X�V
//--------------------------------------------------
void RobotMoveComponent::UpdateStepScanCollider()
{
	auto robotPos = owner_transform_->GetPosition();
	auto robotSize = owner_collider_->GetSize();

	step_scan_object_->GetTransformComponent()->SetSize(owner_collider_->GetSize().x + scan_distance_, owner_transform_->GetSize().y);
	step_scan_collider_->SetSize(step_scan_object_->GetTransformComponent()->GetSize());

	Vector3 offset = { 0.0f, 0.0f, 0.0f };
	if (direction_.x > 0)
		offset = {  scan_distance_ / 2, robotSize.y, 0.0f};
	else
		offset = { -scan_distance_ / 2, robotSize.y, 0.0f};
	step_scan_collider_->SetOffset(offset);
	step_scan_collider_->SetWorldHitBox(robotPos);

	step_scan_object_->GetTransformComponent()->SetPosition(robotPos+offset);
}
//--------------------------------------------------
// �n�ʃX�L�����p�̃q�b�g�{�b�N�X�̍X�V
//--------------------------------------------------
void RobotMoveComponent::UpdateGroundScanCollider()
{
	auto robotPos = owner_transform_->GetPosition();
	auto robotSize = owner_collider_->GetSize();

	ground_scan_object_->GetTransformComponent()->SetSize(owner_collider_->GetSize().x + scan_distance_, owner_transform_->GetSize().y + 5.0f);
	ground_scan_collider_->SetSize(step_scan_object_->GetTransformComponent()->GetSize());

	Vector3 offset = { 0.0f, 0.0f, 0.0f };
	if(direction_.x > 0)
		offset = { ( robotSize.x + scan_distance_), (-robotSize.y - scan_distance_), 0.0f };
	else
		offset = { (-robotSize.x - scan_distance_), (-robotSize.y - scan_distance_), 0.0f };

	ground_scan_collider_->SetOffset(offset);
	ground_scan_collider_->SetWorldHitBox(robotPos);

	ground_scan_object_->GetTransformComponent()->SetPosition(robotPos + offset);

}

//--------------------------------------------------
// @brief �ǂƂ̏Փˌ��m
// @return �Փ˂��Ă���: true, ���Ă��Ȃ�: false
//--------------------------------------------------
bool RobotMoveComponent::CheckWallCollision()
{
	auto objects = owner_->GetGameManager()->GetColliderManager()->GetColliderGameObjects();
	auto scanHitbox = wall_scan_collider_->GetWorldHitBox();

	// �Փ˔���
	for (const auto& obj : objects) {
		auto otherCollider = obj->GetComponent<ColliderBaseComponent>();
		if (auto otherBoxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider)) {
			auto otherHitbox = otherBoxCollider->GetWorldHitBox();

			// �g���q�b�g�{�b�N�X�Ƒ��I�u�W�F�N�g��AABB���d�Ȃ�ꍇ�A�Փ˂Ɣ���
			if (scanHitbox.max_.x > otherHitbox.min_.x && scanHitbox.min_.x < otherHitbox.max_.x &&
				scanHitbox.max_.y > otherHitbox.min_.y && scanHitbox.min_.y < otherHitbox.max_.y) {

				// �X�L�����p�q�b�g�{�b�N�X�Ƒ��̃I�u�W�F�N�g��AABB���d�Ȃ�ꍇ�A�Փ˂Ɣ���
				if (scanHitbox.max_.x > otherHitbox.min_.x && scanHitbox.min_.x < otherHitbox.max_.x &&
					scanHitbox.max_.y > otherHitbox.min_.y && scanHitbox.min_.y < otherHitbox.max_.y) {
					return true;
				}
			}
		}
	}
	return false;
}

//--------------------------------------------------
// @brief �i�����m
// @return �i��������: true, �Ȃ�: false
//--------------------------------------------------
bool RobotMoveComponent::CheckStepUp()
{
	auto objects = owner_->GetGameManager()->GetColliderManager()->GetColliderGameObjects();
	auto stepHitbox = step_scan_collider_->GetWorldHitBox();
	for (const auto& obj : objects) {
		auto otherCollider = obj->GetComponent<ColliderBaseComponent>();
		if (auto otherBoxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider)) {
			auto otherHitbox = otherBoxCollider->GetWorldHitBox();

			// �i�����o (�͈͓��ɑ��I�u�W�F�N�g������ꍇ)
			if (stepHitbox.max_.x > otherHitbox.min_.x && stepHitbox.min_.x < otherHitbox.max_.x &&
				stepHitbox.max_.y > otherHitbox.min_.y && stepHitbox.min_.y < otherHitbox.max_.y) {
				return true;
			}
		}
	}
	return false;
}

//--------------------------------------------------
// @brief �n�ʌ��m
// @return �n�ʂ�����: true, �Ȃ�: false
//--------------------------------------------------
bool RobotMoveComponent::CheckGround()
{
	auto objects = owner_->GetGameManager()->GetColliderManager()->GetColliderGameObjects();
	auto groundHitbox = ground_scan_collider_->GetWorldHitBox();
	for (const auto& obj : objects) {
		auto otherCollider = obj->GetComponent<ColliderBaseComponent>();
		if (auto otherBoxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider)) {
			auto otherHitbox = otherBoxCollider->GetWorldHitBox();

			// �i�����o (�͈͓��ɑ��I�u�W�F�N�g������ꍇ)
			if (groundHitbox.max_.x > otherHitbox.min_.x && groundHitbox.min_.x < otherHitbox.max_.x &&
				groundHitbox.max_.y > otherHitbox.min_.y && groundHitbox.min_.y < otherHitbox.max_.y) {
				return true;
			}
		}
	}
	return false;
}
