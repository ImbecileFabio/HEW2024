//=================================================================
// [WeakFloorGroup.cpp] WeakFloorGroupソースファイル
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：WeakFloorGroup実装
//=================================================================
/*----- インクルード -----*/
#include "WeakFloorGroup.h"
#include "../WeakFloor.h"
#include "../../../GameObject/Pendulum.h"
#include "../../../Component/PendulumMovementComponent.h"
#include "../../../Component/EventComponent/ColliderEventComponent.h"
#include "../../../Component/ColliderComponent/BoxColliderComponent.h"
#include "../../../Component/TimerComponent.h"
#include "../../../GameObject/Robot.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
WeakFloorGroup::WeakFloorGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "WeakFloorGroup")
	, isWeakFloorBreak_(false)
	, isCenterMedian(false)
	, tileCenterNum_(0)
	, centerPendulum_(nullptr)
	, owner_pendulum_movement_(nullptr)
	, timer_component_(nullptr)
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
WeakFloorGroup::~WeakFloorGroup(void)
{
	delete timer_component_;
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void WeakFloorGroup::InitGameObject(void)
{
	timer_component_ = new TimerComponent(this, 5.0f);
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void WeakFloorGroup::UpdateGameObject(void)
{
	if (isPendulumOn_)
	{
		// 振り子を中心に調整する処理
		if (!isCenterMedian)
		{
			owner_pendulum_movement_->SetPendulumAngle(1.0f);
			size_t size = weakFloorTiles_.size();
			if (size == 0)
			{
				// タイルが存在しない場合は処理をスキップ
				return;
			}

			DirectX::SimpleMath::Vector3 centerPos;

			if (size % 2 == 0) // 偶数
			{
				// 中心2つのタイルのインデックスを計算
				size_t leftIndex = (size / 2) - 1;
				size_t rightIndex = size / 2;

				// 中心2つのタイルの位置を取得し、平均を計算
				DirectX::SimpleMath::Vector3 leftPos = weakFloorTiles_[leftIndex]->GetTransformComponent()->GetPosition();
				DirectX::SimpleMath::Vector3 rightPos = weakFloorTiles_[rightIndex]->GetTransformComponent()->GetPosition();
				centerPos = (leftPos + rightPos) / 2.0f;
			}
			else // 奇数
			{
				// 中心のタイルのインデックスを計算
				size_t centerIndex = size / 2;

				// 中心のタイルの位置を取得
				centerPos = weakFloorTiles_[centerIndex]->GetTransformComponent()->GetPosition();
			}

			// 振り子の中心を設定
			owner_pendulum_movement_->SetPendulumFulcrum(centerPos);
			isCenterMedian = true;
		}
		int hitCount = 0;
		for (auto& tile : weakFloorTiles_)
		{
			bool hit = false;
			hit = tile->GetComponent<BoxColliderComponent>()->GetHitFg();
			if (hit)
			{
				hitCount++;
			}
		}
		// 床が誰とも判定を取らなかったら床を壊さない
		if (hitCount == 0)
		{
			isWeakFloorBreak_ = false;
		}
		else
		{
			isWeakFloorBreak_ = true;
		}
		if (!isWeakFloorBreak_ || !owner_pendulum_movement_->GetPendulumMovement())
		{
			timer_component_->StopTimer();
		}
		// 脆い床が壊れたかどうかかつ、振り子が動いている場合
		if (isWeakFloorBreak_ && owner_pendulum_movement_->GetPendulumMovement())
		{
			// タイマーを開始
			if (!timer_component_->GetIsActive())
			{
				timer_component_->StartTimer();
			}
			// タイマーが経過して、トリガーが発生した場合
			if (timer_component_->GetIsTriggered())
			{
				timer_component_->StopTimer();
				// グループの方で脆いタイルを一括で変更をかける この処理は一度だけ
				if (weakFloorTiles_[0]->GetState() == GameObject::State::Dead) return;
				for (int i = 0; i < weakFloorTiles_.size(); i++)
				{	// 左端タイルがロボットより左にある場合、ロボットをちょっと戻す
					auto robotTransForm = robot_->GetTransformComponent();
					auto robotPos = robotTransForm->GetPosition();
					if (robotTransForm->GetPosition().x <= weakFloorTiles_[0]->GetTransformComponent()->GetPosition().x)
					{
						robotTransForm->SetPosition(weakFloorTiles_[0]->GetTransformComponent()->GetPosition().x + 20.0f, robotPos.y);
					}
					else if (robotTransForm->GetPosition().x >= weakFloorTiles_[weakFloorTiles_.size() - 1]->GetTransformComponent()->GetPosition().x)
					{
						// 右端タイルがロボットより右にある場合、ロボットをちょっと戻す
						robotTransForm->SetPosition(weakFloorTiles_[weakFloorTiles_.size() - 1]->GetTransformComponent()->GetPosition().x - 20.0f, robotPos.y);
					}
					weakFloorTiles_[i]->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
					weakFloorTiles_[i]->GetComponent<EventBaseComponent>()->RemoveEvent();
					weakFloorTiles_[i]->SetState(GameObject::State::Dead);
				}
				auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
				pendulum->NotDrawAndStopPendulum();
				//robot_ = nullptr;	// 壊れたら参照を削除
			}
		}
	}
	else
	{
		int hitCount = 0;
		for (auto& tile : weakFloorTiles_)
		{
			bool hit = false;
			hit = tile->GetComponent<BoxColliderComponent>()->GetHitFg();
			if (hit)
			{
				hitCount++;
			}
		}
		// 床が誰とも判定を取らなかったら床を壊さない
		if (hitCount == 0)
		{
			isWeakFloorBreak_ = false;
		}
		else
		{
			isWeakFloorBreak_ = true;
		}
		if (!isWeakFloorBreak_ )
		{
			timer_component_->StopTimer();
		}
		// 脆い床が壊れたかどうかかつ、振り子が動いている場合
		if (isWeakFloorBreak_)
		{
			// タイマーを開始
			if (!timer_component_->GetIsActive())
			{
				timer_component_->StartTimer();
			}
			// タイマーが経過して、トリガーが発生した場合
			if (timer_component_->GetIsTriggered())
			{
				timer_component_->StopTimer();
				// グループの方で脆いタイルを一括で変更をかける この処理は一度だけ
				for (auto& tile : weakFloorTiles_)
				{
					tile->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
					tile->GetComponent<EventBaseComponent>()->RemoveEvent();
					tile->SetState(GameObject::State::Dead);
				}
			}
		}

	}
}
//--------------------------------------------------
// @brief 脆い床タイルを追加
// @param _tile[追加するタイルオブジェクト]
//--------------------------------------------------
void WeakFloorGroup::AddWeakFloorTile(GameObject* _tile)
{
	weakFloorTiles_.emplace_back(_tile);
	auto weakFloor = dynamic_cast<WeakFloor*>(_tile);
	weakFloor->SetWeakFloorGroup(this);
}
//--------------------------------------------------
// @brief ギミックと連動する振り子を設定、振り子のコンポーネントをキャッシュ
// @param _centerPendulum[振り子オブジェクト]
//--------------------------------------------------
void WeakFloorGroup::SetPendulumANDMovement(GameObject* _centerPendulum)
{
	centerPendulum_ = _centerPendulum;
	// 振り子のコンポーネントを取得しておく
	owner_pendulum_movement_ = centerPendulum_->GetComponent<PendulumMovementComponent>();
}

void WeakFloorGroup::SetRobot(Robot* _robot)
{
	isOnRobot_ = true;
	robot_ = _robot;
}

