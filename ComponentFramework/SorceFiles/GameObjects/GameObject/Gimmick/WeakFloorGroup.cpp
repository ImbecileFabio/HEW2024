//=================================================================
// [WeakFloorGroup.cpp] WeakFloorGroupソースファイル
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：WeakFloorGroup実装
//=================================================================
/*----- インクルード -----*/
#include "WeakFloorGroup.h"
#include "WeakFloor.h"
#include "../../GameObject/Pendulum.h"
#include "../../Component/PendulumMovementComponent.h"
#include "../../Component/EventComponent/ColliderEventComponent.h"
#include "../../Component/ColliderComponent/BoxColliderComponent.h"
//--------------------------------------------------
// @brief コンストラクタ
//--------------------------------------------------
WeakFloorGroup::WeakFloorGroup(GameManager* _gameManager)
	:GameObject(_gameManager, "WeakFloorGroup")
{
	this->InitGameObject();
}
//--------------------------------------------------
// @brief デストラクタ
//--------------------------------------------------
WeakFloorGroup::~WeakFloorGroup(void)
{
}
//--------------------------------------------------
// @brief 初期化処理
//--------------------------------------------------
void WeakFloorGroup::InitGameObject(void)
{
}
//--------------------------------------------------
// @brief 更新処理
//--------------------------------------------------
void WeakFloorGroup::UpdateGameObject(void)
{
    // 振り子を中心に調整する処理
    if (!isCenterMedian)
    {
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
        centerPendulum_->GetComponent<PendulumMovementComponent>()->SetPendulumFulcrum(centerPos);
        isCenterMedian = true;
    }
	// 脆い床が壊れたかどうかかつ、振り子が動いている場合
	if (isWeakFloorBreak_ && owner_pendulum_movement_->GetPendulumMovement())
	{
		// グループの方で脆いタイルを一括で変更をかける この処理は一度だけ
		for (auto& tile : weakFloorTiles_)
		{
			tile->GetComponent<RenderComponent>()->SetState(RenderComponent::State::notDraw);
			tile->GetComponent<EventBaseComponent>()->RemoveEvent();
			tile->SetState(GameObject::State::Paused);
		}
		auto pendulum = dynamic_cast<Pendulum*>(centerPendulum_);
		pendulum->NotDrawAndStopPendulum();
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

