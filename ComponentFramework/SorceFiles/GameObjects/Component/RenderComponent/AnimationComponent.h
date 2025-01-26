//==================================================
// [AnimationComponent.h] �A�j���[�V�����R���|�[�l���g
// ���ҁF����仓�		�ǋL�F���J����
//--------------------------------------------------
// �����F�A�j���[�V�����R���|�[�l���g�̐錾
//==================================================
#ifndef ANIMATION_COMPONENT_H_
#define ANIMATION_COMPONENT_H_
#include "../../Component.h"

#define FPS 60

class RenderComponent;
class SpriteComponent;

class AnimationComponent : public Component
{
public:
	AnimationComponent(RenderComponent* _spriteComponent, GameObject* _owner);
	~AnimationComponent();
	void Init(void)   override;
	void Uninit(void) override;
	void Update(void) override;
	TypeID GetComponentType(void) const override { return TypeID::AnimationComponent; }

	auto GetLoopEnd() { return LoopEnd; }
private:
	RenderComponent* sprite_component_{};	// �A�j���[�V����������X�v���C�g�̎Q�Ƃ�����
	SpriteComponent* Sprite_Component_{};	// �_�C�i�~�b�N�L���X�g�p

	int fpsCounter;	// FPS�J�E���^
	int anmFlame;	// �A�j���[�V�����t���[��
	bool LoopEnd;	// ���[�v�I���t���O
};

#endif // ANIMATION_COMPONENT_H_