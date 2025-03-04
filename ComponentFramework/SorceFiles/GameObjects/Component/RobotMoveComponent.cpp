//==================================================
// [RobotMoveComponent.cpp] ロボット移動コンポーネント
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ロボットの挙動を制御するコンポーネントの定義
// 自動で横に歩く
// 壁に当たったら反転する
// 地面がない場合は反転する
// 
// 既存の処理を用いずとにかく書き込んでます、コンポーネント指向とはいったい
// ぐちゃぐちゃコードでごめんなさい
//==================================================

/*----- インクルード -----*/
#include <memory>

#include "RobotMoveComponent.h"

#include "../../GameManager.h"
#include "../../TileMapManager.h"
#include "../../ColliderManager.h"

#include "../GameObject.h"
#include "../GameObject/Robot.h"
#include "../GameObject/Lift.h"
#include "../GameObject/Gimmick/Smoke.h"

#include "RigidbodyComponent/VelocityComponent.h"
#include "ColliderComponent/BoxColliderComponent.h"
#include "ColliderComponent/ScanColliderComponent.h"
#include "GravityComponent.h"


//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
RobotMoveComponent::RobotMoveComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
	, speed_(2.0f)
	, direction_(Vector2(1.0f, 0.0f))
	, scan_distance_(2.0f)
	, max_step_height_(TILE_SIZE_Y)
	, move_state_(RobotMoveState::Move)
{

	// スキャン用オブジェクトを生成
	wall_scan_object_ = new GameObject(owner_->GetGameManager(), "WallScanObject");
	wall_scan_collider_ = new ScanColliderComponent(wall_scan_object_);
	// ステップアップ用オブジェクトを生成
	step_scan_object_ = new GameObject(owner_->GetGameManager(), "StepScanObject");
	step_scan_collider_ = new ScanColliderComponent(step_scan_object_);
	// 地面スキャン用オブジェクトを生成
	ground_scan_object_ = new GameObject(owner_->GetGameManager(), "GroundScanObject");
	ground_scan_collider_ = new ScanColliderComponent(ground_scan_object_);

	owner_transform_ = owner_->GetTransformComponent();
	owner_velocity_ = owner_->GetComponent<VelocityComponent>();
	owner_collider_ = owner_->GetComponent<BoxColliderComponent>();
	owner_gravity_ = owner_->GetComponent<GravityComponent>();


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
	direction_ = Vector2(-1.0f, 0.0f);

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
	switch (move_state_) {
	case RobotMoveState::Idle:
	{
		// 止まる
		owner_velocity_->SetVelocity({ 0.0f, 0.0f, 0.0f });

		break;
	}
	case RobotMoveState::Move:
	{
		// 当たり判定の更新
		this->UpdateWallScanCollider();
		this->UpdateStepScanCollider();
		this->UpdateGroundScanCollider();

		// 壁の衝突判定
		if (CheckWallCollision())	// 壁に当たっている
		{
			float stepHeight = ComputeStepHeight();
			if (stepHeight > 0 && stepHeight <= max_step_height_) {
				// 上る処理
				Vector3 currentPos = owner_transform_->GetPosition();
				owner_transform_->SetPosition(
					currentPos.x + (direction_.x * 2.0f),	// 引っかからないように少し多めに前に進む
					currentPos.y + stepHeight,
					currentPos.z
				);
				// 移動
				owner_velocity_->SetVelocity({ speed_ * direction_.x, 0.0f, 0.0f });
			}
			else { // 登れない段差
				direction_ = { -direction_.x, direction_.y }; // 移動方向を反転
				owner_velocity_->SetVelocity({ 0.0f, owner_velocity_->GetVelocity().y, 0.0f }); // 横の速度をリセット
			}
		}
		// 床の衝突判定
		else if (!CheckGround()) // 進行方向に地面がない
		{
			direction_ = { -direction_.x, direction_.y }; // 移動方向を反転
			owner_velocity_->SetVelocity({ 0.0f, owner_velocity_->GetVelocity().y, 0.0f }); // 横の速度をリセット
		}
		// 通常移動
		else
		{
			owner_velocity_->SetVelocity({ speed_ * direction_.x, 0.0f, 0.0f });
		}
		break;
	}
	case RobotMoveState::Fall:
	{

		break;
	}
	case RobotMoveState::OnLift:
	{

		break;
	}
	case RobotMoveState::OnSmoke:
	{

		break;
	}
	}
}

