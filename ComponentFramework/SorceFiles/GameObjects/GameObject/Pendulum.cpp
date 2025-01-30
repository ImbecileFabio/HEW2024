//==================================================
// [Pendulum.cpp] 振り子オブジェクト
// 著者：中谷凌也
//--------------------------------------------------
// 説明：振り子の処理を定義
//==================================================

/*----- インクルード -----*/
#include <iostream>
#include <format>

#include "Pendulum.h"
#include "TimeZone.h"
#include "Stick.h"
#include "../../GameManager.h"
#include "../../TileMapManager.h"
#include "../../PemdulumManager.h"

#include "../Component.h"
#include "../Component/RenderComponent/SpriteComponent.h"
#include "../Component/ColliderComponent/CircleColliderComponent.h"
#include "../Component/TransformComponent.h"
#include "../Component/PendulumMovementComponent.h"
#include "../Component/EventComponent/ColliderEventComponent.h"
#include "../Component/ChildrenComponent.h"
#include "../Component/StickMoveComponent.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
Pendulum::Pendulum(GameManager* _gameManager, Vector3 _fulcrum, bool _movement, float _pendulumAngle, LangthState _langthState)
	:GameObject(_gameManager, "Pendulum")
{
	// スプライトコンポーネント
	sprite_component_ = new SpriteComponent(this, "ball");
	// 当たり判定コンポーネント
	collider_component_ = new CircleColliderComponent(this);
	// 振り子コンポーネント
	pendulum_component_ = new PendulumMovementComponent(this);
	// 子タイムゾーン
	time_zone_ = new TimeZone(game_manager_, this);
	// 子スティック
	stick_ = new Stick(game_manager_, this);

	// 子オブジェクト管理コンポーネント
	children_component_ = new ChildrenComponent(this, this);
	children_component_->AddChild(time_zone_);
	children_component_->AddChild(stick_);
	// イベント追加処理
	collider_event_component_ = new ColliderEventComponent(this);
	auto f = std::function<void(GameObject*)>(std::bind(&Pendulum::OnCollisionEnter, this, std::placeholders::_1));
	collider_event_component_->AddEvent(f);

	pendulum_component_->PendulumInit(_fulcrum, _movement, _pendulumAngle);
	pendulum_component_->SetLangthState(static_cast<PendulumMovementComponent::LangthState>(_langthState));
	this->InitGameObject();

	transform_component_->SetSize(TILE_SIZE_X * 1.3, TILE_SIZE_Y * 1.3);
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
Pendulum::~Pendulum(void)
{
	// ここでコンポーネントを削除
	delete sprite_component_;
	delete collider_component_;
	delete pendulum_component_;
	delete children_component_;
	delete collider_event_component_;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Pendulum::InitGameObject(void)
{

}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void Pendulum::UpdateGameObject(void)
{
	// タイムゾーンに振り子が動いているかどうかを渡す
	DirectX::SimpleMath::Vector3 fulcrumPos = pendulum_component_->GetPendulumFulcrum();	// 振り子の支点座標を取得
	float length = pendulum_component_->GetPendulumLength();								// 振り子の長さを取得
	StickMoveComponent* stickMoveComponent = stick_->GetComponent<StickMoveComponent>();
	// タイムゾーンの座標を振り子の支点に合わせる
	time_zone_->GetTransformComponent()->SetPosition(fulcrumPos.x, fulcrumPos.y);
	time_zone_->GetTransformComponent()->SetSize((length + transform_component_->GetSize().x) * 2, (length + transform_component_->GetSize().y) * 2);	// 振り子の長さを半径としてタイムゾーンのサイズを変える

	// タイムゾーンの状態を設定
	time_zone_->SetTimeZoneState(static_cast<TimeZone::TimeZoneState>(pendulum_component_->GetLangthState()));	
	// 棒の状態を設定
	stick_->SetStickLengthState(static_cast<Stick::StickLengthState>(pendulum_component_->GetLangthState()));

	//// 振り子の棒の動きを反映
	//stickMoveComponent->SetStickFulcrum({ fulcrumPos.x, fulcrumPos.y, 0.0f });
	//float pendulumAngle = pendulum_component_->GetPendulumAngle();
	//stickMoveComponent->SetStickAngle(pendulumAngle);
	////// 振り子の棒の座標を計算
	//stickMoveComponent->StickPosition(fulcrumPos, stickMoveComponent->GetStickLength());
}
//--------------------------------------------------
// 当たり判定の実行処理
//--------------------------------------------------
void Pendulum::OnCollisionEnter(GameObject* _other)
{
	bool moveFg = false;
	switch (_other->GetType())
	{
	case GameObject::TypeID::Pendulum:
		moveFg = _other->GetComponent<PendulumMovementComponent>()->GetPendulumMovement();
		// 振り子が止まっていたら
		if ((!moveFg)&&_other->GetComponent<PendulumMovementComponent>()->GetPendulumAngle() == 0)
		{
			// 振り子の動きを開始
			_other->GetComponent<PendulumMovementComponent>()->SetPendulumMovement(true);
			_other->GetComponent<PendulumMovementComponent>()->StartPendulumMovement();
		}
		break;
	default:
		break;
	}
}
//--------------------------------------------------
// @brief 振り子の描画と更新状態を一括で変更
//--------------------------------------------------
void Pendulum::NotDrawAndStopPendulum(void)
{
	game_manager_->GetPendulumManager()->RemoveGameObject(this);	// 振り子マネージャーから振り子を削除
	//game_manager_->GetPendulumManager()->PendulumSearch();

	state_ = State::Dead;
	time_zone_->SetState(State::Dead);
	stick_->SetState(State::Dead);
	sprite_component_->SetState(RenderComponent::State::notDraw);
	time_zone_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
	stick_->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
}
