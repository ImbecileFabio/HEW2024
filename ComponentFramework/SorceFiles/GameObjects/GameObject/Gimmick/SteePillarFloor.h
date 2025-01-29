//=================================================================
// [SteePillarFloor.h] 鉄柱の足場オブジェクトヘッダ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：鉄柱の足場オブジェクトの宣言
//=================================================================
#ifndef STEE_PILLAR_FLOOR_H_
#define STEE_PILLAR_FLOOR_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// 鉄柱の足場オブジェクト
//--------------------------------------------------
class SteePillarFloor : public GameObject
{
public:
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
	SteePillarFloor(GameManager* _gameManager);
	~SteePillarFloor(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarFloor; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;

	void SetSteePillarFloorGroup(class SteePillarFloorGroup* _stee_pillar_floor_group);

	void SetIsDown(bool _isDown) { isDown_ = _isDown; }
	void SetLeftTilePosition(const DirectX::SimpleMath::Vector3& _leftTilePosition) { leftTilePosition_ = _leftTilePosition; }
	void SetTilePosition(const DirectX::SimpleMath::Vector3& _tilePosition) { tilePosition_ = _tilePosition; }
	DirectX::SimpleMath::Vector3 GetTilePosition() { return tilePosition_; }
private:
	class SteePillarFloorGroup* stee_pillar_floor_group_;	// 鉄柱の足場グループ

	class SpriteComponent* sprite_component_;
	class VelocityComponent* velocity_component_;
	class GravityComponent* gravity_component_;
	class ColliderBaseComponent* box_collider_component_;
	class EventBaseComponent* event_component_;

	//class SteePillarFloorMove* stee_pillar_floor_move_;	// 鉄柱の足場の動作

	bool isDown_ = false;	// 落下するかどうか
	float offsetY_ = 50.0f;	// 落下する高さ

	DirectX::SimpleMath::Vector3 leftTilePosition_;
	DirectX::SimpleMath::Vector3 tilePosition_;
};
#endif // STEE_PILLAR_FLOOR_H_
