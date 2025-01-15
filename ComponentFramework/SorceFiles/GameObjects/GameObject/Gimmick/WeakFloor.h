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

class GameManager;
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

	std::list<std::shared_ptr<Component>> WeakFloorComponentList;	// 各Floorが保持するコンポーネントを入れるリスト
	std::list<std::shared_ptr<Component>> WeakFloorList;			// 各Floorを入れるリスト
};

#endif  // WEAK_FLOOR_H_
