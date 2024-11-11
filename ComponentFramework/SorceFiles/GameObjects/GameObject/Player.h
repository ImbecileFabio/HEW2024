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
class SpriteComponent;

//--------------------------------------------------
// �v���C���[�I�u�W�F�N�g
//--------------------------------------------------
class Player : public GameObject
{
public:
	Player(class GameManager* _gameManager);
	~Player(void);
	void UpdateGameObject(void) override;

	TypeID GetType(void) const { return TypeID::Player; }
private:
	// ��������R���|�[�l���g�������ɏ���
	std::unique_ptr<SpriteComponent> sprite_component_{};	// �X�v���C�g�R���|�[�l���g
};


#endif	// PLAYER_H_