//=================================================================
// [LiftGroup.cpp] ���t�g�O���[�v�\�[�X�t�@�C��
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F���t�g�O���[�v����
//=================================================================
/*----- �C���N���[�h -----*/
#include "LiftGroup.h"
#include "../Lift.h"
#include "../Pendulum.h"
#include "../../Component/PendulumMovementComponent.h"
#include "../../Component/GimmickComponent/LiftComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
LiftGroup::LiftGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "LiftGroup")
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
LiftGroup::~LiftGroup(void)
{
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void LiftGroup::InitGameObject(void)
{
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void LiftGroup::UpdateGameObject(void)
{
    if (!isCenterMedian)
    {
        size_t size = liftTiles_.size();
        if (size == 0)
        {
            // �^�C�������݂��Ȃ��ꍇ�͏������X�L�b�v
            return;
        }

        // �����ʒu���L���b�V��
        initialPositions_.clear();
        for (auto& tile : liftTiles_)
        {
            initialPositions_.push_back(tile->GetTransformComponent()->GetPosition());
            owner_lift_components_.push_back(tile->GetComponent<LiftComponent>());
        }

        DirectX::SimpleMath::Vector3 centerPos;

        if (size % 2 == 0) // ����
        {
            int leftIndex = (size / 2) - 1;
            int rightIndex = size / 2;
            tileCenterNum_ = leftIndex;

            DirectX::SimpleMath::Vector3 leftPos = initialPositions_[leftIndex];
            DirectX::SimpleMath::Vector3 rightPos = initialPositions_[rightIndex];
            centerPos = (leftPos + rightPos) / 2.0f;

            auto lift = dynamic_cast<Lift*>(liftTiles_[leftIndex]);
            auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
            lift->SetPendulum(pendulum);
            lift->GetComponent<LiftComponent>()->SetPendulum(pendulum);
        }
        else // �
        {
            int centerIndex = size / 2;
            tileCenterNum_ = centerIndex;

            centerPos = initialPositions_[centerIndex];

            auto lift = dynamic_cast<Lift*>(liftTiles_[centerIndex]);
            auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
            lift->SetPendulum(pendulum);
            lift->GetComponent<LiftComponent>()->SetPendulum(pendulum);
        }
        isCenterMedian = true;
    }

    // ���݂̒��S�^�C���ʒu
    DirectX::SimpleMath::Vector3 centerLiftPos = liftTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition();
    DirectX::SimpleMath::Vector3 centerInitialPos = initialPositions_[tileCenterNum_];
    DirectX::SimpleMath::Vector3 currentOffset = centerLiftPos - centerInitialPos;

    // �e�^�C���̈ʒu���X�V
    for (size_t i = 0; i < liftTiles_.size(); ++i)
    {
        if (i == tileCenterNum_) continue; // ���S�^�C���͍X�V���Ȃ�

        DirectX::SimpleMath::Vector3 newPosition = initialPositions_[i] + currentOffset;
        liftTiles_[i]->GetTransformComponent()->SetPosition(newPosition);
    }
}
//--------------------------------------------------
// @brief ���t�g�^�C����ǉ�
// @param _tile[�ǉ�����^�C���I�u�W�F�N�g]
//--------------------------------------------------
void LiftGroup::AddLiftTile(GameObject* _tile)
{
	liftTiles_.push_back(_tile);
    auto lift = dynamic_cast<Lift*>(_tile);
    lift->SetLiftGroup(this);
}
//--------------------------------------------------
// @brief �M�~�b�N�ƘA������U��q��ݒ�A�U��q�̃R���|�[�l���g���L���b�V��
// @param _centerPendulum[�U��q�I�u�W�F�N�g]
//--------------------------------------------------
void LiftGroup::SetPendulumANDMovement(GameObject* _centerPendulum)
{
	centerPendulum_ = _centerPendulum;
	// �U��q�̃R���|�[�l���g���擾���Ă���
	owner_pendulum_movement_ = centerPendulum_->GetComponent<PendulumMovementComponent>();
}


