//==================================================
// [SmokeInteractionComponent.cpp] 煙やり取りコンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：煙とのやり取りをするコンポーネントの定義
//==================================================
/*----- インクルード -----*/
#include "SmokeInteractionComponent.h"

#include "../../GameObject.h"

#include "../../GameObject/Robot.h"
#include "../../GameObject/Gimmick/Smoke.h"
#include "../../GameObject/Gimmick/SmokePipe.h"

#include "../RigidbodyComponent/VelocityComponent.h"

//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
SmokeInteractionComponent::SmokeInteractionComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
{

	this->Init();
}


//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
SmokeInteractionComponent::~SmokeInteractionComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SmokeInteractionComponent::Init()
{
}
//--------------------------------------------------
// @brief 終了処理
//--------------------------------------------------
void SmokeInteractionComponent::Uninit()
{

}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SmokeInteractionComponent::Update()
{
	if (!current_smoke_) return;	// 現在乗っている煙がない場合は処理を行わない

	auto ownerTransform = owner_->GetTransformComponent();
	auto ownerVelocity = owner_->GetComponent<VelocityComponent>();
	auto pos = ownerTransform->GetPosition();
	auto smokepipe = dynamic_cast<SmokePipe*>(current_smoke_->GetOwnerObj());

	if (smokepipe->GetBrakeFlg())
		if (pos.y <= current_smoke_->GetTransformComponent()->GetPosition().y + current_smoke_->GetTransformComponent()->GetSize().y) {
				ownerVelocity->SetAcceleration({
					0.0f,
					1.0f,
					0.0f 
					});
		}
;
	current_smoke_ = nullptr;
}
