//==================================================
// [SmokeInteractionComponent.cpp] �������R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���Ƃ̂���������R���|�[�l���g�̒�`
//==================================================
/*----- �C���N���[�h -----*/
#include "SmokeInteractionComponent.h"

#include "../../GameObject.h"

#include "../../GameObject/Robot.h"
#include "../../GameObject/Gimmick/Smoke.h"
#include "../../GameObject/Gimmick/SmokePipe.h"

#include "../RigidbodyComponent/VelocityComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SmokeInteractionComponent::SmokeInteractionComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{

	this->Init();
}


//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
SmokeInteractionComponent::~SmokeInteractionComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SmokeInteractionComponent::Init()
{
}
//--------------------------------------------------
// @brief �I������
//--------------------------------------------------
void SmokeInteractionComponent::Uninit()
{

}
//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SmokeInteractionComponent::Update()
{
	if (!current_smoke_) return;	// ���ݏ���Ă��鉌���Ȃ��ꍇ�͏������s��Ȃ�

	auto ownerTransform = owner_->GetTransformComponent();
	auto ownerVelocity = owner_->GetComponent<VelocityComponent>();
	auto pos = ownerTransform->GetPosition();
	auto smokepipe = dynamic_cast<SmokePipe*>(current_smoke_->GetOwnerObj());

	if (smokepipe->GetBrakeFlg())
		if (pos.y <= current_smoke_->GetTransformComponent()->GetPosition().y + current_smoke_->GetTransformComponent()->GetSize().y) {
				ownerVelocity->SetAcceleration({
					0.0f,
					1.0f,
					0.0f 
					});
		}
;
	current_smoke_ = nullptr;
}
