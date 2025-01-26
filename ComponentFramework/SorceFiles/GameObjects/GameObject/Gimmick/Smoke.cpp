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

//--------------------------------------------------
// �R���X�g���N�^/�f�X�g���N�^
//--------------------------------------------------
Smoke::Smoke(GameManager* _gameManager) 
	:GameObject(_gameManager, "Smoke")
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
}

//--------------------------------------------------
// ����
//--------------------------------------------------
void Smoke::UpdateGameObject() {
}