//==================================================
// [Player.h] �v���C���[�I�u�W�F�N�g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�v���C���[�̑��삨��ѐ�����s���N���X
//==================================================
#ifndef PLAYER_H_
#define PLAYER_H_

/*----- �C���N���[�h -----*/
#include <memory>
#include "../GameObject.h"

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/

//--------------------------------------------------
// �v���C���[�I�u�W�F�N�g
//--------------------------------------------------
class Player 
	: public GameObject
{
public:
	Player(GameManager* _gameManager);
	~Player(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Player; }

private:
	// ���L����R���|�[�l���g
	class SpriteComponent* sprite_component_{};
	class ColliderBaseComponent* collider_component_{};
	class VelocityComponent* velocity_component_{};
	
};
#endif	// PLAYER_H_