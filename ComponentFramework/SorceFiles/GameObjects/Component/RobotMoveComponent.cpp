//==================================================
// [RobotMoveComponent.cpp] ロボット移動コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ロボットの挙動を制御するコンポーネントの定義
//==================================================

/*----- インクルード -----*/
#include "RobotMoveComponent.h"

#include "../GameObject.h"
#include "../../GameManager.h"
#include "RigidbodyComponent/VelocityComponent.h"
#include "ColliderComponent/BoxColliderComponent.h"
//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
RobotMoveComponent::RobotMoveComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
	, speed_(20.0f)
	, direction_(Vector2(1.0f, 0.0f))
	, step_scan_distance_(1.0f)
	, max_step_scan_distance_(150.0f)
{

	this->Init();
}


//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
RobotMoveComponent::~RobotMoveComponent()
{
	this->Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void RobotMoveComponent::Init()
{
	direction_ = Vector2(1.0f, 0.0f);
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void RobotMoveComponent::Uninit()
{

}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void RobotMoveComponent::Update()
{
	auto velocity = this->owner_->GetComponent<VelocityComponent>();
	auto collider = this->owner_->GetComponent<BoxColliderComponent>();
	auto transform = this->owner_->GetComponent<TransformComponent>();

	if (!velocity || !collider || !transform)
	{
		std::cout << std::format("[RobotMoveComponent]-> コンポーネントが取得できませんでした\n");
		return; 
	}

	this->CheckTurnAround(*transform, *collider);

	// 進行方向に進む
	velocity->SetVelocity(Vector3(direction_.x * speed_, direction_.y * speed_, 0.0f));

	// 段差をチェック
	auto objects = this->owner_->GetGameManager()->GetGameObjects();
	auto stepHeight = ChackStepHeight(*transform, objects);
}


//--------------------------------------------------
// 進行方向を決める
//--------------------------------------------------
void RobotMoveComponent::CheckTurnAround(const TransformComponent& _transform, const BoxColliderComponent& _collider)
{
	auto pos = _transform.GetPosition();
	auto size = _collider.GetBoxSize();
	// 画面外に出そうになるなら
	if (pos.x < (-960 - size.x / 2))
	{
		direction_ = Vector2(1.0f, 0.0f);
	}
	else if (pos.x > (960 + size.x / 2))
	{
		direction_ = Vector2(-1.0f, 0.0f);
	}
}

// たぶんばぐってます
//--------------------------------------------------
// @brief 段差の高さを調べる
// @param _transform ロボットの姿勢, _gameObjects 環境オブジェクト
// @return 段差の高さ
//--------------------------------------------------
std::optional<float> RobotMoveComponent::ChackStepHeight(const TransformComponent& _transform, const std::vector<GameObject*> _gameObjects)
{
	auto position = _transform.GetPosition();
	Vector2 scanStart = position + Vector2(direction_.x * step_scan_distance_);
	Vector2 scnaEnd = scanStart + Vector2(0, -max_step_scan_distance_);

	float closestStepHeight = max_step_scan_distance_ + 1;	// 初期値： スキャン範囲外を超える値

	for (const auto& obj : _gameObjects) {
		auto boxsize = obj->GetComponent<BoxColliderComponent>()->GetBoxSize();
		// 水平方向に足元のラインが重なっているかチェック
		if (boxsize.y <= scanStart.x && boxsize.z >= scanStart.x) {
			// 段差の高さを計算
			float stepHeight = position.y - boxsize.w;
			if (stepHeight >= 0 && stepHeight <= max_step_height_) {
				closestStepHeight = min(closestStepHeight, stepHeight);
			}
		}
	}

	// 最も近い段差が見つかればその高さを返す
	if (closestStepHeight <= max_step_height_) {
		return closestStepHeight;
	}

	return std::nullopt; // 段差がない
}

