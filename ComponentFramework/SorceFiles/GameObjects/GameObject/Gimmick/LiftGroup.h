//=================================================================
// [LiftGroup.h] ���t�g�O���[�v�I�u�W�F�N�g
// ���ҁF����仓�
//-----------------------------------------------------------------
// �����F���t�g���܂Ƃ߂ĊǗ�����N���X
//=================================================================
#ifndef LIFT_GROUP_H_
#define LIFT_GROUP_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// ���t�g�O���[�v�I�u�W�F�N�g
//--------------------------------------------------
class LiftGroup : public GameObject
{
public:
	LiftGroup(GameManager* _gameManager);
	~LiftGroup(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::LiftGroup; }
private:

};
#endif // LIFT_GROUP_H_
