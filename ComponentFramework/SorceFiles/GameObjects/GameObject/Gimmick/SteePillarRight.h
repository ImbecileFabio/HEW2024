//=================================================================
// [SteePillarRight.h] �S���̃I�u�W�F�N�g�w�b�_
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�S���̃I�u�W�F�N�g�̐錾
//=================================================================
#ifndef STEE_PILLAR_H_
#define STEE_PILLAR_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
// SteePillarRight�I�u�W�F�N�g
//--------------------------------------------------
class SteePillarRight : public GameObject
{
public:
	SteePillarRight(GameManager* _gameManager);
	~SteePillarRight(void);
	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarRight; }

	void SetPillarRightGroup(class SteePillarRightGroup* _group);
private:
	class SteePillarRightGroup* stee_pillar_right_group_;
	class RenderComponent* sprite_component_;
};
#endif // STEE_PILLAR_H_
