//=================================================================
// [SteePillarLeft.h] 左鉄柱のオブジェクトヘッダ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：左鉄柱のオブジェクトの宣言
//=================================================================
#ifndef STEE_PILLAR_LEFT_H_
#define STEE_PILLAR_LEFT_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
// SteePillarLeftオブジェクト
//--------------------------------------------------
class SteePillarLeft : public GameObject
{
public:
	SteePillarLeft(GameManager* _gameManager);
	~SteePillarLeft(void);
	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarLeft; }

	void SetPillarLeftGroup(class SteePillarLeftGroup* _group);

	void SetIsDown(bool _fg) { isDown_ = _fg; }
	bool GetIsDown() { return isDown_; }
	void SetIsFloorVelocity(bool _fg) { isFloorDown_ = _fg; }
	bool GetIsFloorVelocity() { return isFloorDown_; }

	void SetFloorPosition(DirectX::SimpleMath::Vector3 _floorPos)  { floorPosition_ = _floorPos; }
	void SetFloorOffset(DirectX::SimpleMath::Vector3 _floorOffset) { floorOffset_ = _floorOffset; }
	void SetBoxCollider(class BoxColliderComponent* _box) { box_collider_ = _box; }
	void SetEvent(class ColliderEventComponent* _event) { event_component_ = _event; }
private:
	class SteePillarLeftGroup* stee_pillar_left_group_;

	class SpriteComponent* sprite_component_;
	class AnimationComponent* animation_component_;
	class VelocityComponent* velocity_component_;
	class GravityComponent* gravity_component_;
	class BoxColliderComponent* box_collider_{};
	class ColliderEventComponent* event_component_{};

	bool offsetFg_ = false;
	bool isFloorDown_ = false;	// 鉄柱が落下したときに行うオフセット処理
	bool isDown_ = false;
	DirectX::SimpleMath::Vector3 offset_;
	DirectX::SimpleMath::Vector3 floorOffset_;		// 鉄柱の床が落下したときのオフセット値
	DirectX::SimpleMath::Vector3 floorPosition_;	// 鉄柱の床の座標を保存

};
#endif // STEE_PILLAR_H_
