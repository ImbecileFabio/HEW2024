//=================================================================
// [hoge.h] hogehogehoge
// 著者：有馬啓太
//-----------------------------------------------------------------
// 説明：hogehogehgoe
//=================================================================
#ifndef HOGE_H_
#define HOGE_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// HOGEオブジェクト
//--------------------------------------------------
class hoge : public GameObject
{
public:
	hoge(GameManager* _gameManager);
	~hoge(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::HOGE; }
private:

};
#endif // HOGE_H_
