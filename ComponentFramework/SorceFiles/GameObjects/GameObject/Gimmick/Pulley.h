//=================================================================
// [Pulley.h] 滑車ギミックのヘッダ
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：滑車ギミックの宣言
//=================================================================
#ifndef PULLEY_H_
#define PULLEY_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// Pulleyオブジェクト
//--------------------------------------------------
class Pulley : public GameObject
{
public:
	Pulley(GameManager* _gameManager);
	~Pulley(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Pulley; }
private:

};
#endif // PULLEY_H_
