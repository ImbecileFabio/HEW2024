//=================================================================
// [SteePillarFloorGroup.cpp] SteePillarFloorGroup�\�[�X�t�@�C��
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����FSteePillarFloorGroup����
//=================================================================
/*----- �C���N���[�h -----*/
#include "SteePillarFloorGroup.h"
#include "../SteePillarFloor.h"
#include "../../../GameObject/Pendulum.h"
#include "../../../Component/PendulumMovementComponent.h"
#include "../../../Component/EventComponent/ColliderEventComponent.h"
#include "../../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../../Component/TimerComponent.h"
#include "SteePillarLeftGroup.h"
#include "SteePillarRightGroup.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SteePillarFloorGroup::SteePillarFloorGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarFloorGroup")
	, isCenterMedian_(false)
	, tileCenterNum_(0)
	, centerPendulum_(nullptr)
	, owner_pendulum_movement_(nullptr)
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
SteePillarFloorGroup::~SteePillarFloorGroup(void)
{
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SteePillarFloorGroup::InitGameObject(void)
{
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SteePillarFloorGroup::UpdateGameObject(void)
{
	// �U��q�𒆐S�ɒ������鏈��
	if (!isCenterMedian_)
	{
		if (steePillarFloorTiles_.empty()) return;
		if (initialPositions_.empty()) // �����ʒu�̃L���b�V�����܂��̏ꍇ
		{
			// �����ʒu���L���b�V��
			initialPositions_.clear();
			for (auto& tile : steePillarFloorTiles_)
			{
				initialPositions_.push_back(tile->GetTransformComponent()->GetPosition());
			}
		}

		int size = static_cast<int>(steePillarFloorTiles_.size());
		DirectX::SimpleMath::Vector3 centerPos;

		if (size % 2 == 0) // ����
		{
			// ���S2�̃^�C���̃C���f�b�N�X���v�Z
			leftIndex_ = (size / 2) - 1;
			rightIndex_ = size / 2;

			// ���S2�̃^�C���̈ʒu���擾���A���ς��v�Z
			DirectX::SimpleMath::Vector3 leftPos = steePillarFloorTiles_[leftIndex_]->GetTransformComponent()->GetPosition();
			DirectX::SimpleMath::Vector3 rightPos = steePillarFloorTiles_[rightIndex_]->GetTransformComponent()->GetPosition();
			centerPos = (leftPos + rightPos) / 2.0f;
		}
		else // �
		{
			isOddNumber_ = false;
			// ���S�̃^�C���̃C���f�b�N�X���v�Z
			tileCenterNum_ = size / 2;
			// ���S�̃^�C���̈ʒu���擾
			centerPos = steePillarFloorTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition();
		}
		// �U��q�̒��S��ݒ�
		owner_pendulum_movement_->SetPendulumFulcrum(centerPos);
		isCenterMedian_ = true;
	}
	if (owner_pendulum_movement_->GetPendulumMovement() && !isPendulumDelete_)
	{
		steePillarLeftGroup_->SetIsBreak(true);
		steePillarLeftGroup_->SetIsBreakStop(false);
		steePillarRightGroup_->SetIsBreakStop(false);
		steePillarRightGroup_->SetIsBreak(true);
	}
	else
	{
		steePillarLeftGroup_->SetIsBreakStop(true);
		steePillarRightGroup_->SetIsBreakStop(true);
	}
	// ���S���̃A�j���[�V�������I��������
	if (steePillarRightGroup_->GetIsAnimationEnd() && !isDownStart_)
	{
		isDownStart_ = true;	// ���������̊J�n��ݒ�

		for (auto& it : steePillarFloorTiles_)
		{
			auto steePillarFloor = dynamic_cast<SteePillarFloor*>(it);
			steePillarFloor->SetIsDown(true);
		}
		// ���E�̓S���O���[�v�̗����t���O��ݒ�
		steePillarLeftGroup_->SetIsDownStart(true);
		steePillarRightGroup_->SetIsDownStart(true);
	}

	if (isOddNumber_)	// ����
	{
		DirectX::SimpleMath::Vector3 centerPos = (steePillarFloorTiles_[leftIndex_]->GetTransformComponent()->GetPosition() + steePillarFloorTiles_[rightIndex_]->GetTransformComponent()->GetPosition()) / 2.0f;
		owner_pendulum_movement_->SetPendulumFulcrum(centerPos);
	}
	else                // �
	{
		owner_pendulum_movement_->SetPendulumFulcrum(steePillarFloorTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition());
	}
	// �S���̏����^�C���Ɠ������Ă�����
	if (isHitTile_ && !isPendulumDelete_)
	{
		auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
		pendulum->NotDrawAndStopPendulum();
		isPendulumDelete_ = true;
		for (auto& it : steePillarFloorTiles_)
		{
			auto steePillarFloor = dynamic_cast<SteePillarFloor*>(it);
			steePillarFloor->SetIsDown(false);
		}
		steePillarLeftGroup_->SetVelocityStop();
		steePillarRightGroup_->SetVelocityStop();
	}
	// ��ʊO����
	if (steePillarFloorTiles_[0]->GetTransformComponent()->GetPosition().y < -500.0f && !isPendulumDelete_)
	{
		auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
		pendulum->NotDrawAndStopPendulum();
		isPendulumDelete_ = true;
	}
}
//--------------------------------------------------
// @brief �Ƃ����^�C����ǉ�
// @param _tile[�ǉ�����^�C���I�u�W�F�N�g]
//--------------------------------------------------
void SteePillarFloorGroup::AddSteePillarFloorTile(GameObject* _tile)
{
	steePillarFloorTiles_.emplace_back(_tile);
	auto steePillarFloor = dynamic_cast<SteePillarFloor*>(_tile);
	steePillarFloor->SetSteePillarFloorGroup(this);
}
//--------------------------------------------------
// @brief �M�~�b�N�ƘA������U��q��ݒ�A�U��q�̃R���|�[�l���g���L���b�V��
// @param _centerPendulum[�U��q�I�u�W�F�N�g]
//--------------------------------------------------
void SteePillarFloorGroup::SetPendulumANDMovement(GameObject* _centerPendulum)
{
	centerPendulum_ = _centerPendulum;
	// �U��q�̃R���|�[�l���g���擾���Ă���
	owner_pendulum_movement_ = centerPendulum_->GetComponent<PendulumMovementComponent>();
}

void SteePillarFloorGroup::SetSteePillarLeftGroup(SteePillarLeftGroup* _steePillarLeftGroup)
{
	steePillarLeftGroup_ = _steePillarLeftGroup;
}

void SteePillarFloorGroup::SetSteePillarRightGroup(SteePillarRightGroup* _steePillarRightGroup)
{
	steePillarRightGroup_ = _steePillarRightGroup;
}

void SteePillarFloorGroup::UpdateSteePillarFloorTilePositions()
{
	if (initialPositions_.empty()) return;
	DirectX::SimpleMath::Vector3 centerLiftPos = steePillarFloorTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition();
	DirectX::SimpleMath::Vector3 centerInitialPos = initialPositions_[tileCenterNum_];
	DirectX::SimpleMath::Vector3 currentOffset = centerLiftPos - centerInitialPos;

	for (int i = 0; i < steePillarFloorTiles_.size(); i++)
	{
		DirectX::SimpleMath::Vector3 newPosition = initialPositions_[i] + currentOffset;
		steePillarFloorTiles_[i]->GetTransformComponent()->SetPosition(newPosition);
	}
}


