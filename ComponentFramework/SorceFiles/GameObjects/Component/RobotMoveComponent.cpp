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

#include "RigidbodyComponent/VelocityComponent.h"
#include "ColliderComponent/BoxColliderComponent.h"
#include "ColliderComponent/ScanColliderComponent.h"
#include "GravityComponent.h"


#include "RenderComponent/SpriteComponent.h"

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
RobotMoveComponent::RobotMoveComponent(GameObject* _owner, int _updateOrder)
	:Component(_owner, _updateOrder)
	, speed_(2.0f)
	, direction_(Vector2(1.0f, 0.0f))
	, scan_distance_(1.0f)
	, step_up_height_(TILE_SIZE_Y)
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

	if (!wall_scan_object_) {
		// スキャン用オブジェクトを生成
		wall_scan_object_ = new GameObject(owner_->GetGameManager(), "WallScanObject");
		wall_scan_collider_ = new ScanColliderComponent(wall_scan_object_);
	}
	if (!step_scan_object_)
	{
		// ステップアップ用オブジェクトを生成
		step_scan_object_ = new GameObject(owner_->GetGameManager(), "StepScanObject");
		step_scan_collider_ = new ScanColliderComponent(step_scan_object_);

	}
	if (!ground_scan_object_)
	{
		// 地面スキャン用オブジェクトを生成
		ground_scan_object_ = new GameObject(owner_->GetGameManager(), "GroundScanObject");
		ground_scan_collider_ = new ScanColliderComponent(ground_scan_object_);
	}
	owner_transform_ = owner_->GetTransformComponent();
	owner_velocity_ = owner_->GetComponent<VelocityComponent>();
	owner_collider_ = owner_->GetComponent<BoxColliderComponent>();
	owner_gravity_ = owner_->GetComponent<GravityComponent>();


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
	if (!owner_transform_ || !owner_velocity_ || !owner_collider_ || !owner_gravity_)	//	一度だけ取得
	{
		owner_transform_ = owner_->GetTransformComponent();
		owner_velocity_ = owner_->GetComponent<VelocityComponent>();
		owner_collider_ = owner_->GetComponent<BoxColliderComponent>();
		owner_gravity_ = owner_->GetComponent<GravityComponent>();

	}

	if (!owner_transform_ || !owner_velocity_ || !owner_collider_ || !owner_gravity_)
	{
		std::cout << std::format("＜RobotMoveComponent＞ -> Update Error\n");
		return;
	}


	// 当たり判定の更新
	this->UpdateWallScanCollider();
	this->UpdateStepScanCollider();
	this->UpdateGroundScanCollider();

	// 壁の衝突判定
	if (CheckWallCollision())	// 壁に当たっている
	{
		// ステップアップ判定
		if (!CheckStepUp())	// 登れる段差
		{
			// 上る
			owner_transform_->SetPosition(owner_transform_->GetPosition() + Vector3(0.0f, step_up_height_, 0.0f));
		}
		else				// 登れない段差
		{
			direction_ = { -direction_.x, direction_.y };	// 移動方向を反転
			owner_velocity_->SetVelocity({ 0.0f, owner_velocity_->GetVelocity().y, 0.0f });	// 横の速度をリセット
		}
	}
	// 床の衝突判定
	else if (!CheckGround())	//進行方向に地面がない
	{
		direction_ = { -direction_.x, direction_.y };	// 移動方向を反転
		owner_velocity_->SetVelocity({ 0.0f, owner_velocity_->GetVelocity().y, 0.0f });	// 横の速度をリセット
	}

	// 空中でなければ移動
	if(owner_gravity_->GetIsGround())
	owner_velocity_->SetVelocity({ speed_ * direction_.x, owner_velocity_->GetVelocity().y, 0.0f});
}

//--------------------------------------------------
// ウォールスキャン用ヒットボックスの更新
//--------------------------------------------------
void RobotMoveComponent::UpdateWallScanCollider()
{
	auto robotPos = owner_transform_->GetPosition();
	auto robotSize = owner_collider_->GetSize();

	wall_scan_object_->GetTransformComponent()->SetSize(scan_distance_, owner_transform_->GetSize().y - 5.0f);
	wall_scan_collider_->SetSize(wall_scan_object_->GetTransformComponent()->GetSize());

	Vector3 offset = { 0.0f, 0.0f, 0.0f };
	if (direction_.x > 0)
		offset = { ( robotSize.x+ scan_distance_) / 2, 0.0f, 0.0f };
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

	step_scan_object_->GetTransformComponent()->SetSize(owner_collider_->GetSize().x + scan_distance_, owner_transform_->GetSize().y);
	step_scan_collider_->SetSize(step_scan_object_->GetTransformComponent()->GetSize());

	Vector3 offset = { 0.0f, 0.0f, 0.0f };
	if (direction_.x > 0)
		offset = {  scan_distance_ / 2, robotSize.y, 0.0f};
	else
		offset = { -scan_distance_ / 2, robotSize.y, 0.0f};
	step_scan_collider_->SetOffset(offset);
	step_scan_collider_->SetWorldHitBox(robotPos);

	step_scan_object_->GetTransformComponent()->SetPosition(robotPos+offset);
}
//--------------------------------------------------
// 地面スキャン用のヒットボックスの更新
//--------------------------------------------------
void RobotMoveComponent::UpdateGroundScanCollider()
{
	auto robotPos = owner_transform_->GetPosition();
	auto robotSize = owner_collider_->GetSize();

	ground_scan_object_->GetTransformComponent()->SetSize(owner_collider_->GetSize().x + scan_distance_, owner_transform_->GetSize().y + 5.0f);
	ground_scan_collider_->SetSize(step_scan_object_->GetTransformComponent()->GetSize());

	Vector3 offset = { 0.0f, 0.0f, 0.0f };
	if(direction_.x > 0)
		offset = { ( robotSize.x + scan_distance_), (-robotSize.y - scan_distance_), 0.0f };
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
// @brief 段差検知
// @return 段差がある: true, ない: false
//--------------------------------------------------
bool RobotMoveComponent::CheckStepUp()
{
	auto objects = owner_->GetGameManager()->GetColliderManager()->GetColliderGameObjects();
	auto stepHitbox = step_scan_collider_->GetWorldHitBox();
	for (const auto& obj : objects) {
		auto otherCollider = obj->GetComponent<ColliderBaseComponent>();
		if (auto otherBoxCollider = dynamic_cast<BoxColliderComponent*>(otherCollider)) {
			auto otherHitbox = otherBoxCollider->GetWorldHitBox();

			// 段差検出 (範囲内に他オブジェクトがある場合)
			if (stepHitbox.max_.x > otherHitbox.min_.x && stepHitbox.min_.x < otherHitbox.max_.x &&
				stepHitbox.max_.y > otherHitbox.min_.y && stepHitbox.min_.y < otherHitbox.max_.y) {
				return true;
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
