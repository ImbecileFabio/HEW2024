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
	Lift(Lift::MoveState _moveState, float _moveDistance, GameManager* _gameManager);

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

	float maxMoveDistance_;								// �ő�ړ�����
	DirectX::SimpleMath::Vector2 traveledDistance_;		// �ݐψړ�����
	DirectX::SimpleMath::Vector2 direction_;			// �ړ�����
	DirectX::SimpleMath::Vector3 startPos_;				// �J�n�ʒu

	LiftState lift_state_;
	int turn_count_;									// �؂�Ԃ��܂ł̎���

	Pendulum* pendulum_;					// �A�����������U��q
	bool switchFg_;							// �X�C�b�`�t���O
	MoveState moveState_;					// �ړ����
};
#endif // _LIFT_H_