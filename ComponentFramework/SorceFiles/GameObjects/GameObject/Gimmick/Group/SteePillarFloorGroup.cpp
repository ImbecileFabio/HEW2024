//=================================================================
// [SteePillarFloorGroup.cpp] SteePillarFloorGroupソースファイル
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：SteePillarFloorGroup実装
//=================================================================
/*----- インクルード -----*/
#include "SteePillarFloorGroup.h"
#include "../SteePillarFloor.h"
#include "../SteePillarLeft.h"
#include "../../../GameObject/Pendulum.h"
#include "../../../Component/PendulumMovementComponent.h"
#include "../../../Component/EventComponent/ColliderEventComponent.h"
#include "../../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../../Component/TimerComponent.h"
#include "../../../Component/GravityComponent.h"
#include "SteePillarLeftGroup.h"
#include "SteePillarRightGroup.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
SteePillarFloorGroup::SteePillarFloorGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "SteePillarFloorGroup")
	, isCenterMedian_(false)
	, tileCenterNum_(0)
	, centerPendulum_(nullptr)
	, owner_pendulum_movement_(nullptr)
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
SteePillarFloorGroup::~SteePillarFloorGroup(void)
{
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void SteePillarFloorGroup::InitGameObject(void)
{
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void SteePillarFloorGroup::UpdateGameObject(void)
{
	// 振り子を中心に調整する処理
	if (!isCenterMedian_)
	{
		CacheInitPosition();
	}
	// 振り子の状態を更新
	UpdatePendulumState();

	// 左鉄柱のアニメーションが終了したら
	if (steePillarRightGroup_->GetIsAnimationEnd() && !isDownStart_)
	{
		StartFalling();
	}
	// 落ちた状態に一回でもなっていればずっとオフセットを適用する
	if (isDownStart_)
	{
		auto leftTiles = steePillarLeftGroup_->GetSteePillarLeftTiles();
		if (leftTiles.size() <= 1) return; // 鉄柱が1つ以下なら処理不要
		// 0番を省いて、大きい添え字から適用
		for (int i = static_cast<int>(leftTiles.size()) - 1; i > 0; i--)
		{
			auto tile = dynamic_cast<SteePillarLeft*>(leftTiles[i]);
			if (!tile) continue;
			tile->SetIsFloorVelocity(true);
			// 基準の床座標
			Vector3 basePos = steePillarFloorTiles_[0]->GetTransformComponent()->GetPosition();

			// 添え字 i を利用したオフセット計算
			float offsetY = static_cast<float>(i) * 42.0f; // 例えば10ずつ高さをずらす
			tile->SetFloorPosition(Vector3(basePos.x, basePos.y + offsetY, basePos.z));
		}
	}
	// 振り子の中心を再設定
	owner_pendulum_movement_->SetPendulumFulcrum(GetCenterPosition());

	// 鉄柱の床がタイルと当たっていたら
	if (isHitTile_ && !isPendulumDelete_)
	{
		auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
		pendulum->NotDrawAndStopPendulum();
		isPendulumDelete_ = true;
		for (auto& it : steePillarFloorTiles_)
		{
			auto steePillarFloor = dynamic_cast<SteePillarFloor*>(it);
			steePillarFloor->SetIsDown(false);
		}
		steePillarLeftGroup_->SetVelocityStop();
		steePillarRightGroup_->SetVelocityStop();
	}
	if (isHitLift_ && !isPendulumDelete_)
	{
		auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
		pendulum->NotDrawAndStopPendulum();
		isPendulumDelete_ = true;
		for (auto& it : steePillarFloorTiles_)
		{
			auto steePillarFloor = dynamic_cast<SteePillarFloor*>(it);
			steePillarFloor->SetIsDown(false);
		}
		steePillarLeftGroup_->SetVelocityStop();
		steePillarRightGroup_->SetVelocityStop();
	}
	// 画面外処理
	if (steePillarFloorTiles_[0]->GetTransformComponent()->GetPosition().y < -500.0f && !isPendulumDelete_)
	{
		auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
		pendulum->NotDrawAndStopPendulum();
		isPendulumDelete_ = true;
	}
}
//--------------------------------------------------
// @brief 脆い床タイルを追加
// @param _tile[追加するタイルオブジェクト]
//--------------------------------------------------
void SteePillarFloorGroup::AddSteePillarFloorTile(GameObject* _tile)
{
	steePillarFloorTiles_.emplace_back(_tile);
	auto steePillarFloor = dynamic_cast<SteePillarFloor*>(_tile);
	steePillarFloor->SetSteePillarFloorGroup(this);
}
//--------------------------------------------------
// @brief ギミックと連動する振り子を設定、振り子のコンポーネントをキャッシュ
// @param _centerPendulum[振り子オブジェクト]
//--------------------------------------------------
void SteePillarFloorGroup::SetPendulumANDMovement(GameObject* _centerPendulum)
{
	centerPendulum_ = _centerPendulum;
	// 振り子のコンポーネントを取得しておく
	owner_pendulum_movement_ = centerPendulum_->GetComponent<PendulumMovementComponent>();
}

void SteePillarFloorGroup::SetSteePillarLeftGroup(SteePillarLeftGroup* _steePillarLeftGroup)
{
	steePillarLeftGroup_ = _steePillarLeftGroup;
}

void SteePillarFloorGroup::SetSteePillarRightGroup(SteePillarRightGroup* _steePillarRightGroup)
{
	steePillarRightGroup_ = _steePillarRightGroup;
}

void SteePillarFloorGroup::UpdateSteePillarFloorTilePositions()
{
	if (initialPositions_.empty()) return;
	DirectX::SimpleMath::Vector3 centerLiftPos = steePillarFloorTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition();
	DirectX::SimpleMath::Vector3 centerInitialPos = initialPositions_[tileCenterNum_];
	DirectX::SimpleMath::Vector3 currentOffset = centerLiftPos - centerInitialPos;

	for (int i = 0; i < steePillarFloorTiles_.size(); i++)
	{
		DirectX::SimpleMath::Vector3 newPosition = initialPositions_[i] + currentOffset;
		steePillarFloorTiles_[i]->GetTransformComponent()->SetPosition(newPosition);
	}
}

void SteePillarFloorGroup::AlignSteePillarFloorTilesWithTile(float _y)
{
	for (auto& tile : steePillarFloorTiles_)
	{
		auto transform = tile->GetTransformComponent();
		transform->SetPositionY(_y + 60.0f);
	}

}

void SteePillarFloorGroup::CacheInitPosition()
{
	if (steePillarFloorTiles_.empty()) return;
	owner_pendulum_movement_->SetPendulumAngle(1.0f);
	if (initialPositions_.empty()) // 初期位置のキャッシュがまだの場合
	{
		// 初期位置をキャッシュ
		initialPositions_.clear();
		for (auto& tile : steePillarFloorTiles_)
		{
			initialPositions_.push_back(tile->GetTransformComponent()->GetPosition());
		}
	}

	int size = static_cast<int>(steePillarFloorTiles_.size());
	DirectX::SimpleMath::Vector3 centerPos;

	if (size % 2 == 0) // 偶数
	{
		// 中心2つのタイルのインデックスを計算
		leftIndex_ = (size / 2) - 1;
		rightIndex_ = size / 2;

		// 中心2つのタイルの位置を取得し、平均を計算
		DirectX::SimpleMath::Vector3 leftPos = steePillarFloorTiles_[leftIndex_]->GetTransformComponent()->GetPosition();
		DirectX::SimpleMath::Vector3 rightPos = steePillarFloorTiles_[rightIndex_]->GetTransformComponent()->GetPosition();
		centerPos = (leftPos + rightPos) / 2.0f;
	}
	else // 奇数
	{
		isOddNumber_ = false;
		// 中心のタイルのインデックスを計算
		tileCenterNum_ = size / 2;
		// 中心のタイルの位置を取得
		centerPos = steePillarFloorTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition();
	}
	// 振り子の中心を設定
	owner_pendulum_movement_->SetPendulumFulcrum(centerPos);
	isCenterMedian_ = true;
}

void SteePillarFloorGroup::UpdatePendulumState()
{
	if (owner_pendulum_movement_->GetPendulumMovement() && !isPendulumDelete_)
	{
		steePillarLeftGroup_->SetIsBreak(true);
		steePillarLeftGroup_->SetIsBreakStop(false);
		steePillarRightGroup_->SetIsBreakStop(false);
		steePillarRightGroup_->SetIsBreak(true);
	}
	else
	{
		steePillarLeftGroup_->SetIsBreakStop(true);
		steePillarRightGroup_->SetIsBreakStop(true);
	}
}

void SteePillarFloorGroup::StartFalling()
{
	isDownStart_ = true;
	for (auto& it : steePillarFloorTiles_)
	{
		auto steePillarFloor = dynamic_cast<SteePillarFloor*>(it);
		steePillarFloor->SetIsDown(true);
		steePillarFloor->GetComponent<GravityComponent>()->SetIsRobot(true);
	}
	steePillarLeftGroup_->SetIsDownStart(true);
	steePillarRightGroup_->SetIsDownStart(true);
}

DirectX::SimpleMath::Vector3 SteePillarFloorGroup::GetCenterPosition()
{
	if (isOddNumber_)	// 偶数
	{
		return (steePillarFloorTiles_[leftIndex_]->GetTransformComponent()->GetPosition() +
			steePillarFloorTiles_[rightIndex_]->GetTransformComponent()->GetPosition()) / 2.0f;
	}
	else                // 奇数
	{
		return steePillarFloorTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition();
	}
}


