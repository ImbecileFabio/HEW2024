//=================================================================
// [WeakFloorGroup.cpp] WeakFloorGroup�\�[�X�t�@�C��
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����FWeakFloorGroup����
//=================================================================
/*----- �C���N���[�h -----*/
#include "WeakFloorGroup.h"
#include "../WeakFloor.h"
#include "../../../GameObject/Pendulum.h"
#include "../../../Component/PendulumMovementComponent.h"
#include "../../../Component/EventComponent/ColliderEventComponent.h"
#include "../../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../../Component/TimerComponent.h"
//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
WeakFloorGroup::WeakFloorGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "WeakFloorGroup")
	, isWeakFloorBreak_(false)
	, isCenterMedian(false)
	, tileCenterNum_(0)
	, centerPendulum_(nullptr)
	, owner_pendulum_movement_(nullptr)
	, timer_component_(nullptr)
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
WeakFloorGroup::~WeakFloorGroup(void)
{
	delete timer_component_;
}
//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void WeakFloorGroup::InitGameObject(void)
{
	timer_component_ = new TimerComponent(this, 5.0f);
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
		owner_pendulum_movement_->SetPendulumFulcrum(centerPos);
        isCenterMedian = true;
    }		
	// �Ƃ�������ꂽ���ǂ������A�U��q�������Ă���ꍇ
	if (isWeakFloorBreak_ && owner_pendulum_movement_->GetPendulumMovement())
	{
		// �^�C�}�[���J�n
		if (!timer_component_->GetIsActive())
		{
			timer_component_->StartTimer();
		}
		// �^�C�}�[���o�߂��āA�g���K�[�����������ꍇ
		if (timer_component_->GetIsTriggered())
		{
			timer_component_->StopTimer();
			// �O���[�v�̕��ŐƂ��^�C�����ꊇ�ŕύX�������� ���̏����͈�x����
			for (auto& tile : weakFloorTiles_)
			{
				tile->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
				tile->GetComponent<EventBaseComponent>()->RemoveEvent();
				tile->SetState(GameObject::State::Dead);
			}
			auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
			pendulum->NotDrawAndStopPendulum();
		}
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

