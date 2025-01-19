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
            size_t leftIndex = (size / 2) - 1;
            size_t rightIndex = size / 2;
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
            size_t centerIndex = size / 2;
            tileCenterNum_ = centerIndex;

            centerPos = initialPositions_[centerIndex];

            auto lift = dynamic_cast<Lift*>(liftTiles_[centerIndex]);
            auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
            lift->SetPendulum(pendulum);
            lift->GetComponent<LiftComponent>()->SetPendulum(pendulum);
        }

        centerPendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(centerPos);
        isCenterMedian = true;
    }
    DirectX::SimpleMath::Vector3 centerLiftPos = liftTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition();

    for (size_t i = 0; i < liftTiles_.size(); ++i)
    {
        DirectX::SimpleMath::Vector3 initialPos = initialPositions_[i];
		initialPos.x = std::abs(initialPos.x);
		initialPos.y = std::abs(initialPos.y);
        DirectX::SimpleMath::Vector3 currentOffset = centerLiftPos - initialPositions_[tileCenterNum_];
		currentOffset.x = std::abs(currentOffset.x);
		currentOffset.y = std::abs(currentOffset.y);
        DirectX::SimpleMath::Vector3 newPosition = initialPos + currentOffset;
		newPosition.x = std::abs(newPosition.x);
		newPosition.y = std::abs(newPosition.y);

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


