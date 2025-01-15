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
	Init();
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
AnimationComponent::~AnimationComponent()
{
	Uninit();
}
//--------------------------------------------------
// ����������
//--------------------------------------------------
void AnimationComponent::Init(void)
{
	Sprite_Component_ = dynamic_cast<SpriteComponent*>(sprite_component_);
	fpsCounter = 0;
	anmFlame = 0;
	LoopEnd = false;
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
	auto texture = Sprite_Component_->GetTexture();
	auto vertices = sprite_component_->GetVertices();

	if (!LoopEnd) {
		fpsCounter++;

		if (fpsCounter >= FPS / texture->GetAnmSpeed()) {
			// UV���W���X�V
			texture->SetNumU(texture->GetNumU() + 1);
			if (texture->GetNumU() >= texture->GetCutU()) {
				texture->SetNumU(0);
				texture->SetNumV(texture->GetNumV() + 1);
				if (texture->GetNumV() >= texture->GetCutV()) {
					texture->SetNumV(0);
				}
			}

			// UV���W���Z�b�g
			vertices[0].uv = Vector2(texture->GetNumU() / texture->GetCutU(), texture->GetNumV() / texture->GetCutV());
			vertices[1].uv = Vector2((texture->GetNumU() + 1.0f) / texture->GetCutU(), texture->GetNumV() / texture->GetCutV());
			vertices[2].uv = Vector2(texture->GetNumU() / texture->GetCutU(), (texture->GetNumV() + 1.0f) / texture->GetCutV());
			vertices[3].uv = Vector2((texture->GetNumU() + 1.0f) / texture->GetCutU(), (texture->GetNumV() + 1.0f) / texture->GetCutV());
			// �o�b�t�@����������
			sprite_component_->SetVertexBuffer(vertices);

			// ���[�v����
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