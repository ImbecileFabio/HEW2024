//==================================================
// [Player.h] プレイヤーゲームオブジェクトヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：プレイヤーゲームオブジェクトのクラス
//==================================================
#ifndef PLAYER_H_
#define PLAYER_H_

/*----- インクルード -----*/
#include "../GameObject.h"

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------------------
// プレイヤークラス
//--------------------------------------------------
class Player : public GameObject
{
	Player(class GameManager* gameManager);
	~Player(void);

	void UpdateGameObject(float deltaTime) override;

	TypeID GetType(void) const override { return TypeID::Player; }

private:
	//class SpriteComponent* sprite_;
};

#endif	// PLAYER_H_
//==================================================
//				End of FIle
//==================================================

