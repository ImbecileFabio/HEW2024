#include "AnimationComponent.h"
#include "../RenderComponent/SpriteComponent.h"
#include <SimpleMath.h>
using namespace DirectX::SimpleMath;
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
AnimationComponent::AnimationComponent(SpriteComponent* _spriteComponent, GameObject* _owner)
	: Component(_owner)
	, sprite_component_(_spriteComponent)
{
	Init();
}
//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
AnimationComponent::~AnimationComponent()
{
	Uninit();
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
	auto texture = sprite_component_->GetTexture();
	auto vertices = sprite_component_->GetVertices();

	// UV座標を更新
	texture->SetNumU(texture->GetNumU() + 1);
	if (texture->GetNumU() >= texture->GetCutU()) {
		texture->SetNumU(0);
		texture->SetNumV(texture->GetNumV() + 1);
		if (texture->GetNumV() >= texture->GetCutV()) {
			texture->SetNumV(0);
		}
	}

	// UV座標をセット
	vertices[0].uv = Vector2(texture->GetNumU()     / texture->GetCutU(), texture->GetNumV()     / texture->GetCutV());
	vertices[1].uv = Vector2(texture->GetNumU() + 1 / texture->GetCutU(), texture->GetNumV()     / texture->GetCutV());
	vertices[2].uv = Vector2(texture->GetNumU()     / texture->GetCutU(), texture->GetNumV() + 1 / texture->GetCutV());
	vertices[3].uv = Vector2(texture->GetNumU() + 1 / texture->GetCutU(), texture->GetNumV() + 1 / texture->GetCutV());
}