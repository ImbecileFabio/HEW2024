//=================================================================
// [SteePillarFloorGroup.cpp] SteePillarFloorGroupソースファイル
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：SteePillarFloorGroup実装
//=================================================================
/*----- インクルード -----*/
#include "SteePillarFloorGroup.h"
#include "../SteePillarFloor.h"
#include "../../../GameObject/Pendulum.h"
#include "../../../Component/PendulumMovementComponent.h"
#include "../../../Component/EventComponent/ColliderEventComponent.h"
#include "../../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../../Component/TimerComponent.h"
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
		if (steePillarFloorTiles_.empty()) return;
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
	// 左鉄柱のアニメーションが終了したら
	if (steePillarRightGroup_->GetIsAnimationEnd() && !isDownStart_)
	{
		isDownStart_ = true;	// 落下処理の開始を設定

		for (auto& it : steePillarFloorTiles_)
		{
			auto steePillarFloor = dynamic_cast<SteePillarFloor*>(it);
			steePillarFloor->SetIsDown(true);
		}
		// 左右の鉄柱グループの落下フラグを設定
		steePillarLeftGroup_->SetIsDownStart(true);
		steePillarRightGroup_->SetIsDownStart(true);
	}

	if (isOddNumber_)	// 偶数
	{
		DirectX::SimpleMath::Vector3 centerPos = (steePillarFloorTiles_[leftIndex_]->GetTransformComponent()->GetPosition() + steePillarFloorTiles_[rightIndex_]->GetTransformComponent()->GetPosition()) / 2.0f;
		owner_pendulum_movement_->SetPendulumFulcrum(centerPos);
	}
	else                // 奇数
	{
		owner_pendulum_movement_->SetPendulumFulcrum(steePillarFloorTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition());
	}
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


