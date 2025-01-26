//=================================================================
// [SteePillarRightTop.h] 鉄柱のオブジェクトヘッダ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：鉄柱のオブジェクトの宣言
//=================================================================
#ifndef STEE_PILLAR_RIGHT_TOP_H_
#define STEE_PILLAR_RIGHT_TOP_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
// SteePillarTopオブジェクト
//--------------------------------------------------
class SteePillarRightTop : public GameObject
{
public:
	SteePillarRightTop(GameManager* _gameManager);
	~SteePillarRightTop(void);
	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarRightTop; }
private:
	class RenderComponent* sprite_component_;
	class AnimationComponent* animation_component_;
};
#endif // STEE_PILLAR_RIGHT_TOP_H_
