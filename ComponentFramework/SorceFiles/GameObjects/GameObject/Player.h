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
class SpriteComponent;

//--------------------------------------------------
// プレイヤーオブジェクト
//--------------------------------------------------
class Player : public GameObject
{
public:
	Player(class GameManager* _gameManager);
	~Player(void);
	void UpdateGameObject(void) override;

	TypeID GetType(void) const { return TypeID::Player; }
private:
	// 所持するコンポーネントをここに書く
	std::unique_ptr<SpriteComponent> sprite_component_{};	// スプライトコンポーネント
};


#endif	// PLAYER_H_