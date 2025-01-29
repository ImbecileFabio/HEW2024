//==================================================
// [WallRight.h] 壁オブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：壁のタイルオブジェクト
//==================================================
#ifndef WALL_RIGHT_H_
#define WALL_RIGHT_H_

/*----- インクルード -----*/
#include <memory>
#include "../GameObject.h"

/*----- 構造体定義 -----*/
//--------------------------------------------------
// 壁オブジェクト
//--------------------------------------------------
class WallRight
	: public GameObject
{
public:
	WallRight(GameManager* _gameManager);
	~WallRight(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Wall; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	// 所有するコンポーネント
	class SpriteComponent* sprite_component_{};
	class ColliderBaseComponent* collider_component_{};
	class ColliderEventComponent* collider_event_component_{};


};
#endif	// WALL_RIGHT_H_