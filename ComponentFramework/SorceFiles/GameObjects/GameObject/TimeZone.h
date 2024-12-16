//==================================================
// [TimeZone.h] タイムゾーンヘッダ
// 著者：有馬啓太
//--------------------------------------------------
// 説明：タイムゾーンオブジェクト
//==================================================
#ifndef TIME_ZONE_H_
#define TIME_ZONE_H_
/*----- インクルード -----*/
#include "../GameObject.h"
//--------------------------------------------------
// タイムゾーンオブジェクト
//--------------------------------------------------
class TimeZone : public GameObject
{
public:
	TimeZone(GameManager* _gameManager);
	~TimeZone();

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::TimeZone; }
	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	class RenderComponent*				sprite_component_ = {};
	class ColliderBaseComponent* collider_base_component_ = {};
	class EventBaseComponent*		event_base_component_ = {};
};
#endif // TIME_ZONE_OBJECT_H_