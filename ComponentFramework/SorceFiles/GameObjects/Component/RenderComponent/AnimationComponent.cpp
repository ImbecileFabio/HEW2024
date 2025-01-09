#include "AnimationComponent.h"
#include "../RenderComponent/SpriteComponent.h"
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
AnimationComponent::AnimationComponent(RenderComponent* _spriteComponent, GameObject* _owner)
	: Component(_owner)
	, sprite_component_(_spriteComponent)
{
	sprite_component_
}
//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
AnimationComponent::~AnimationComponent()
{
	delete sprite_component_;
}
//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void AnimationComponent::Init(void)
{

}
//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void AnimationComponent::Uninit(void)
{

}
//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void AnimationComponent::Update(void)
{
	
}