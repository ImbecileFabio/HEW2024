//==================================================
// [RobotMoveComponent.cpp] ロボット移動コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ロボットの挙動を制御するコンポーネントの定義
//==================================================

/*----- インクルード -----*/
#include <memory>

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
	, speed_(1.0f)
	, direction_(Vector2(1.0f, 0.0f))
	, max_step_height_(100.0f)
	, step_scan_distance_(1.0f)
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
	auto transform = this->owner_->GetTransformComponent();

	if (!velocity || !collider || !transform)
	{
		std::cout << std::format("[RobotMoveComponent]-> コンポーネントが取得できませんでした\n");
		return; 
	}

	// 段差をチェック
	auto objects = this->owner_->GetGameManager()->GetGameObjects();
	auto stepHeightOpt = CheckStepHeight(*transform, collider->GetSize(), objects);

	// 段差がある場合
	if (stepHeightOpt.has_value()) {
		float stepHeight = stepHeightOpt.value();
		// 段差が最大値以下なら
		if (std::abs(stepHeight) <= max_step_height_) {
			// 段差を上るor降りる
			auto pos = transform->GetPosition();
			transform->SetPosition(Vector3(pos.x, pos.y + stepHeight, pos.z));
		}
		// 段差が最大値を超える場合
		else {
			// 段差が高すぎる場合は進路方向をを反転
			direction_ = Vector2(-direction_.x, direction_.y);
		}
	}


	// 進行方向に進む
	velocity->SetVelocity(Vector3(direction_.x * speed_, direction_.y * speed_, 0.0f));

}


// ばぐってます
//--------------------------------------------------
// @param _transform 自身のトランスフォーム, _gameObjects オブジェクトリスト
// @brief 段差の高さを調べる
// @return 段差の高さ
//--------------------------------------------------
std::optional<float> RobotMoveComponent::CheckStepHeight(const TransformComponent& _transform, const Vector3& _size,  const std::vector<GameObject*> _gameObjects)
{
	auto position = _transform.GetPosition();
	Vector2 scanStart = Vector2((position.x + _size.x ) + direction_.x * step_scan_distance_, position.y);
	Vector2 scanEnd   = Vector2(scanStart.x, scanStart.y - max_step_height_);

	float closestStepHeight = max_step_height_ + 1;	// 初期値： スキャン範囲外を超える値

	// オブジェクトリストを走査
	for (const auto& obj : _gameObjects) {
		auto otherCollider = obj->GetComponent<ColliderBaseComponent>();
		if(auto boxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider))
		{
			auto hitbox = boxCollider->GetWorldHitBox();
			// 足元のスキャンラインがAABBに重なっているか確認
			if (scanStart.x >= hitbox.min_.x && scanStart.x <= hitbox.max_.x) {
				float stepHeight = hitbox.max_.y - scanEnd.y;  // 段差の高さ
				// 登れる段差の高さか確認
				if (stepHeight > 0 && stepHeight <= max_step_height_) {
					closestStepHeight = min(closestStepHeight, stepHeight);
				}
			}
		}
	}
	// 最も近い段差が見つかればその高さを返す
	if (closestStepHeight <= max_step_height_) {
		std::cout << std::format("段差の高さ：{}\n", closestStepHeight);
		return closestStepHeight;
	}

	return std::nullopt; // 段差がない
}

