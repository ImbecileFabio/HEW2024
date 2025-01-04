//==================================================
// [RobotMoveComponent.cpp] ���{�b�g�ړ��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���{�b�g�̋����𐧌䂷��R���|�[�l���g�̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include <memory>

#include "RobotMoveComponent.h"

#include "../GameObject.h"
#include "../../GameManager.h"
#include "RigidbodyComponent/VelocityComponent.h"
#include "ColliderComponent/BoxColliderComponent.h"
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
RobotMoveComponent::RobotMoveComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
	, speed_(1.0f)
	, direction_(Vector2(1.0f, 0.0f))
	, max_step_height_(100.0f)
	, step_scan_distance_(1.0f)
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
	auto velocity = this->owner_->GetComponent<VelocityComponent>();
	auto collider = this->owner_->GetComponent<BoxColliderComponent>();
	auto transform = this->owner_->GetTransformComponent();

	if (!velocity || !collider || !transform)
	{
		std::cout << std::format("[RobotMoveComponent]-> �R���|�[�l���g���擾�ł��܂���ł���\n");
		return; 
	}

	// �i�����`�F�b�N
	auto objects = this->owner_->GetGameManager()->GetGameObjects();
	auto stepHeightOpt = CheckStepHeight(*transform, collider->GetSize(), objects);

	// �i��������ꍇ
	if (stepHeightOpt.has_value()) {
		float stepHeight = stepHeightOpt.value();
		// �i�����ő�l�ȉ��Ȃ�
		if (std::abs(stepHeight) <= max_step_height_) {
			// �i�������or�~���
			auto pos = transform->GetPosition();
			transform->SetPosition(Vector3(pos.x, pos.y + stepHeight, pos.z));
		}
		// �i�����ő�l�𒴂���ꍇ
		else {
			// �i������������ꍇ�͐i�H�������𔽓]
			direction_ = Vector2(-direction_.x, direction_.y);
		}
	}


	// �i�s�����ɐi��
	velocity->SetVelocity(Vector3(direction_.x * speed_, direction_.y * speed_, 0.0f));

}


// �΂����Ă܂�
//--------------------------------------------------
// @param _transform ���g�̃g�����X�t�H�[��, _gameObjects �I�u�W�F�N�g���X�g
// @brief �i���̍����𒲂ׂ�
// @return �i���̍���
//--------------------------------------------------
std::optional<float> RobotMoveComponent::CheckStepHeight(const TransformComponent& _transform, const Vector3& _size,  const std::vector<GameObject*> _gameObjects)
{
	auto position = _transform.GetPosition();
	Vector2 scanStart = Vector2((position.x + _size.x ) + direction_.x * step_scan_distance_, position.y);
	Vector2 scanEnd   = Vector2(scanStart.x, scanStart.y - max_step_height_);

	float closestStepHeight = max_step_height_ + 1;	// �����l�F �X�L�����͈͊O�𒴂���l

	// �I�u�W�F�N�g���X�g�𑖍�
	for (const auto& obj : _gameObjects) {
		auto otherCollider = obj->GetComponent<ColliderBaseComponent>();
		if(auto boxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider))
		{
			auto hitbox = boxCollider->GetWorldHitBox();
			// �����̃X�L�������C����AABB�ɏd�Ȃ��Ă��邩�m�F
			if (scanStart.x >= hitbox.min_.x && scanStart.x <= hitbox.max_.x) {
				float stepHeight = hitbox.max_.y - scanEnd.y;  // �i���̍���
				// �o���i���̍������m�F
				if (stepHeight > 0 && stepHeight <= max_step_height_) {
					closestStepHeight = min(closestStepHeight, stepHeight);
				}
			}
		}
	}
	// �ł��߂��i����������΂��̍�����Ԃ�
	if (closestStepHeight <= max_step_height_) {
		std::cout << std::format("�i���̍����F{}\n", closestStepHeight);
		return closestStepHeight;
	}

	return std::nullopt; // �i�����Ȃ�
}

