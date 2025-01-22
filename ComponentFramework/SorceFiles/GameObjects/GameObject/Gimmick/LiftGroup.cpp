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
        size_t size = liftTiles_.size();
        if (size == 0)
        {
            // タイルが存在しない場合は処理をスキップ
            return;
        }

        // 初期位置をキャッシュ
        initialPositions_.clear();
        for (auto& tile : liftTiles_)
        {
            initialPositions_.push_back(tile->GetTransformComponent()->GetPosition());
            owner_lift_components_.push_back(tile->GetComponent<LiftComponent>());
        }

        DirectX::SimpleMath::Vector3 centerPos;

        if (size % 2 == 0) // 偶数
        {
            int leftIndex = (size / 2) - 1;
            int rightIndex = size / 2;
            tileCenterNum_ = leftIndex;

            DirectX::SimpleMath::Vector3 leftPos = initialPositions_[leftIndex];
            DirectX::SimpleMath::Vector3 rightPos = initialPositions_[rightIndex];
            centerPos = (leftPos + rightPos) / 2.0f;

            auto lift = dynamic_cast<Lift*>(liftTiles_[leftIndex]);
            auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
            lift->SetPendulum(pendulum);
            lift->GetComponent<LiftComponent>()->SetPendulum(pendulum);
        }
        else // 奇数
        {
            int centerIndex = size / 2;
            tileCenterNum_ = centerIndex;

            centerPos = initialPositions_[centerIndex];

            auto lift = dynamic_cast<Lift*>(liftTiles_[centerIndex]);
            auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
            lift->SetPendulum(pendulum);
            lift->GetComponent<LiftComponent>()->SetPendulum(pendulum);
        }
        isCenterMedian = true;
    }

    // 現在の中心タイル位置
    DirectX::SimpleMath::Vector3 centerLiftPos = liftTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition();
    DirectX::SimpleMath::Vector3 centerInitialPos = initialPositions_[tileCenterNum_];
    DirectX::SimpleMath::Vector3 currentOffset = centerLiftPos - centerInitialPos;

    // 各タイルの位置を更新
    for (size_t i = 0; i < liftTiles_.size(); ++i)
    {
        if (i == tileCenterNum_) continue; // 中心タイルは更新しない

        DirectX::SimpleMath::Vector3 newPosition = initialPositions_[i] + currentOffset;
        liftTiles_[i]->GetTransformComponent()->SetPosition(newPosition);
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


