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
	enum class TimeZoneState {
		Slow,
		Normal,
		Fast,
	};

	TimeZone(GameManager* _gameManager, GameObject* _ownerPendulum, int _order = 40);
	~TimeZone();

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::TimeZone; }
	void OnCollisionEnter(GameObject* _other = nullptr) override;

	void SetTimeZoneState(TimeZoneState _state) { state_ = _state; }
	auto GetState(void) { return state_; }

private:
	// �^�C���]�[���I�u�W�F�N�g�̏��L��
	GameObject* owner_pendulum_;

	class RenderComponent*				sprite_component_ = {};
	class ColliderBaseComponent* collider_base_component_ = {};
	class EventBaseComponent*		event_base_component_ = {};
	class TimeZoneComponent* time_zone_component_ = {};

	TimeZoneState state_;
};
#endif // TIME_ZONE_OBJECT_H_