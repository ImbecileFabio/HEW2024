//==================================================
// [Tile.h] タイルオブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：床や壁のタイルオブジェクト
//==================================================
#ifndef TILE_H_
#define TILE_H_

/*----- インクルード -----*/
#include <memory>
#include "../GameObject.h"

/*----- 構造体定義 -----*/

/*----- 前方宣言 -----*/
class SpriteComponent;
class ColliderComponent;
//--------------------------------------------------
// タイルオブジェクト
//--------------------------------------------------
class Tile
	: public GameObject
{
public:
	Tile(GameManager* _gameManager);
	~Tile(void);
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Tile; }

private:
	// 所有するコンポーネント
	SpriteComponent* sprite_component_{};
	ColliderComponent* collider_component_{};
};
#endif	// TILE_H_