//=================================================================
// [SteePillarLeftTop.h] 鉄柱のオブジェクトヘッダ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：鉄柱のオブジェクトの宣言
//=================================================================
#ifndef STEE_PILLAR_LEFT_TOP_H_
#define STEE_PILLAR_LEFT_TOP_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
// SteePillarTopオブジェクト
//--------------------------------------------------
class SteePillarLeftTop : public GameObject
{
public:
	SteePillarLeftTop(GameManager* _gameManager);
	~SteePillarLeftTop(void);
	void InitGameObject	 (void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarLeftTop; }
private:
	class RenderComponent*		 sprite_component_;
	class AnimationComponent* animation_component_;
	
	bool offsetFg_;
	DirectX::SimpleMath::Vector2 offset_;
};
#endif // STEE_PILLAR_LEFT_TOP_H_
