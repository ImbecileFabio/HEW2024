//=================================================================
// [EffectBase.cpp] EffectBaseソースファイル
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：EffectBaseです
// まだ触っている途中です
//=================================================================

/*----- インクルード -----*/
#include "EffectBase.h"

#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/RenderComponent/AnimationComponent.h"
#include "../Component/TimerComponent.h"

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
EffectBase::EffectBase(GameManager* _gameManager, const std::string& _effectTex)
	:GameObject(_gameManager, "EffectBase")
{
	sprite_component_ = new SpriteComponent(this, _effectTex);
	animation_component_ = new AnimationComponent(this, sprite_component_);

	auto texture = sprite_component_->GetTexture();
	auto triggerTime = texture->GetTottalFrame() * texture->GetAnmSpeed();

	timer_component_ = new TimerComponent(this, triggerTime);

	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
EffectBase::~EffectBase(void)
{

}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void EffectBase::InitGameObject(void)
{

}

//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void EffectBase::UpdateGameObject(void)
{

}

