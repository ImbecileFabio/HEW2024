//==================================================
// [AnimationComponent.h] アニメーションコンポーネント
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：アニメーションコンポーネントの宣言
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
	SpriteComponent* sprite_component_{};	// アニメーションをするスプライトの参照を持つ
};

#endif // ANIMATION_COMPONENT_H_