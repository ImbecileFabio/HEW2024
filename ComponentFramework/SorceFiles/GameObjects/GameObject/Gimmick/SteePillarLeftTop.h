//=================================================================
// [SteePillarLeftTop.h] �S���̃I�u�W�F�N�g�w�b�_
// ���ҁF�L�n�[��
//-----------------------------------------------------------------
// �����F�S���̃I�u�W�F�N�g�̐錾
//=================================================================
#ifndef STEE_PILLAR_LEFT_TOP_H_
#define STEE_PILLAR_LEFT_TOP_H_
/*----- �C���N���[�h -----*/
#include "../../GameObject.h"
/*----- �O���錾 -----*/
// SteePillarTop�I�u�W�F�N�g
//--------------------------------------------------
class SteePillarLeftTop : public GameObject
{
public:
	SteePillarLeftTop(GameManager* _gameManager);
	~SteePillarLeftTop(void);
	void InitGameObject	 (void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::SteePillarLeftTop; }
private:
	class RenderComponent*		 sprite_component_;
	class AnimationComponent* animation_component_;
	
	bool offsetFg_;
	DirectX::SimpleMath::Vector2 offset_;
};
#endif // STEE_PILLAR_LEFT_TOP_H_
