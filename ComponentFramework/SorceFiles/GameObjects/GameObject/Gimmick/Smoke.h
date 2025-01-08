//=================================================================
// [Smoke.h] ���M�~�b�N�̃w�b�_
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F���M�~�b�N�̒�`
//=================================================================
#ifndef SMOKE_H_
#define SMOKE_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// Smoke�I�u�W�F�N�g
//--------------------------------------------------
class Smoke : public GameObject
{
public:
	Smoke(GameManager* _gameManager);
	~Smoke(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Smoke; }
private:

};
#endif // SMOKE_H_
