//=================================================================
// [Effect.cpp] Effectソースファイル
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：Effectです
// まだ触っている途中です
//=================================================================

/*----- インクルード -----*/
#include "Effect.h"

#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/RenderComponent/AnimationComponent.h"
#include "../Component/TimerComponent.h"

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
Effect::Effect(GameManager* _gameManager, const std::string& _effectTex)
	:GameObject(_gameManager, "Effect")
{
	sprite_component_ = new SpriteComponent(this, _effectTex);
	animation_component_ = new AnimationComponent(this, sprite_component_);

	auto texture = sprite_component_->GetTexture();
	auto triggerTime = texture->GetAnmSpeed() * texture->GetCutU() * texture->GetCutV();	// 総フレーム数を取得する関数に変更予定

	timer_component_ = new TimerComponent(this, triggerTime);

	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
Effect::~Effect(void)
{

}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void Effect::InitGameObject(void)
{

}

//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void Effect::UpdateGameObject(void)
{

}

