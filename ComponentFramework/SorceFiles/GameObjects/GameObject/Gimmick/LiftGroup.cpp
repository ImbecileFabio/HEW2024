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
    // 振り子を中心に調整する処理
    if (!isCenterMedian)
    {
        size_t size = liftTiles_.size();
        if (size == 0)
        {
            // タイルが存在しない場合は処理をスキップ
            return;
        }

        // リフトを一括で変更するためのキャッシュ
        for (auto& tile : liftTiles_)
        {
            owner_lift_components_.push_back(tile->GetComponent<LiftComponent>());
        }

        DirectX::SimpleMath::Vector3 centerPos;

        if (size % 2 == 0) // 偶数
        {
            // 中心2つのタイルのインデックスを計算
            size_t leftIndex = (size / 2) - 1;
            size_t rightIndex = size / 2;
            // 添え字を保存
            tileCenterNum_ = leftIndex;
            // 中心2つのタイルの位置を取得し、平均を計算
            DirectX::SimpleMath::Vector3 leftPos = liftTiles_[leftIndex] ->GetTransformComponent()->GetPosition();
            DirectX::SimpleMath::Vector3 rightPos = liftTiles_[rightIndex]->GetTransformComponent()->GetPosition();
            centerPos = (leftPos + rightPos) / 2.0f;
            // 中心リフトとコンポーネントだけに振り子を設定
            auto lift = dynamic_cast<Lift*>(liftTiles_[leftIndex]);
			auto liftComponent = lift->GetComponent<LiftComponent>();
            auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
            lift->SetPendulum(pendulum);
            liftComponent->SetPendulum(pendulum);
        }
        else // 奇数
        {
            // 中心のタイルのインデックスを計算
            size_t centerIndex = size / 2;
            // 添え字を保存
			tileCenterNum_ = centerIndex;
            // 中心のタイルの位置を取得
            centerPos = liftTiles_[centerIndex]->GetTransformComponent()->GetPosition();
			// 中心リフトとコンポーネントだけに振り子を設定
            auto lift = dynamic_cast<Lift*>(liftTiles_[centerIndex]);
            auto liftComponent = lift->GetComponent<LiftComponent>();
            auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
            lift->SetPendulum(pendulum);
            liftComponent->SetPendulum(pendulum);
        }
        // 振り子の中心を設定
        centerPendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(centerPos);
        isCenterMedian = true;
    }
    // 振り子が動いている場合
    if (owner_pendulum_movement_->GetPendulumMovement())
    {
		DirectX::SimpleMath::Vector3 centerLiftPos = liftTiles_[tileCenterNum_]->GetTransformComponent()->GetPosition();
        // 各タイルのオフセットを計算して一括で移動
        for (auto& tile : liftTiles_)
        {
            DirectX::SimpleMath::Vector3 currentPos = tile->GetTransformComponent()->GetPosition();
            float yOffset = centerLiftPos.y - currentPos.y; // 中心位置とのオフセットを計算
            float xOffset = centerLiftPos.x - currentPos.x; // 中心位置とのオフセットを計算
            tile->GetTransformComponent()->SetPosition(currentPos.x + xOffset, currentPos.y + yOffset);
        }
        // 振り子の中心点も更新
        DirectX::SimpleMath::Vector3 newPendulumPos = centerLiftPos;
        centerPendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(newPendulumPos);
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


