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

class GameManager;
//-----------------------------------------------------------------
// �Ƃ����̃I�u�W�F�N�g
//-----------------------------------------------------------------
class WeakFloor : public GameObject
{
public:
	WeakFloor(GameManager* _gameManager, int _MaxFloor = 3);
	~WeakFloor(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::WeakFloor; }
private:
	int max_floor_;

	std::list<std::shared_ptr<Component>> WeakFloorComponentList;	// �eFloor���ێ�����R���|�[�l���g�����郊�X�g
	std::list<std::shared_ptr<Component>> WeakFloorList;			// �eFloor�����郊�X�g
};

#endif  // WEAK_FLOOR_H_
