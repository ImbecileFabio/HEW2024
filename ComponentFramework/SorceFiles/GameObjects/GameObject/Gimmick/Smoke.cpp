//=================================================================
// [SmokePipe.cpp] ���M�~�b�N�̉��{�̂̃\�[�X�t�@�C��
// ���ҁF���J����
//-----------------------------------------------------------------
// �����F���M�~�b�N�̒�`
//=================================================================

#include "Smoke.h"
#include "../../Component/TransformComponent.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/EventComponent/ColliderEventComponent.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../Component/RenderComponent/AnimationComponent.h"

#include "../../Component/RenderComponent/DebugColliderDrawComponent.h"

//--------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
//--------------------------------------------------
Smoke::Smoke(GameManager* _gameManager, float _gimmickSize)
	:GameObject(_gameManager, "Smoke")
	, m_gimmickSize(_gimmickSize)
{
	InitGameObject();
}
Smoke::~Smoke() {
	delete sprite_component_;
	delete collider_component_;
	delete collider_event_component_;
	delete animation_component_;
}

//--------------------------------------------------
// ������
//--------------------------------------------------
void Smoke::InitGameObject() {
	sprite_component_ = new SpriteComponent(this,"smoke00");
	collider_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	animation_component_ = new AnimationComponent(sprite_component_, this);

	auto debug = new DebugColliderDrawComponent(this);

	auto f = std::function<void(GameObject*)>(std::bind(&Smoke::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	sprite_component_->GetTexture()->SetOffsetSize({ 1.0f,m_gimmickSize });
	sprite_component_->GetTexture()->SetOffsetPos({ 0.0f,10.0f + (m_gimmickSize - 1.0f) * 28.0f });
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void Smoke::UpdateGameObject() {
}


void Smoke::OnCollisionEnter(GameObject* _other) {
}