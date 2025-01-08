//=================================================================
// [Smoke.h] 煙ギミックのヘッダ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：煙ギミックの定義
//=================================================================
#ifndef SMOKE_H_
#define SMOKE_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// Smokeオブジェクト
//--------------------------------------------------
class Smoke : public GameObject
{
public:
	Smoke(GameManager* _gameManager);
	~Smoke(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Smoke; }
private:

};
#endif // SMOKE_H_
