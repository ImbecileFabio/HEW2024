//=================================================================
// [Smoke.cpp] 煙ギミックのソースファイル
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：煙ギミックの定義
//=================================================================
/*----- インクルード -----*/
#include "Smoke.h"
#include "../../Component/TransformComponent.h"
#include "../../Component/RenderComponent/SpriteComponent.h"
#include "../../Component/EventComponent/ColliderEventComponent.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../Component/GimmickComponent/SmokeComponent.h"

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
Smoke::Smoke(GameManager* _gameManager)
	:GameObject(_gameManager, "Smoke")
{
	this->InitGameObject();
}
//--------------------------------------------------
// brief デストラクタ
//--------------------------------------------------
Smoke::~Smoke(void)
{
	delete collider_component_;
	delete collider_event_component_;
	delete sprite_component_;
	delete smoke_component_;
}

//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void Smoke::InitGameObject(void)
{
	sprite_component_ = new SpriteComponent(this, "smoke01");
	collider_component_ = new BoxColliderComponent(this);			// 当たり判定
	collider_event_component_ = new ColliderEventComponent(this);	// 当たり判定イベント
	smoke_component_ = new SmokeComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&Smoke::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);
}

//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void Smoke::UpdateGameObject(void)
{
	// もう一段階外側にタイムゾーンに触れているかの判定

	if (brakeFlg_) {

	}
	else {	// [BRAKE_DEFAULT_TIME]秒後に破壊（待機状態を抜ける）
		fpsCounter_++;
		if (fpsCounter_ >= 60 * BRAKE_DEFAULT_TIME) brakeFlg_ = true;
	}
}