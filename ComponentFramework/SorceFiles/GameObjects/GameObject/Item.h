//==================================================
// [Item.h] アイテムヘッダ
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：アイテムオブジェクト
//==================================================
#ifndef ITEM_H_
#define ITEM_H_
#include "../GameObject.h"
class Item :
    public GameObject
{
public:
    Item(GameManager* _gameManager);
    ~Item();

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Item; }
	void OnCollisionEnter(GameObject* _other = nullptr) override;

private:
	class SpriteComponent* sprite_component_ = {};
	class EventBaseComponent* event_base_component_ = {};
	class ColliderBaseComponent* collider_base_component_ = {};
};
#endif // ITEM_H_