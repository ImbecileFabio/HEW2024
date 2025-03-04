//==================================================
// [Lift.h] ���t�g�w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F���t�g�I�u�W�F�N�g
//==================================================
#ifndef LIFT_H_
#define LIFT_H_
/*----- �C���N���[�h -----*/
#include "../GameObject.h"
#include <SimpleMath.h>
/*----- �O���錾 -----*/
class Pendulum;
class LiftGroup;
//--------------------------------------------------
// ���t�g�I�u�W�F�N�g
//--------------------------------------------------
class Lift : public GameObject
{
public:
	enum class LiftState {
		Move,
		Wait,
		Stop
	};

	enum class MoveState
	{
		length,		// �c�ړ�
		side,		// ���ړ�
		diagonalRight,	// �΂߈ړ�(�E)
		diagonalLeft,	// �΂߈ړ�(��)
	};
	Lift(GameManager* _gameManager, int _order = 45);
	Lift(GameManager* _gameManager, Lift::MoveState _moveState, Vector3 _startpos, Vector3 _endPos, Pendulum* _pendulum = nullptr);

	~Lift(void);

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Lift; }	
	void OnCollisionEnter(GameObject* _other = nullptr) override;

	void SetPendulum(Pendulum* _pendulum);

	void SetMoveState(Lift::MoveState _moveState);
	auto GetMoveState() { return move_state_; }

	void SetLiftState(LiftState _state) { lift_state_ = _state; }
	auto GetLiftState() { return lift_state_; }

	void SetLiftGroup(LiftGroup* _group) { lift_group_ = _group; }
	LiftGroup* GetLiftGroup() { return lift_group_; }
private:
	class ColliderBaseComponent* collider_component_ = {};
	class EventBaseComponent*	collider_event_component_ = {};
	class RenderComponent*		sprite_component_		  = {};	// �摜�\��
	class VelocityComponent*	velocity_component_		  = {};
	class LiftComponent*		lift_component_ = {};

	LiftState lift_state_;		// ���t�g�̏��
	MoveState move_state_;		// �ړ�����
	int turn_count_;			// �o�ߎ���
	int max_count_;				// �؂�Ԃ��܂ł̎���

	Pendulum* pendulum_;					// �A�����������U��q
	LiftGroup* lift_group_{};					// ���t�g���܂Ƃ߂�O���[�v


};
#endif // _LIFT_H_