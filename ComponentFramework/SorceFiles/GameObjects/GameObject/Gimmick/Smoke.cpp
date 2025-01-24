//=================================================================
// [Smoke.cpp] ���M�~�b�N�̃\�[�X�t�@�C��
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F���M�~�b�N�̒�`
//=================================================================
/*----- �C���N���[�h -----*/
#include "Smoke.h"
#include "../../Component/TransformComponent.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/EventComponent/ColliderEventComponent.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../Component/GimmickComponent/SmokeComponent.h"

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
Smoke::Smoke(GameManager* _gameManager)
	:GameObject(_gameManager, "Smoke")
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief �f�X�g���N�^
//--------------------------------------------------
Smoke::~Smoke(void)
{
	delete collider_component_;
	delete collider_event_component_;
	delete sprite_component_;
	delete smoke_component_;
}

//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void Smoke::InitGameObject(void)
{
	sprite_component_ = new SpriteComponent(this, "smoke01");
	collider_component_ = new BoxColliderComponent(this);			// �����蔻��
	collider_event_component_ = new ColliderEventComponent(this);	// �����蔻��C�x���g
	smoke_component_ = new SmokeComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&Smoke::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);
}

//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void Smoke::UpdateGameObject(void)
{
	// ������i�K�O���Ƀ^�C���]�[���ɐG��Ă��邩�̔���

	if (brakeFlg_) {

	}
	else {	// [BRAKE_DEFAULT_TIME]�b��ɔj��i�ҋ@��Ԃ𔲂���j
		fpsCounter_++;
		if (fpsCounter_ >= 60 * BRAKE_DEFAULT_TIME) brakeFlg_ = true;
	}
}