//==================================================
// [SteePillarFloorDown.h] 鉄柱ギミック落下コンポーネントヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：鉄柱ギミックの落下コンポーネント定義
//==================================================
#ifndef STEE_PILLAR_FLOOR_DOWN_H_
#define STEE_PILLAR_FLOOR_DOWN_H_
/*----- インクルード -----*/
#include "../../../Component.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// 鉄柱の床落下コンポーネント
//--------------------------------------------------
class SteePillarFloorMove : public Component
{
public:
    // 鉄柱の床の移動状態
    enum class FloorState
    {
        Up,
        Stop,
        Falling,
        OnLift,
        OnTile,
        OnLiftAndTile,
        Down,
    };
    SteePillarFloorMove(GameObject* _owner, int _updateOrder = 20);
    ~SteePillarFloorMove();

    void Init() override;
    void Uninit() override;
    void Update() override;

    TypeID GetComponentType(void) const override { return TypeID::SteePillarFloorDown; }
    
    void SetFloorState(FloorState _floorState) { floorState_ = _floorState; }
    FloorState GetFloorState() { return floorState_; }

	void SetLiftPosition(const DirectX::SimpleMath::Vector3& _liftPosition) { liftPosition_ = _liftPosition; }
	void SetTilePosition(const DirectX::SimpleMath::Vector3& _tilePosition) { tilePosition_ = _tilePosition; }

private:
    FloorState floorState_;	// 鉄柱の床状態

    class TransformComponent* owner_transform_{}; // キャッシュしたコンポーネント
    class VelocityComponent* owner_velocity_{};
    class GravityComponent* owner_gravity_{};
    class BoxColliderComponent* owner_box_collider_{};

    DirectX::SimpleMath::Vector2 direction_;    // 鉄柱床の移動する方向
	DirectX::SimpleMath::Vector3 liftPosition_; // リフトの位置
	DirectX::SimpleMath::Vector3 tilePosition_; // タイルの位置
};
#endif // STEE_PILLAR_COMPONENT_H_
