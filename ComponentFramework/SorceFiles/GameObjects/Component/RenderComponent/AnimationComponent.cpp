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
	Init();
}
//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
AnimationComponent::~AnimationComponent()
{
	Uninit();
}
//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void AnimationComponent::Init(void)
{
	Sprite_Component_ = dynamic_cast<SpriteComponent*>(sprite_component_);
	fpsCounter = 0;
	anmFlame = 0;
	LoopEnd = false;
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
	auto texture = Sprite_Component_->GetTexture();
	auto vertices = sprite_component_->GetVertices();

	if (!LoopEnd) {
		fpsCounter++;

		if (fpsCounter >= FPS / texture->GetAnmSpeed()) {
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
			vertices[0].uv = Vector2(texture->GetNumU() / texture->GetCutU(), texture->GetNumV() / texture->GetCutV());
			vertices[1].uv = Vector2((texture->GetNumU() + 1.0f) / texture->GetCutU(), texture->GetNumV() / texture->GetCutV());
			vertices[2].uv = Vector2(texture->GetNumU() / texture->GetCutU(), (texture->GetNumV() + 1.0f) / texture->GetCutV());
			vertices[3].uv = Vector2((texture->GetNumU() + 1.0f) / texture->GetCutU(), (texture->GetNumV() + 1.0f) / texture->GetCutV());
			// バッファを書き換え
			sprite_component_->SetVertexBuffer(vertices);

			// ループ判定
			if (!(texture->GetLoopFlg())) {
				anmFlame++;
				if (anmFlame >= (texture->GetCutU() * texture->GetCutV()) - 1) {
					LoopEnd = true;
				}
			}

			fpsCounter = 0;
		}
	}
}