//=================================================================
// [LiftGroup.h] リフトグループオブジェクト
// 著者：尾上莉奈
//-----------------------------------------------------------------
// 説明：リフトをまとめて管理するクラス
//=================================================================
#ifndef LIFT_GROUP_H_
#define LIFT_GROUP_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
/*----- 前方宣言 -----*/
//--------------------------------------------------
// リフトグループオブジェクト
//--------------------------------------------------
class LiftGroup : public GameObject
{
public:
	LiftGroup(GameManager* _gameManager);
	~LiftGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::LiftGroup; }
private:

};
#endif // LIFT_GROUP_H_
