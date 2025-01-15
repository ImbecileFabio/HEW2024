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
	enum class RobotState {
		Idle,
		Move,
		Fall,
		OnLift
	};

	Robot(GameManager* _gameManager);
	~Robot(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Robot; }

	void SetState(RobotState _state) { robot_state_ = _state; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	RobotState robot_state_;


	// ���L����R���|�[�l���g
	class RenderComponent* sprite_component_{};
	class ColliderBaseComponent* collider_component_{};	// �����蔻��
	class ColliderEventComponent* collider_event_component_{};	// �����蔻��C�x���g
	class VelocityComponent* velocity_component_{};		// ���x
	class GravityComponent* gravity_component_{};		// �d��
	class RobotMoveComponent* robot_move_component_{};	// ���{�b�g�̈ړ�
	class PushOutComponent* push_out_component_{};	// �����o��

};
#endif	// ROBOT_H_