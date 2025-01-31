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
Smoke::Smoke(GameManager* _gameManager,GameObject* _ownerObj, float _gimmickSize)
	:GameObject(_gameManager, "Smoke")
	,m_ownerObj(_ownerObj)
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
	sprite_component_ = new SpriteComponent(this,"smoke00", 21);
	collider_component_ = new BoxColliderComponent(this);
	collider_event_component_ = new ColliderEventComponent(this);
	animation_component_ = new AnimationComponent(this, sprite_component_);


	auto f = std::function<void(GameObject*)>(std::bind(&Smoke::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	auto transform = this->GetTransformComponent();
	m_smokeSize = transform->GetSize().y;
	transform->SetSize(transform->GetSize().x, transform->GetSize().y * m_gimmickSize);

}

//--------------------------------------------------
// ����
//--------------------------------------------------
void Smoke::UpdateGameObject() {
	auto transform = this->GetTransformComponent();
	transform->SetPosition(m_ownerObj->GetTransformComponent()->GetPosition().x,
		m_ownerObj->GetTransformComponent()->GetPosition().y + (m_smokeSize * (m_gimmickSize - 1) / 2));
	collider_component_->SetSize(Vector3(this->GetTransformComponent()->GetSize().x,
		this->GetTransformComponent()->GetSize().y - 10.0f,
		this->GetTransformComponent()->GetSize().z));
}