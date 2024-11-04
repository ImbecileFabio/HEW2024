//==================================================
// [Player.h] �v���C���[�I�u�W�F�N�g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�v���C���[�̑��삨��ѐ�����s���N���X
//==================================================
#ifndef PLAYER_H_
#define PLAYER_H_

/*----- �C���N���[�h -----*/
#include "../GameObject.h"
/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/

//--------------------------------------------------
// �v���C���[�I�u�W�F�N�g
//--------------------------------------------------
class Player : public GameObject
{
public:
	Player(class GameManager* _gameManager);
	~Player();

	void UpdateGameObject(void) override;

	virtual TypeID GetType(void) const { return TypeID::Player; }
private:
	class SpriteComponent* sprite_ = nullptr;
	class TransformComponent* transform_ = nullptr;
};


#endif	// PLAYER_H_
//==================================================
//				End of FIle
//==================================================

