//=================================================================
// [SteePillar.h] �S���̃I�u�W�F�N�g�w�b�_
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�S���̃I�u�W�F�N�g�̐錾
//=================================================================
#ifndef STEE_PILLAR_H_
#define STEE_PILLAR_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
//--------------------------------------------------
// SteePillar�I�u�W�F�N�g
//--------------------------------------------------
class SteePillar : public GameObject
{
public:
	SteePillar(GameManager* _gameManager);
	~SteePillar(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillar; }
private:

};
#endif // STEE_PILLAR_H_
