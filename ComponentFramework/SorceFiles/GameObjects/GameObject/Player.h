//==================================================
// [Player.h] プレイヤーオブジェクトヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：プレイヤーの操作および制御を行うクラス
//==================================================
#ifndef PLAYER_H_
#define PLAYER_H_

/*----- インクルード -----*/
#include <memory>
#include "../GameObject.h"

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/

//--------------------------------------------------
// プレイヤーオブジェクト
//--------------------------------------------------
class Player 
	: public GameObject
{
public:
	Player(GameManager* _gameManager);
	~Player(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Player; }

private:
	// 所有するコンポーネント
	class SpriteComponent* sprite_component_{};
	class ColliderBaseComponent* collider_component_{};
	class VelocityComponent* velocity_component_{};
	
};
#endif	// PLAYER_H_