//=================================================================
// [WeakFloorGroup.cpp] WeakFloorGroup�\�[�X�t�@�C��
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����FWeakFloorGroup����
//=================================================================
/*----- �C���N���[�h -----*/
#include "WeakFloorGroup.h"
#include "WeakFloor.h"
#include "../../GameObject/Pendulum.h"
#include "../../Component/PendulumMovementComponent.h"
#include "../../Component/EventComponent/ColliderEventComponent.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
WeakFloorGroup::WeakFloorGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "WeakFloorGroup")
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
WeakFloorGroup::~WeakFloorGroup(void)
{
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void WeakFloorGroup::InitGameObject(void)
{
}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void WeakFloorGroup::UpdateGameObject(void)
{
    // �U��q�𒆐S�ɒ������鏈��
    if (!isCenterMedian)
    {
        size_t size = weakFloorTiles_.size();
        if (size == 0)
        {
            // �^�C�������݂��Ȃ��ꍇ�͏������X�L�b�v
            return;
        }

        DirectX::SimpleMath::Vector3 centerPos;

        if (size % 2 == 0) // ����
        {
            // ���S2�̃^�C���̃C���f�b�N�X���v�Z
            size_t leftIndex = (size / 2) - 1;
            size_t rightIndex = size / 2;

            // ���S2�̃^�C���̈ʒu���擾���A���ς��v�Z
            DirectX::SimpleMath::Vector3 leftPos = weakFloorTiles_[leftIndex]->GetTransformComponent()->GetPosition();
            DirectX::SimpleMath::Vector3 rightPos = weakFloorTiles_[rightIndex]->GetTransformComponent()->GetPosition();
            centerPos = (leftPos + rightPos) / 2.0f;
        }
        else // �
        {
            // ���S�̃^�C���̃C���f�b�N�X���v�Z
            size_t centerIndex = size / 2;

            // ���S�̃^�C���̈ʒu���擾
            centerPos = weakFloorTiles_[centerIndex]->GetTransformComponent()->GetPosition();
        }

        // �U��q�̒��S��ݒ�
        centerPendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(centerPos);
        isCenterMedian = true;
    }
	// �Ƃ�������ꂽ���ǂ������A�U��q�������Ă���ꍇ
	if (isWeakFloorBreak_ && owner_pendulum_movement_->GetPendulumMovement())
	{
		// �O���[�v�̕��ŐƂ��^�C�����ꊇ�ŕύX�������� ���̏����͈�x����
		for (auto& tile : weakFloorTiles_)
		{
			tile->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			tile->GetComponent<EventBaseComponent>()->RemoveEvent();
			tile->SetState(GameObject::State::Paused);
		}
		auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
		pendulum->NotDrawAndStopPendulum();
    }
}
//--------------------------------------------------
// @brief �Ƃ����^�C����ǉ�
// @param _tile[�ǉ�����^�C���I�u�W�F�N�g]
//--------------------------------------------------
void WeakFloorGroup::AddWeakFloorTile(GameObject* _tile)
{
	weakFloorTiles_.emplace_back(_tile);
	auto weakFloor = dynamic_cast<WeakFloor*>(_tile);
	weakFloor->SetWeakFloorGroup(this);
}
//--------------------------------------------------
// @brief �M�~�b�N�ƘA������U��q��ݒ�A�U��q�̃R���|�[�l���g���L���b�V��
// @param _centerPendulum[�U��q�I�u�W�F�N�g]
//--------------------------------------------------
void WeakFloorGroup::SetPendulumANDMovement(GameObject* _centerPendulum)
{
	centerPendulum_ = _centerPendulum;
	// �U��q�̃R���|�[�l���g���擾���Ă���
	owner_pendulum_movement_ = centerPendulum_->GetComponent<PendulumMovementComponent>();
}

