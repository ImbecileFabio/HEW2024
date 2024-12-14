//==================================================
// [TimeZone.h] �^�C���]�[���w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F�^�C���]�[���I�u�W�F�N�g
//==================================================
#ifndef TIME_ZONE_H_
#define TIME_ZONE_H_
/*----- �C���N���[�h -----*/
#include "../GameObject.h"
//--------------------------------------------------
// �^�C���]�[���I�u�W�F�N�g
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