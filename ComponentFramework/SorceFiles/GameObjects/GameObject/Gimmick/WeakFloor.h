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

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

private:
};

#endif  // WEAK_FLOOR_H_
