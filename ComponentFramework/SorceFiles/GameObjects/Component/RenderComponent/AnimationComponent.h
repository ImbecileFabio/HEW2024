//==================================================
// [AnimationComponent.h] �A�j���[�V�����R���|�[�l���g
// ���ҁF����仓�
//--------------------------------------------------
// �����F�A�j���[�V�����R���|�[�l���g�̐錾
//==================================================
#ifndef ANIMATION_COMPONENT_H_
#define ANIMATION_COMPONENT_H_
#include "../../Component.h"
class AnimationComponent : public Component
{
public:
	AnimationComponent(class SpriteComponent* _spriteComponent, GameObject* _owner);
	~AnimationComponent();
	void Init(void)   override;
	void Uninit(void) override;
	void Update(void) override;
	TypeID GetComponentType(void) const override { return TypeID::AnimationComponent; }
private:
	SpriteComponent* sprite_component_{};	// �A�j���[�V����������X�v���C�g�̎Q�Ƃ�����
};

#endif // ANIMATION_COMPONENT_H_