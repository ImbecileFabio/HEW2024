//==================================================
// [WeakFloor.cpp] �Ƃ����I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�Ƃ����̒�`
//==================================================
#ifndef WEAK_FLOOR_H_
#define WEAK_FLOOR_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
//-----------------------------------------------------------------
// �Ƃ����̃I�u�W�F�N�g
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
	// �^�C�������L����O���[�v
	class WeakFloorGroup*				  weak_floor_group_{};	// �Ƃ����O���[�v
	// ���L����R���|�[�l���g
	class RenderComponent*				  sprite_component_{};	// �X�v���C�g
	class ColliderBaseComponent*		collider_component_{};	// �����蔻��
	class ColliderEventComponent* collider_event_component_{};	// �����蔻��C�x���g
	class WeakFloorComponent*		  weak_floor_component_{};	// �Ƃ����M�~�b�N�R���|�l�[�g
};

#endif  // WEAK_FLOOR_H_
