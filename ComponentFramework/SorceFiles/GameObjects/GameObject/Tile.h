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
//--------------------------------------------------
// タイルオブジェクト
//--------------------------------------------------
class Tile
	: public GameObject
{
public:
	Tile(GameManager* _gameManager);
	~Tile(void);

	void InitGameObject	 (void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Tile; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	// 所有するコンポーネント
	class RenderComponent* sprite_component_{};
	class ColliderBaseComponent* collider_component_{};
	class ColliderEventComponent* collider_event_component_{};


	// デバッグ用
	class DebugColliderDrawComponent* debug_collider_draw_component_{};
};
#endif	// TILE_H_