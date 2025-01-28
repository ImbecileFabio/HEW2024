//=================================================================
// [SteePillarFloor.h] �S���̑���I�u�W�F�N�g�w�b�_
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�S���̑���I�u�W�F�N�g�̐錾
//=================================================================
#ifndef STEE_PILLAR_FLOOR_H_
#define STEE_PILLAR_FLOOR_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// �S���̑���I�u�W�F�N�g
//--------------------------------------------------
class SteePillarFloor : public GameObject
{
public:
	SteePillarFloor(GameManager* _gameManager);
	~SteePillarFloor(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarFloor; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;

	void SetSteePillarFloorGroup(class SteePillarFloorGroup* _stee_pillar_floor_group);

	void SetIsDown(bool _isDown) { isDown_ = _isDown; }
private:
	class SteePillarFloorGroup* stee_pillar_floor_group_;	// �S���̑���O���[�v

	class SpriteComponent* sprite_component_;
	class VelocityComponent* velocity_component_;
	class GravityComponent* gravity_component_;
	class ColliderBaseComponent* box_collider_component_;
	class EventBaseComponent* event_component_;

	bool isDown_ = false;	// �������邩�ǂ���
};
#endif // STEE_PILLAR_FLOOR_H_
