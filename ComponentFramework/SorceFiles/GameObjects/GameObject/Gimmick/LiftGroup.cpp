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
    // �U��q�𒆐S�ɒ������鏈��
    if (!isCenterMedian)
    {
        size_t size = liftTiles_.size();
        if (size == 0)
        {
            // �^�C�������݂��Ȃ��ꍇ�͏������X�L�b�v
            return;
        }

        // ���t�g���ꊇ�ŕύX���邽�߂̃L���b�V��
        for (auto& tile : liftTiles_)
        {
            owner_lift_components_.push_back(tile->GetComponent<LiftComponent>());
        }

        DirectX::SimpleMath::Vector3 centerPos;

        if (size % 2 == 0) // ����
        {
            // ���S2�̃^�C���̃C���f�b�N�X���v�Z
            size_t leftIndex = (size / 2) - 1;
            size_t rightIndex = size / 2;
            // �Y������ۑ�
            tileCenterNum_ = leftIndex;
            // ���S2�̃^�C���̈ʒu���擾���A���ς��v�Z
            DirectX::SimpleMath::Vector3 leftPos = liftTiles_[leftIndex] ->GetTransformComponent()->GetPosition();
            DirectX::SimpleMath::Vector3 rightPos = liftTiles_[rightIndex]->GetTransformComponent()->GetPosition();
            centerPos = (leftPos + rightPos) / 2.0f;
            // ���S���t�g�ƃR���|�[�l���g�����ɐU��q��ݒ�
            auto lift = dynamic_cast<Lift*>(liftTiles_[leftIndex]);
			auto liftComponent = lift->GetComponent<LiftComponent>();
            auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
            lift->SetPendulum(pendulum);
            liftComponent->SetPendulum(pendulum);
        }
        else // �
        {
            // ���S�̃^�C���̃C���f�b�N�X���v�Z
            size_t centerIndex = size / 2;
            // �Y������ۑ�
			tileCenterNum_ = centerIndex;
            // ���S�̃^�C���̈ʒu���擾
            centerPos = liftTiles_[centerIndex]->GetTransformComponent()->GetPosition();
			// ���S���t�g�ƃR���|�[�l���g�����ɐU��q��ݒ�
            auto lift = dynamic_cast<Lift*>(liftTiles_[centerIndex]);
            auto liftComponent = lift->GetComponent<LiftComponent>();
            auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
            lift->SetPendulum(pendulum);
            liftComponent->SetPendulum(pendulum);
        }
        // �U��q�̒��S��ݒ�
        centerPendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(centerPos);
        isCenterMedian = true;
    }
    // �U��q�������Ă���ꍇ
    if (owner_pendulum_movement_->GetPendulumMovement())
    {
		DirectX::SimpleMath::Vector3 centerLiftPos = liftTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition();
        // �e�^�C���̃I�t�Z�b�g���v�Z���Ĉꊇ�ňړ�
        for (auto& tile : liftTiles_)
        {
            DirectX::SimpleMath::Vector3 currentPos = tile->GetTransformComponent()->GetPosition();
            float yOffset = centerLiftPos.y - currentPos.y; // ���S�ʒu�Ƃ̃I�t�Z�b�g���v�Z
            float xOffset = centerLiftPos.x - currentPos.x; // ���S�ʒu�Ƃ̃I�t�Z�b�g���v�Z
            tile->GetTransformComponent()->SetPosition(currentPos.x + xOffset, currentPos.y + yOffset);
        }
        // �U��q�̒��S�_���X�V
        DirectX::SimpleMath::Vector3 newPendulumPos = centerLiftPos;
        centerPendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(newPendulumPos);
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


