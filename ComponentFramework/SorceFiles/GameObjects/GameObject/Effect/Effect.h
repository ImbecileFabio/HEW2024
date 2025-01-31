//=================================================================
// [EffectBase.h] hogehogehoge
// 著者：
//-----------------------------------------------------------------
// 説明：hogehogehgoe
//=================================================================
#ifndef DFFECT_BASE_H_
#define DFFECT_BASE_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// HOGEオブジェクト
//--------------------------------------------------
class EffectBase : public GameObject
{
public:
	EffectBase(GameManager* _gameManager);
	~EffectBase(void);

	virturl void InitGameObject(void) override;
	virturl void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::EffectBase; }
private:

};
#endif // DFFECT_BASE_H_
