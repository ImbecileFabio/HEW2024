//==================================================
// [RobotMoveComponent.cpp] ���{�b�g�ړ��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���{�b�g�̋����𐧌䂷��R���|�[�l���g�̒�`
//==================================================

/*----- �C���N���[�h -----*/
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
	, speed_(20.0f)
	, direction_(Vector2(1.0f, 0.0f))
	, step_scan_distance_(1.0f)
	, max_step_scan_distance_(150.0f)
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
	auto transform = this->owner_->GetComponent<TransformComponent>();

	if (!velocity || !collider || !transform)
	{
		std::cout << std::format("[RobotMoveComponent]-> �R���|�[�l���g���擾�ł��܂���ł���\n");
		return; 
	}

	this->CheckTurnAround(*transform, *collider);

	// �i�s�����ɐi��
	velocity->SetVelocity(Vector3(direction_.x * speed_, direction_.y * speed_, 0.0f));

	// �i�����`�F�b�N
	auto objects = this->owner_->GetGameManager()->GetGameObjects();
	auto stepHeight = ChackStepHeight(*transform, objects);
}


//--------------------------------------------------
// �i�s���������߂�
//--------------------------------------------------
void RobotMoveComponent::CheckTurnAround(const TransformComponent& _transform, const BoxColliderComponent& _collider)
{
	auto pos = _transform.GetPosition();
	auto size = _collider.GetBoxSize();
	// ��ʊO�ɏo�����ɂȂ�Ȃ�
	if (pos.x < (-960 - size.x / 2))
	{
		direction_ = Vector2(1.0f, 0.0f);
	}
	else if (pos.x > (960 + size.x / 2))
	{
		direction_ = Vector2(-1.0f, 0.0f);
	}
}

// ���Ԃ�΂����Ă܂�
//--------------------------------------------------
// @brief �i���̍����𒲂ׂ�
// @param _transform ���{�b�g�̎p��, _gameObjects ���I�u�W�F�N�g
// @return �i���̍���
//--------------------------------------------------
std::optional<float> RobotMoveComponent::ChackStepHeight(const TransformComponent& _transform, const std::vector<GameObject*> _gameObjects)
{
	auto position = _transform.GetPosition();
	Vector2 scanStart = position + Vector2(direction_.x * step_scan_distance_);
	Vector2 scnaEnd = scanStart + Vector2(0, -max_step_scan_distance_);

	float closestStepHeight = max_step_scan_distance_ + 1;	// �����l�F �X�L�����͈͊O�𒴂���l

	for (const auto& obj : _gameObjects) {
		auto boxsize = obj->GetComponent<BoxColliderComponent>()->GetBoxSize();
		// ���������ɑ����̃��C�����d�Ȃ��Ă��邩�`�F�b�N
		if (boxsize.y <= scanStart.x && boxsize.z >= scanStart.x) {
			// �i���̍������v�Z
			float stepHeight = position.y - boxsize.w;
			if (stepHeight >= 0 && stepHeight <= max_step_height_) {
				closestStepHeight = min(closestStepHeight, stepHeight);
			}
		}
	}

	// �ł��߂��i����������΂��̍�����Ԃ�
	if (closestStepHeight <= max_step_height_) {
		return closestStepHeight;
	}

	return std::nullopt; // �i�����Ȃ�
}

