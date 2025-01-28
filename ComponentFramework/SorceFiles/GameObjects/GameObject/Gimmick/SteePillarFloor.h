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
	SteePillarFloor(GameManager* _gameManager);
	~SteePillarFloor(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarFloor; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;

	void SetSteePillarFloorGroup(class SteePillarFloorGroup* _stee_pillar_floor_group);

	void SetIsDown(bool _isDown) { isDown_ = _isDown; }
private:
	class SteePillarFloorGroup* stee_pillar_floor_group_;	// 鉄柱の足場グループ

	class SpriteComponent* sprite_component_;
	class VelocityComponent* velocity_component_;
	class GravityComponent* gravity_component_;
	class ColliderBaseComponent* box_collider_component_;
	class EventBaseComponent* event_component_;

	bool isDown_ = false;	// 落下するかどうか
};
#endif // STEE_PILLAR_FLOOR_H_
