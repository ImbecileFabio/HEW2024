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
//--------------------------------------------------
// ���t�g�I�u�W�F�N�g
//--------------------------------------------------
class Lift : public GameObject
{
public:
	enum class LiftState {
		Move,
		Stop
	};

	enum class MoveState
	{
		length,		// �c�ړ�
		side,		// ���ړ�
		diagonalRight,	// �΂߈ړ�(�E)
		diagonalLeft,	// �΂߈ړ�(��)
	};
	Lift(GameManager* _gameManager);
	Lift(GameManager* _gameManager, Lift::MoveState _moveState, Vector3 _startpos, Vector3 _endPos, Pendulum* _pendulum);

	~Lift(void);

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Lift; }	
	void OnCollisionEnter(GameObject* _other = nullptr) override;

	void SetPendulum(Pendulum* _pendulum);

	void SetMoveState(Lift::MoveState _moveState);

	auto GetLiftState() { return lift_state_; }
private:
	class ColliderBaseComponent* collider_component_ = {};
	class EventBaseComponent*	collider_event_component_ = {};
	class RenderComponent*		sprite_component_		  = {};	// �摜�\��
	class VelocityComponent*	velocity_component_		  = {};
	class LiftComponent*		lift_component_ = {};

	LiftState lift_state_;		// ���t�g�̏��
	MoveState move_state_;		// �ړ�����
	int turn_count_;			// �؂�Ԃ��܂ł̎��� ����������Component�Ɉړ�������ׂ�

	Pendulum* pendulum_;					// �A�����������U��q
};
#endif // _LIFT_H_