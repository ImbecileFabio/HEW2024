//==================================================
// [Robot.h] タイルオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：床や壁のタイルオブジェクト
//==================================================
#ifndef ROBOT_H_
#define ROBOT_H_

/*----- インクルード -----*/
#include <memory>
#include "../GameObject.h"

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class SpriteComponent;
class ColliderBaseComponent;
//--------------------------------------------------
// タイルオブジェクト
//--------------------------------------------------
class Robot
	: public GameObject
{
public:
	Robot(GameManager* _gameManager);
	~Robot(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Robot; }

private:
	// 所有するコンポーネント
	SpriteComponent* sprite_component_{};
	ColliderBaseComponent* collider_component_{};
};
#endif	// ROBOT_H_