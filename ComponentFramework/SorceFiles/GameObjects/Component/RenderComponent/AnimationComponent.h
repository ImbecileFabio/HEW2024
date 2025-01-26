//==================================================
// [AnimationComponent.h] アニメーションコンポーネント
// 著者：尾上莉奈		追記：中谷凌也
//--------------------------------------------------
// 説明：アニメーションコンポーネントの宣言
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
	RenderComponent* sprite_component_{};	// アニメーションをするスプライトの参照を持つ
	SpriteComponent* Sprite_Component_{};	// ダイナミックキャスト用

	int fpsCounter;	// FPSカウンタ
	int anmFlame;	// アニメーションフレーム
	bool LoopEnd;	// ループ終了フラグ
};

#endif // ANIMATION_COMPONENT_H_