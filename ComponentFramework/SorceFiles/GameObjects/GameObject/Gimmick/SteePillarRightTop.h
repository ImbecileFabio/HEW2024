//=================================================================
// [SteePillarRightTop.h] �S���̃I�u�W�F�N�g�w�b�_
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�S���̃I�u�W�F�N�g�̐錾
//=================================================================
#ifndef STEE_PILLAR_RIGHT_TOP_H_
#define STEE_PILLAR_RIGHT_TOP_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
// SteePillarTop�I�u�W�F�N�g
//--------------------------------------------------
class SteePillarRightTop : public GameObject
{
public:
	SteePillarRightTop(GameManager* _gameManager);
	~SteePillarRightTop(void);
	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarRightTop; }
private:
	class RenderComponent* sprite_component_;
	class AnimationComponent* animation_component_;
};
#endif // STEE_PILLAR_RIGHT_TOP_H_
