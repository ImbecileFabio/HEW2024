//=================================================================
// [SmokePipe.cpp] ���M�~�b�N�̃\�[�X�t�@�C��
// ���ҁF�L�n�[��		�ǋL�F���J����
//-----------------------------------------------------------------
// �����F���M�~�b�N�̒�`
//=================================================================
/*----- �C���N���[�h -----*/
#include "SmokePipe.h"
#include "Smoke.h"
#include "../../../AudioManager.h"
#include "../../Component/TransformComponent.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/EventComponent/ColliderEventComponent.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../Component/GimmickComponent/SmokeComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SmokePipe::SmokePipe(GameManager* _gameManager, float _gimmickSize)
	:GameObject(_gameManager, "SmokePipe")
{
	sprite_component_1_ = new SpriteComponent(this, "smoke01");
	smoke_ = new Smoke(_gameManager,this, _gimmickSize);
	sprite_component_2_ = new SpriteComponent(this, "smoke02");
	this->InitGameObject();
}
//--------------------------------------------------
// brief �f�X�g���N�^
//--------------------------------------------------
SmokePipe::~SmokePipe(void)
{
	delete collider_component_;
	delete collider_event_component_;
	delete sprite_component_1_;
	delete sprite_component_2_;
	delete smoke_component_;
}

//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SmokePipe::InitGameObject(void)
{
	collider_component_ = new BoxColliderComponent(this);			// �����蔻��
	collider_event_component_ = new ColliderEventComponent(this);	// �����蔻��C�x���g
	smoke_component_ = new SmokeComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&SmokePipe::OnCollisionStay, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);
	SetBreakFlg(false);
}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SmokePipe::UpdateGameObject(void)
{
	// �^�C���]�[���ɐG��Ă��邩�̔���
	if (smoke_component_->GetTimeZoneHitFlg()) {
		// �^�C���]�[���������Ă��邩�̔���
		if (smoke_component_->GetTimeZoneONFlg()) {
			if (breakFlg_) {
				smoke_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
			}
			else {	// [BRAKE_DEFAULT_TIME]�b��ɔj��i�ҋ@��Ԃ𔲂���j
				fpsCounter_ += smoke_component_->GetTimeSpeed();
				if (fpsCounter_ >= 60.0f * BRAKE_DEFAULT_TIME)
				{
					SetBreakFlg(true);
				}
				smoke_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			}
		}
		else {
			smoke_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
		}
	}
	else {
		if (breakFlg_) smoke_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::draw);
	}

	if ((this->GetBreakFlg() && !smoke_component_->GetTimeZoneHitFlg()) ||
		(this->GetBreakFlg() && smoke_component_->GetTimeZoneHitFlg() && smoke_component_->GetTimeZoneONFlg())) {
		if (!AudioManager::GetInstance()->GetPlayingState(this->GetType(), this->GetObjectFier())) {
			AudioManager::GetInstance()->Play(this->GetType(), this->GetObjectFier());
		}
	}
	else {
		AudioManager::GetInstance()->Stop(this->GetType(), this->GetObjectFier());
	}

	smoke_component_->SetTimeZoneONFlg(false);
	smoke_component_->SetTimeZoneHitFlg(false);
}