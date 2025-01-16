//=================================================================
// [WeakFloorGroup.h] 脆い床タイルを管理するグループクラス
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：脆い床タイルをまとめて管理するクラス
//=================================================================
#ifndef WEAK_FLOOR_GROUP_H_
#define WEAK_FLOOR_GROUP_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
#include <vector>
/*----- 前方宣言 -----*/
//--------------------------------------------------
// 脆い床タイルを管理するグループオブジェクト
//--------------------------------------------------
class WeakFloorGroup : public GameObject
{
public:
	WeakFloorGroup(GameManager* _gameManager);
	~WeakFloorGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::WeakFloorGroup; }

	void AddWeakFlootTile(GameObject* _tile);	// グループにタイルを追加
private:
	std::vector<GameObject*> weakFloorTiles_;	// グループが管理したいタイル
};
#endif // WEAK_FLOOR_GROUP_H_

