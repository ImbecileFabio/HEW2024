//==================================================
// [AnimationComponent.h] アニメーションコンポーネント
// 著者：
//--------------------------------------------------
// 説明：アニメーションコンポーネントの宣言
//==================================================
#ifndef ANIMATION_COMPONENT_H_
#define ANIMATION_COMPONENT_H_
#include "../../Component.h"


class SpriteComponent;
class Texture;

class AnimationComponent : public Component
{
public:
	AnimationComponent(GameObject* _owner, SpriteComponent* _spriteComponent, int _updateOrder = 80);
	~AnimationComponent();
	void Init(void)   override;
	void Uninit(void) override;
	void Update(void) override;
	TypeID GetComponentType(void) const override { return TypeID::AnimationComponent; }

	void PlayAnimation();
	void StopAnimation();

	void ResetAnimation();

	void UpdateUV();

	bool GetIsPlaying();
private:
	SpriteComponent* sprite_component_{};	// アニメーションをするスプライトの参照を持つ

	int total_frame_;	// 総フレーム数

	int current_frame_;		// 現在のフレーム
	float elapsed_time_;	// 経過時間
	float frame_duration_;	// 1フレームの時間
	bool is_loop_;			// ループするかどうか
	bool is_playing_;		// アニメーションを再生中かどうか
};

#endif // ANIMATION_COMPONENT_H_