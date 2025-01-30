//==================================================
// [Robot.h] ���{�b�g�I�u�W�F�N�g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���{�b�g�I�u�W�F�N�g�ł�
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
		OnLift,
		OnSmoke
	};

	Robot(GameManager* _gameManager);
	~Robot(void);

	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Robot; }

	void SetRobotState(RobotState _state) { robot_state_ = _state; }
	auto GetRobotState(void) { return robot_state_; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;
	//void OnCollisionStay(GameObject* _other = nullptr) override;
private:
	RobotState robot_state_;

	// ���L����R���|�[�l���g
	class SpriteComponent* sprite_component_{};
	class AnimationComponent* animation_component_{};	// �A�j���[�V����
	class FlipComponent* flip_component_{};	// ���]
	class BoxColliderComponent* collider_component_{};	// �����蔻��
	class ColliderEventComponent* collider_event_component_{};	// �����蔻��C�x���g
	class VelocityComponent* velocity_component_{};		// ���x
	class GravityComponent* gravity_component_{};		// �d��
	class RobotMoveComponent* robot_move_component_{};	// ���{�b�g�̈ړ�
	class PushOutComponent* push_out_component_{};	// �����o��
	class LiftInteractionComponent* lift_interaction_component_{};	// ���t�g�Ƃ̂����
	class SmokeInteractionComponent* smoke_interaction_component_{};	// ���Ƃ̂����

};
#endif	// ROBOT_H_