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
private:
	class SteePillarLeftGroup* stee_pillar_left_group_;

	class SpriteComponent* sprite_component_;
	class AnimationComponent* animation_component_;
	class VelocityComponent* velocity_component_;
	class GravityComponent* gravity_component_;

	bool offsetFg_ = false;
	bool isDown_ = false;
	DirectX::SimpleMath::Vector2 offset_;

};
#endif // STEE_PILLAR_H_
