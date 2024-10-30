//==================================================
// [Camera.h] カメラオブジェクトヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：カメラの処理を宣言
//==================================================
#ifndef PLAYER_H_
#define PLAYER_H_

/*----- インクルード -----*/
#include "../GameObject.h"
/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------------------
// カエラオブジェクト
//--------------------------------------------------
class Player : public GameObject
{
public:
	Player(class GameManager* gameManager);
	~Player(void);

	void UpdateGameObject(void) override;

	virtual TypeID GetType(void) const { return TypeID::Player; }
private:
	class SpriteComponent* sprite_;
};


#endif	// PLAYER_H_
//==================================================
//				End of FIle
//==================================================