//--------------------------------------------------
// ロボットの速度を変更
//--------------------------------------------------
void RobotMoveComponent::SetSpeed(float _speed)
{
	speed_ = _speed;
}
float RobotMoveComponent::GetSpeed(void)
{
	return speed_;
}

//--------------------------------------------------
// ウォールスキャン用ヒットボックスの更新
//--------------------------------------------------
void RobotMoveComponent::UpdateWallScanCollider()
{
	auto robotPos = owner_transform_->GetPosition();
	auto robotSize = owner_collider_->GetSize();

	wall_scan_object_->GetTransformComponent()->SetSize(scan_distance_, owner_transform_->GetSize().y - 10.0f);
	wall_scan_collider_->SetSize(wall_scan_object_->GetTransformComponent()->GetSize());

	Vector3 offset = { 0.0f, 0.0f, 0.0f };
	if (direction_.x > 0)
		offset = { (robotSize.x + scan_distance_) / 2, 0.0f, 0.0f };
	else
		offset = { (-robotSize.x - scan_distance_) / 2, 0.0f, 0.0f };
	wall_scan_collider_->SetOffset(offset);
	wall_scan_collider_->SetWorldHitBox(robotPos);

	wall_scan_object_->GetTransformComponent()->SetPosition(robotPos + offset);
}

//--------------------------------------------------
// 段差スキャン用のヒットボックスの更新
//--------------------------------------------------
void RobotMoveComponent::UpdateStepScanCollider()
{
	auto robotPos = owner_transform_->GetPosition();
	auto robotSize = owner_collider_->GetSize();

	step_scan_object_->GetTransformComponent()->SetSize(
		owner_collider_->GetSize().x + scan_distance_,
		owner_transform_->GetSize().y
	);
	step_scan_collider_->SetSize(step_scan_object_->GetTransformComponent()->GetSize());

	Vector3 offset = { 0.0f, 0.0f, 0.0f };
	if (direction_.x > 0)
		offset = { scan_distance_ / 2, robotSize.y, 0.0f };
	else
		offset = { -scan_distance_ / 2, robotSize.y, 0.0f };
	step_scan_collider_->SetOffset(offset);
	step_scan_collider_->SetWorldHitBox(robotPos);

	step_scan_object_->GetTransformComponent()->SetPosition(robotPos + offset);
}

//--------------------------------------------------
// 地面スキャン用のヒットボックスの更新
//--------------------------------------------------
void RobotMoveComponent::UpdateGroundScanCollider()
{
	auto robotPos = owner_transform_->GetPosition();
	auto robotSize = owner_collider_->GetSize();

	ground_scan_object_->GetTransformComponent()->SetSize(owner_collider_->GetSize().x + scan_distance_, owner_transform_->GetSize().y + 1.0f);
	ground_scan_collider_->SetSize(step_scan_object_->GetTransformComponent()->GetSize());

	Vector3 offset = { 0.0f, 0.0f, 0.0f };
	if (direction_.x > 0)
		offset = { (robotSize.x + scan_distance_), (-robotSize.y - scan_distance_), 0.0f };
	else
		offset = { (-robotSize.x - scan_distance_), (-robotSize.y - scan_distance_), 0.0f };

	ground_scan_collider_->SetOffset(offset);
	ground_scan_collider_->SetWorldHitBox(robotPos);

	ground_scan_object_->GetTransformComponent()->SetPosition(robotPos + offset);

}

