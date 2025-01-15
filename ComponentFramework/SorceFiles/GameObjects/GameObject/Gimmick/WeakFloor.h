//==================================================
// [WeakFloor.cpp] 脆い床オブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：脆い床の定義
//==================================================
#ifndef WEAK_FLOOR_H_
#define WEAK_FLOOR_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
//-----------------------------------------------------------------
// 脆い床のオブジェクト
//-----------------------------------------------------------------
class WeakFloor : public GameObject
{
public:
	WeakFloor(GameManager* _gameManager, int _MaxFloor = 3);
	~WeakFloor(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::WeakFloor; }
private:


	int max_floor_;
};

#endif  // WEAK_FLOOR_H_
