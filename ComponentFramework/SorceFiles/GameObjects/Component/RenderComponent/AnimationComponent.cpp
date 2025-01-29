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
	is_playing_ = true;
	current_frame_ = 0;
	elapsed_time_ = 0.0f;

	// テクスチャから情報を取得
	auto texture = sprite_component_->GetTexture();
	frame_duration_ = texture->GetAnmSpeed();
	is_loop_ = texture->GetLoopFlg();
	// 分割数から総フレーム数を計算 (最後のフレームが何もなかったりすると透明になるかも)
	total_frame_ = texture->GetTotalFrame();

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
			if (is_loop_) {
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
	auto texture = sprite_component_->GetTexture();
	int frameX = current_frame_ % texture->GetCutU();	// 横の分割数で割ったあまり
	int frameY = current_frame_ / texture->GetCutU();	// 横の分割数で割った商

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
