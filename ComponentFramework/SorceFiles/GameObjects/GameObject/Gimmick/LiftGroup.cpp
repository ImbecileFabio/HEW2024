//=================================================================
// [LiftGroup.cpp] リフトグループソースファイル
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：リフトグループ実装
//=================================================================
/*----- インクルード -----*/
#include "LiftGroup.h"
#include "../Lift.h"
#include "../Pendulum.h"
#include "../../Component/PendulumMovementComponent.h"
#include "../../Component/GimmickComponent/LiftComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
LiftGroup::LiftGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "LiftGroup")
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
LiftGroup::~LiftGroup(void)
{
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void LiftGroup::InitGameObject(void)
{
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void LiftGroup::UpdateGameObject(void)
{
    if (!isCenterMedian)
    {
        if (liftTiles_.empty()) return;
        if (initialPositions_.empty()) // 初期位置のキャッシュがまだの場合
        {
            // 初期位置をキャッシュ
            initialPositions_.clear();
            owner_lift_components_.clear();
            for (auto& tile : liftTiles_)
            {
                tile->GetTransformComponent()->SetSize(61.0f, 60.0f);
                initialPositions_.push_back(tile->GetTransformComponent()->GetPosition());
                owner_lift_components_.push_back(tile->GetComponent<LiftComponent>());
            }
        }

        int size = static_cast<int>(liftTiles_.size());
        DirectX::SimpleMath::Vector3 centerPos;

        if (size % 2 == 0) // 偶数の場合
        {
			isLeftRight_ = false;
            tileCenterNum_ = static_cast<int>(rightIndex_);

            centerPos = (initialPositions_[leftIndex_] + initialPositions_[rightIndex_]) / 2.0f;

            auto lift = dynamic_cast<Lift*>(liftTiles_[rightIndex_]);
            auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
            pendulum->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(centerPos);
            if (lift && pendulum)
            {
                lift->SetPendulum(pendulum);
                lift->GetComponent<LiftComponent>()->SetPendulum(pendulum);
            }
        }
        else // 奇数の場合
        {
            isLeftRight_ = true;
            centerIndex_ = size / 2;
            tileCenterNum_ = static_cast<int>(centerIndex_);

            centerPos = initialPositions_[centerIndex_];

            auto lift = dynamic_cast<Lift*>(liftTiles_[centerIndex_]);
            auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
            if (lift && pendulum)
            {
                lift->SetPendulum(pendulum);
                lift->GetComponent<LiftComponent>()->SetPendulum(pendulum);
            }
        }
        isCenterMedian = true;
    }
	if (isLeftRight_)
	{
        DirectX::SimpleMath::Vector3 centerPos = liftTiles_[centerIndex_]->GetTransformComponent()->GetPosition();
        owner_pendulum_movement_->SetPendulumFulcrum(centerPos);
    }
    else
    {
        DirectX::SimpleMath::Vector3 centerPos = (liftTiles_[leftIndex_]->GetTransformComponent()->GetPosition() + liftTiles_[rightIndex_]->GetTransformComponent()->GetPosition()) / 2.0f;
        owner_pendulum_movement_->SetPendulumFulcrum(centerPos);
    }
}
//--------------------------------------------------
// @brief リフトタイルを追加
// @param _tile[追加するタイルオブジェクト]
//--------------------------------------------------
void LiftGroup::AddLiftTile(GameObject* _tile)
{
	liftTiles_.push_back(_tile);
    auto lift = dynamic_cast<Lift*>(_tile);
    lift->SetLiftGroup(this);
}
//--------------------------------------------------
// @brief ギミックと連動する振り子を設定、振り子のコンポーネントをキャッシュ
// @param _centerPendulum[振り子オブジェクト]
//--------------------------------------------------
void LiftGroup::SetPendulumANDMovement(GameObject* _centerPendulum)
{
	centerPendulum_ = _centerPendulum;
	// 振り子のコンポーネントを取得しておく
	owner_pendulum_movement_ = centerPendulum_->GetComponent<PendulumMovementComponent>();
}
//--------------------------------------------------
// @brief リフトのタイルを同期させる処理
//--------------------------------------------------
void LiftGroup::UpdateLiftTilePositions()
{
    DirectX::SimpleMath::Vector3 centerLiftPos    = liftTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition();
    DirectX::SimpleMath::Vector3 centerInitialPos = initialPositions_[tileCenterNum_];
    DirectX::SimpleMath::Vector3 currentOffset    = centerLiftPos - centerInitialPos;

    for (int i = 0; i < liftTiles_.size(); i++)
    {
        DirectX::SimpleMath::Vector3 newPosition = initialPositions_[i] + currentOffset;
        liftTiles_[i]->GetTransformComponent()->SetPosition(newPosition);
    }
}
