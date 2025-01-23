//==================================================
// [AnimationComponent.cpp] アニメーションコンポーネント
// 著者：
//--------------------------------------------------
// 説明：UV座標を計算するコンポーネント
//==================================================
#include <SimpleMath.h>
#include <iostream>

#include "AnimationComponent.h"
#include "SpriteComponent.h"
using namespace DirectX::SimpleMath;
//--------------------------------------------------
// コンストラクタ
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
	texture_ = sprite_component_->GetTexture();
	frame_count_x_ = texture_->GetCutU();
	frame_count_y_ = texture_->GetCutV();
	frame_duration_ = texture_->GetAnmSpeed();

	total_frame_ = frame_count_x_ * frame_count_y_;
	current_frame_ = 0;
	
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
    if (!is_playing_) return;

	elapsed_time_ += delta_time_;

	// 経過時間が超えたら
	if (elapsed_time_ >= frame_duration_) {
		elapsed_time_ -= frame_duration_;

		++current_frame_;
		// 総フレーム数を超えたら
		if (current_frame_ >= total_frame_) {
			if (loop_) {
				// ループする
				current_frame_ = 0;	
			}
			else {
				// 停止状態を維持する
				current_frame_ = total_frame_ - 1;
				is_playing_ = false;
			}
		}

		// UV座標を計算
		UpdateUV();

	}


}
//--------------------------------------------------
// @brief アニメーション再生
//--------------------------------------------------
void AnimationComponent::PlayAnimation()
{
	is_playing_ = true;
	ResetAnimation();
}
//--------------------------------------------------
// @brief アニメーション停止
//--------------------------------------------------
void AnimationComponent::StopAnimation()
{
	is_playing_ = false;
}

//--------------------------------------------------
// @brief UV座標を更新
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
