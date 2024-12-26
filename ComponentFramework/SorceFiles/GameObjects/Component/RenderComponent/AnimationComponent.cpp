#include "AnimationComponent.h"
#include "../RenderComponent/SpriteComponent.h"
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
AnimationComponent::AnimationComponent(RenderComponent* _spriteComponent, GameObject* _owner)
	: Component(_owner)
	, sprite_component_(_spriteComponent)
{
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
AnimationComponent::~AnimationComponent()
{
	delete sprite_component_;
}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void AnimationComponent::Init(void)
{
}
//--------------------------------------------------
// �I������
//--------------------------------------------------
void AnimationComponent::Uninit(void)
{
}
//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void AnimationComponent::Update(void)
{
	//sprite_component_->SetUV(Vector2(5.0f, 5.0f));
}