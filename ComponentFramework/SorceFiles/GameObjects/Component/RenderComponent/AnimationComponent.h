//==================================================
// [AnimationComponent.h] �A�j���[�V�����R���|�[�l���g
// ���ҁF
//--------------------------------------------------
// �����F�A�j���[�V�����R���|�[�l���g�̐錾
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
	SpriteComponent* sprite_component_{};	// �A�j���[�V����������X�v���C�g�̎Q�Ƃ�����

	int total_frame_;	// ���t���[����

	int current_frame_;		// ���݂̃t���[��
	float elapsed_time_;	// �o�ߎ���
	float frame_duration_;	// 1�t���[���̎���
	bool is_loop_;			// ���[�v���邩�ǂ���
	bool is_playing_;		// �A�j���[�V�������Đ������ǂ���
};

#endif // ANIMATION_COMPONENT_H_