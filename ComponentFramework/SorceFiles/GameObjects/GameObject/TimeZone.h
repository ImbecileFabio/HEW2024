//==================================================
// [TimeZone.h] タイムゾーンヘッダ
// 著者：尾上莉奈
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
private:
	void OnCollisionEnter(GameObject* _other = nullptr) override;
};
#endif // TIME_ZONE_OBJECT_H_