//--------------------------------------------------
// @brief 壁との衝突検知
// @return 衝突している: true, していない: false
//--------------------------------------------------
bool RobotMoveComponent::CheckWallCollision()
{
	auto objects = owner_->GetGameManager()->GetColliderManager()->GetColliderGameObjects();
	auto scanHitbox = wall_scan_collider_->GetWorldHitBox();

	// 衝突判定
	for (const auto& obj : objects) {
		if (obj == owner_) continue;	// オーナーとは比べない
		else if (obj->GetType() == GameObject::TypeID::Item) continue; // 歯車無視
		else if (obj->GetType() == GameObject::TypeID::Smoke) continue; // 煙無視
		else if (obj->GetType() == GameObject::TypeID::SmokePipe) continue; // 排無視
		auto otherCollider = obj->GetComponent<ColliderBaseComponent>();
		if (auto otherBoxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider)) {
			auto otherHitbox = otherBoxCollider->GetWorldHitBox();

			// 拡張ヒットボックスと他オブジェクトのAABBが重なる場合、衝突と判定
			if (scanHitbox.max_.x > otherHitbox.min_.x && scanHitbox.min_.x < otherHitbox.max_.x &&
				scanHitbox.max_.y > otherHitbox.min_.y && scanHitbox.min_.y < otherHitbox.max_.y) {

				// スキャン用ヒットボックスと他のオブジェクトのAABBが重なる場合、衝突と判定
				if (scanHitbox.max_.x > otherHitbox.min_.x && scanHitbox.min_.x < otherHitbox.max_.x &&
					scanHitbox.max_.y > otherHitbox.min_.y && scanHitbox.min_.y < otherHitbox.max_.y) {
					return true;
				}
			}
		}
	}
	return false;
}


//--------------------------------------------------
// @brief 地面検知
// @return 地面がある: true, ない: false
//--------------------------------------------------
bool RobotMoveComponent::CheckGround()
{
	auto objects = owner_->GetGameManager()->GetColliderManager()->GetColliderGameObjects();
	auto groundHitbox = ground_scan_collider_->GetWorldHitBox();
	for (const auto& obj : objects) {
		// 除外リスト
		switch (obj->GetType())
		{
		case GameObject::TypeID::Robot:
		case GameObject::TypeID::Item:
		//case GameObject::TypeID::Smoke:
		case GameObject::TypeID::SmokePipe:
			continue;
		}

		auto otherCollider = obj->GetComponent<ColliderBaseComponent>();
		if (auto otherBoxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider)) {
			auto otherHitbox = otherBoxCollider->GetWorldHitBox();

			// 段差検出 (範囲内に他オブジェクトがある場合)
			if (groundHitbox.max_.x > otherHitbox.min_.x && groundHitbox.min_.x < otherHitbox.max_.x &&
				groundHitbox.max_.y > otherHitbox.min_.y && groundHitbox.min_.y < otherHitbox.max_.y) {
				return true;
			}
		}
	}
	return false;
}

float RobotMoveComponent::ComputeStepHeight()
{
	auto objects = owner_->GetGameManager()->GetColliderManager()->GetColliderGameObjects();
	auto stepHitbox = step_scan_collider_->GetWorldHitBox();
	float robotBottomY = owner_collider_->GetWorldHitBox().min_.y;

	const float MAX_FLOAT = 3.402823466e+38F;	// floatの最大値
	float minStepHeight = MAX_FLOAT;

	for (const auto& obj : objects) {
		// 除外リスト
		switch (obj->GetType()) {
		case GameObject::TypeID::Robot:
		case GameObject::TypeID::Item:
		case GameObject::TypeID::Smoke:
		case GameObject::TypeID::SmokePipe:
		case GameObject::TypeID::Lift:
			continue;
		}

		auto otherCollider = obj->GetComponent<BoxColliderComponent>();
		if (!otherCollider) continue;
		auto otherHitbox = otherCollider->GetWorldHitBox();

		if (direction_.x > 0) {
			if (otherHitbox.min_.x < stepHitbox.max_.x &&
				otherHitbox.min_.x > stepHitbox.min_.x) {

				float heightDiff = otherHitbox.max_.y - robotBottomY;
				if (heightDiff > 0 && heightDiff < minStepHeight) {
					minStepHeight = heightDiff;
				}
			}
		}
		else {
			if (otherHitbox.max_.x > stepHitbox.min_.x &&
				otherHitbox.max_.x < stepHitbox.max_.x) {

				float heightDiff = otherHitbox.max_.y - robotBottomY;
				if (heightDiff > 0 && heightDiff < minStepHeight) {
					minStepHeight = heightDiff;
				}
			}
		}
	}

	return (minStepHeight == MAX_FLOAT ? 0.0f : minStepHeight);

}