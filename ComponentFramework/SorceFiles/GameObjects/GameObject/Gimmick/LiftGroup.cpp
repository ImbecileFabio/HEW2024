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
        if (liftTiles_.empty()) return;
        if (initialPositions_.empty()) // �����ʒu�̃L���b�V�����܂��̏ꍇ
        {
            // �����ʒu���L���b�V��
            initialPositions_.clear();
            owner_lift_components_.clear();
            for (auto& tile : liftTiles_)
            {
                tile->GetTransformComponent()->SetSize(61.0f, 60.0f);
                initialPositions_.push_back(tile->GetTransformComponent()->GetPosition());
                owner_lift_components_.push_back(tile->GetComponent<LiftComponent>());
            }
        }

        int size = static_cast<int>(liftTiles_.size());
        DirectX::SimpleMath::Vector3 centerPos;

        if (size % 2 == 0) // �����̏ꍇ
        {
			isLeftRight_ = false;
            tileCenterNum_ = static_cast<int>(rightIndex_);

            centerPos = (initialPositions_[leftIndex_] + initialPositions_[rightIndex_]) / 2.0f;

            auto lift = dynamic_cast<Lift*>(liftTiles_[rightIndex_]);
            auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
            pendulum->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(centerPos);
            if (lift && pendulum)
            {
                lift->SetPendulum(pendulum);
                lift->GetComponent<LiftComponent>()->SetPendulum(pendulum);
            }
        }
        else // ��̏ꍇ
        {
            isLeftRight_ = true;
            centerIndex_ = size / 2;
            tileCenterNum_ = static_cast<int>(centerIndex_);

            centerPos = initialPositions_[centerIndex_];

            auto lift = dynamic_cast<Lift*>(liftTiles_[centerIndex_]);
            auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
            if (lift && pendulum)
            {
                lift->SetPendulum(pendulum);
                lift->GetComponent<LiftComponent>()->SetPendulum(pendulum);
            }
        }
        isCenterMedian = true;
    }
	if (isLeftRight_)
	{
        DirectX::SimpleMath::Vector3 centerPos = liftTiles_[centerIndex_]->GetTransformComponent()->GetPosition();
        owner_pendulum_movement_->SetPendulumFulcrum(centerPos);
    }
    else
    {
        DirectX::SimpleMath::Vector3 centerPos = (liftTiles_[leftIndex_]->GetTransformComponent()->GetPosition() + liftTiles_[rightIndex_]->GetTransformComponent()->GetPosition()) / 2.0f;
        owner_pendulum_movement_->SetPendulumFulcrum(centerPos);
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
//--------------------------------------------------
// @brief ���t�g�̃^�C���𓯊������鏈��
//--------------------------------------------------
void LiftGroup::UpdateLiftTilePositions()
{
    DirectX::SimpleMath::Vector3 centerLiftPos    = liftTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition();
    DirectX::SimpleMath::Vector3 centerInitialPos = initialPositions_[tileCenterNum_];
    DirectX::SimpleMath::Vector3 currentOffset    = centerLiftPos - centerInitialPos;

    for (int i = 0; i < liftTiles_.size(); i++)
    {
        DirectX::SimpleMath::Vector3 newPosition = initialPositions_[i] + currentOffset;
        liftTiles_[i]->GetTransformComponent()->SetPosition(newPosition);
    }
}
