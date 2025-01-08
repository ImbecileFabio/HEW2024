//=================================================================
// [Pulley.h] ���ԃM�~�b�N�̃w�b�_
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F���ԃM�~�b�N�̐錾
//=================================================================
#ifndef PULLEY_H_
#define PULLEY_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// Pulley�I�u�W�F�N�g
//--------------------------------------------------
class Pulley : public GameObject
{
public:
	Pulley(GameManager* _gameManager);
	~Pulley(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Pulley; }
private:

};
#endif // PULLEY_H_
