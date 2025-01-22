//==================================================
// [WeakFloor.cpp] 脆い床オブジェクト
// 著者：有馬啓太
//--------------------------------------------------
// 説明：脆い床の定義
//==================================================
#ifndef WEAK_FLOOR_H_
#define WEAK_FLOOR_H_
/*----- インクルード -----*/
#include "../../GameObject.h"
//-----------------------------------------------------------------
// 脆い床のオブジェクト
//-----------------------------------------------------------------
class WeakFloor : public GameObject
{
public:
	WeakFloor(GameManager* _gameManager);
	~WeakFloor(void);

	void SetWeakFloorGroup(class WeakFloorGroup* _weak_floor_group);
	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::WeakFloor; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	// タイルを所有するグループ
	class WeakFloorGroup*				  weak_floor_group_{};	// 脆い床グループ
	// 所有するコンポーネント
	class RenderComponent*				  sprite_component_{};	// スプライト
	class ColliderBaseComponent*		collider_component_{};	// 当たり判定
	class ColliderEventComponent* collider_event_component_{};	// 当たり判定イベント
	class WeakFloorComponent*		  weak_floor_component_{};	// 脆い床ギミックコンポネート
};

#endif  // WEAK_FLOOR_H_
