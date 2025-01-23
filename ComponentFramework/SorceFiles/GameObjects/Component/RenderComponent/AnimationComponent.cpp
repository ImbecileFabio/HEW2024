//==================================================
// [AnimationComponent.cpp] �A�j���[�V�����R���|�[�l���g
// ���ҁF
//--------------------------------------------------
// �����FUV���W���v�Z����R���|�[�l���g
//==================================================
#include <SimpleMath.h>
#include <iostream>

#include "AnimationComponent.h"
#include "SpriteComponent.h"
using namespace DirectX::SimpleMath;
//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
AnimationComponent::AnimationComponent(GameObject* _owner, SpriteComponent* _spriteComponent)
	: Component(_owner)
	, sprite_component_(_spriteComponent)
	, frame_count_x_(0)
	, frame_count_y_(0)
	, total_frame_(0)
	, current_frame_(0)
	, elapsed_time_(0.0f)
	, frame_duration_(0.5f)
	, loop_(true)
	, is_playing_(true)
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
	texture_ = sprite_component_->GetTexture();
	frame_count_x_ = texture_->GetCutU();
	frame_count_y_ = texture_->GetCutV();
	frame_duration_ = texture_->GetAnmSpeed();

	total_frame_ = frame_count_x_ * frame_count_y_;
	current_frame_ = 0;
	
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
    if (!is_playing_) return;

	elapsed_time_ += delta_time_;

	// �o�ߎ��Ԃ���������
	if (elapsed_time_ >= frame_duration_) {
		elapsed_time_ -= frame_duration_;

		++current_frame_;
		// ���t���[�����𒴂�����
		if (current_frame_ >= total_frame_) {
			if (loop_) {
				// ���[�v����
				current_frame_ = 0;	
			}
			else {
				// ��~��Ԃ��ێ�����
				current_frame_ = total_frame_ - 1;
				is_playing_ = false;
			}
		}

		// UV���W���v�Z
		UpdateUV();

	}


}
//--------------------------------------------------
// @brief �A�j���[�V�����Đ�
//--------------------------------------------------
void AnimationComponent::PlayAnimation()
{
	is_playing_ = true;
	ResetAnimation();
}
//--------------------------------------------------
// @brief �A�j���[�V������~
//--------------------------------------------------
void AnimationComponent::StopAnimation()
{
	is_playing_ = false;
}

//--------------------------------------------------
// @brief UV���W���X�V
//--------------------------------------------------
void AnimationComponent::UpdateUV()
{
	int frameX = current_frame_ % frame_count_x_;
	int frameY = current_frame_ / frame_count_y_;

	Vector2 uv;
	uv.x = static_cast<float>(frameX) / frame_count_x_;
	uv.y = static_cast<float>(frameY) / frame_count_y_;

	std::cout << "UV: (" << uv.x << ", " << uv.y << ")\n";

	sprite_component_->SetUV(uv);
}

void AnimationComponent::ResetAnimation()
{
	current_frame_ = 0;
	elapsed_time_ = 0.0f;
	UpdateUV();
}
