//=================================================================
// [EffectBase.h] hogehogehoge
// ���ҁF
//-----------------------------------------------------------------
// �����Fhogehogehgoe
//=================================================================
#ifndef DFFECT_BASE_H_
#define DFFECT_BASE_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// HOGE�I�u�W�F�N�g
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
