//==================================================
// [Player.h] プレイヤーオブジェクトヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：プレイヤーの操作および制御を行うクラス
//==================================================
#ifndef PLAYER_H_
#define PLAYER_H_

/*----- インクルード -----*/
#include "../GameObject.h"
/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------------------
// プレイヤーオブジェクト
//--------------------------------------------------
class Player : public GameObject
{
public:
	Player(class GameManager* _gameManager);
	~Player();

	void UpdateGameObject(void) override;

	virtual TypeID GetType(void) const { return TypeID::Player; }
private:
	class SpriteComponent* sprite_ = nullptr;
	class TransformComponent* transform_ = nullptr;
};


#endif	// PLAYER_H_
//==================================================
//				End of FIle
//==================================================

