//=================================================================
// [SteePillarRight.h] 鉄柱のオブジェクトヘッダ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：鉄柱のオブジェクトの宣言
//=================================================================
#ifndef STEE_PILLAR_H_
#define STEE_PILLAR_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
// SteePillarRightオブジェクト
//--------------------------------------------------
class SteePillarRight : public GameObject
{
public:
	SteePillarRight(GameManager* _gameManager);
	~SteePillarRight(void);
	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarRight; }

	void SetPillarRightGroup(class SteePillarRightGroup* _group);

	void SetIsDown(bool _fg) { isDown_ = _fg; }
	bool GetIsDown() { return isDown_; }
	void SetIsFloorVelocityStop(bool _fg) { isFloorVelocityStop_ = _fg; }
	bool GetIsFloorVelocityStop() { return isFloorVelocityStop_; }

	void SetFloorPosition(DirectX::SimpleMath::Vector3 _pos) { floorPosition_ = _pos; }
private:
	class SteePillarRightGroup* stee_pillar_right_group_;
	class SpriteComponent*			   sprite_component_;
	class AnimationComponent*		animation_component_;
	class VelocityComponent*		 velocity_component_;
	class GravityComponent*			  gravity_component_;

	DirectX::SimpleMath::Vector3 floorPosition_;
	DirectX::SimpleMath::Vector3 offset_;

	bool isFloorVelocityStop_ = false;
	bool isDown_   = false;
};
#endif // STEE_PILLAR_H_
