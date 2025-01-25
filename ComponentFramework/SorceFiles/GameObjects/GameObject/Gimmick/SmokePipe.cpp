//=================================================================
// [SmokePipe.cpp] ���M�~�b�N�̃\�[�X�t�@�C��
// ���ҁF�L�n�[��		�ǋL�F���J����
//-----------------------------------------------------------------
// �����F���M�~�b�N�̒�`
//=================================================================
/*----- �C���N���[�h -----*/
#include "SmokePipe.h"
#include "../../Component/TransformComponent.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/EventComponent/ColliderEventComponent.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../Component/GimmickComponent/SmokeComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SmokePipe::SmokePipe(GameManager* _gameManager)
	:GameObject(_gameManager, "SmokePipe")
{
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
	sprite_component_1_ = new SpriteComponent(this, "smoke01");
	sprite_component_2_ = new SpriteComponent(this, "smoke02");
	collider_component_ = new BoxColliderComponent(this);			// �����蔻��
	collider_event_component_ = new ColliderEventComponent(this);	// �����蔻��C�x���g
	smoke_component_ = new SmokeComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&SmokePipe::OnCollisionStay, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);
}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SmokePipe::UpdateGameObject(void)
{
	// ������i�K�O���Ƀ^�C���]�[���ɐG��Ă��邩�̔���

	if (brakeFlg_) {

	}
	else {	// [BRAKE_DEFAULT_TIME]�b��ɔj��i�ҋ@��Ԃ𔲂���j
		fpsCounter_++;
		if (fpsCounter_ >= 60 * BRAKE_DEFAULT_TIME) brakeFlg_ = true;
	}
}

void SmokePipe::OnCollisionStay(GameObject* _other) {

}