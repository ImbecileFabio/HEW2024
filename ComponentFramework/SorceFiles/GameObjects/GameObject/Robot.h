//==================================================
// [Robot.h] �^�C���I�u�W�F�N�g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F����ǂ̃^�C���I�u�W�F�N�g
//==================================================
#ifndef ROBOT_H_
#define ROBOT_H_

/*----- �C���N���[�h -----*/
#include <memory>
#include "../GameObject.h"

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class SpriteComponent;
class ColliderBaseComponent;
//--------------------------------------------------
// �^�C���I�u�W�F�N�g
//--------------------------------------------------
class Robot
	: public GameObject
{
public:
	Robot(GameManager* _gameManager);
	~Robot(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Robot; }

private:
	// ���L����R���|�[�l���g
	SpriteComponent* sprite_component_{};
	ColliderBaseComponent* collider_component_{};
};
#endif	// ROBOT_H_