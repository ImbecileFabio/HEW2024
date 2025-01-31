//=================================================================
// [Effect.cpp] Effectソースファイル
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：Effectです
// まだ触っている途中です
//=================================================================

/*----- インクルード -----*/
#include "Effect.h"

#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/RenderComponent/AnimationComponent.h"

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
Effect::Effect(GameManager* _gameManager, GameObject* _owner, const std::string& _effectTex)
	:GameObject(_gameManager, "Effect")
	, is_finish_(false)
	, owner_(_owner)
{

	sprite_component_ = new SpriteComponent(this, _effectTex);
	animation_component_ = new AnimationComponent(this, sprite_component_);
	transform_component_->SetPosition(owner_->GetTransformComponent()->GetPosition());


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
	// アニメーションが終了終了フラグをオンに
	if (!animation_component_->GetIsPlaying())
	{
		//is_finish_ = true;
		delete this;
	}
}

