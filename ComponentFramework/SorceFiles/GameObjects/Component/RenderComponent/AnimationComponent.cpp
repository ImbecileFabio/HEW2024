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
	, total_frame_(0)
	, current_frame_(0)
	, elapsed_time_(0.0f)
	, frame_duration_(0.5f)
	, is_loop_(true)
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
	is_playing_ = true;
	current_frame_ = 0;
	elapsed_time_ = 0.0f;

	// �e�N�X�`����������擾
	auto texture = sprite_component_->GetTexture();
	frame_duration_ = texture->GetAnmSpeed();
	is_loop_ = texture->GetLoopFlg();
	// ���������瑍�t���[�������v�Z (�Ō�̃t���[���������Ȃ������肷��Ɠ����ɂȂ邩��)
	total_frame_ = texture->GetTotalFrame();

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
			if (is_loop_) {
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
	auto texture = sprite_component_->GetTexture();
	int frameX = current_frame_ % texture->GetCutU();	// ���̕������Ŋ��������܂�
	int frameY = current_frame_ / texture->GetCutU();	// ���̕������Ŋ�������

	Vector2 frameSize = texture->GetFrameSize();

	Vector2 uv = { frameX * frameSize.x, frameY * frameSize.y };

	std::cout << "UV : " << uv.x << ",  " << uv.y << std::endl;
	sprite_component_->SetUV(uv);
}
bool AnimationComponent::GetIsPlaying()
{
	return is_playing_;
}
void AnimationComponent::ResetAnimation()
{
	this->Init();
	UpdateUV();
}
