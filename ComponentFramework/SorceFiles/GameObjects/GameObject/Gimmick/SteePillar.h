//=================================================================
// [SteePillar.h] 鉄柱のオブジェクトヘッダ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：鉄柱のオブジェクトの宣言
//=================================================================
#ifndef STEE_PILLAR_H_
#define STEE_PILLAR_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// SteePillarオブジェクト
//--------------------------------------------------
class SteePillar : public GameObject
{
public:
	SteePillar(GameManager* _gameManager);
	~SteePillar(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillar; }
private:

};
#endif // STEE_PILLAR_H_
