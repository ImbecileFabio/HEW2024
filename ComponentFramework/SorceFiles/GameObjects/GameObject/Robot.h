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

	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	// ���L����R���|�[�l���g
	class SpriteComponent* sprite_component_{};
	class ColliderBaseComponent* collider_component_{};	// �����蔻��
	class ColliderEventComponent* collider_event_component_{};	// �����蔻��C�x���g
	class VelocityComponent* velocity_component_{};		// ���x

	// �f�o�b�O�p�R���|�[�l���g
	class DebugCollisionDrawComponent* debug_collision_draw_component_{};
};
#endif	// ROBOT_H_