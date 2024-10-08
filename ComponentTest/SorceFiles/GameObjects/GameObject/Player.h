//==================================================
// [Player.h] �v���C���[�Q�[���I�u�W�F�N�g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�v���C���[�Q�[���I�u�W�F�N�g�̃N���X
//==================================================
#ifndef PLAYER_H_
#define PLAYER_H_

/*----- �C���N���[�h -----*/
#include "../GameObject.h"

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/

//--------------------------------------------------
// �v���C���[�N���X
//--------------------------------------------------
class Player : public GameObject
{
	Player(class GameManager* gameManager);
	~Player(void);

	void UpdateGameObject(float deltaTime) override;

	TypeID GetType(void) const override { return TypeID::Player; }

private:
	//class SpriteComponent* sprite_;
};

#endif	// PLAYER_H_
//==================================================
//				End of FIle
//==================================================

