//==================================================
// [LiftComponent.h] ���t�g�R���|�[�l���g
// ���ҁF����仓�
//--------------------------------------------------
// �����F���t�g�̋����𐧌䂷��R���|�[�l���g
//==================================================
#ifndef LIFT_COMPONENT_H_
#define LIFT_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include <SimpleMath.h>

#include "../../Component.h"


/*----- �O���錾 -----*/
class Pendulum;

//--------------------------------------------------
// ���t�g�R���|�[�l���g
//--------------------------------------------------
class LiftComponent : public Component
{
public:
	enum class LiftComState {
		Move,
		Stop
	};

	enum class LiftComMoveState
	{
		length,		// �c�ړ�
		side,		// ���ړ�
		diagonalRight,	// �΂߈ړ�(�E)
		diagonalLeft,	// �΂߈ړ�(��)
	};

	LiftComponent(GameObject* _owner, Pendulum* _pendulum, LiftComMoveState _moveState, int _updateOrder = 50);
	~LiftComponent();

	void Init() override;
	void Uninit() override;
	void Update() override;

	TypeID GetComponentType(void) const override { return TypeID::LiftComponent; }

	bool CheckTraveledDistance();	// �ړ������̃`�F�b�N

	void SetLiftComState(LiftComState _state) { lift_com_state_ = _state; }
	auto GetLiftComState(void) { return lift_com_state_; }

	void SetLiftComMoveState(LiftComMoveState _state) { lift_com_move_state_ = _state; }
	auto GetLiftComMoveState(void) { return lift_com_move_state_; }

	void SetMaxMoveDistance(float _distance) { max_move_distance_ = _distance; }
	auto GetMaxMoveDistance(void) { return max_move_distance_; }

	void SetTraveledDistance(DirectX::SimpleMath::Vector2 _distance) { traveled_distance_ = _distance; }
	auto GetTraveledDistance(void) { return traveled_distance_; }

	void SetDirection(DirectX::SimpleMath::Vector2 _direction) { direction_ = _direction; }
	auto GetDirection(void) { return direction_; }

	void SetStartPos(DirectX::SimpleMath::Vector3 _pos) { start_pos_ = _pos; }
	auto GetStartPos(void) { return start_pos_; }

private:
	bool CheckLengthSideTraveled();	// �c���ړ��̈ړ������̃`�F�b�N
	bool CheckDiagonalTraveled();	// �΂߈ړ��̈ړ������̃`�F�b�N

	void InitDirection();	// �ړ������̏�����

	LiftComState lift_com_state_;					// ���t�g�̏��
	LiftComMoveState lift_com_move_state_;			// �ړ�����

	Pendulum* pendulum_;				// �A�����������U��q

	class TransformComponent* owner_transform_ = {};
	class VelocityComponent* owner_velocity_ = {};

	float max_move_distance_;								// �ő�ړ�����
	DirectX::SimpleMath::Vector2 traveled_distance_;		// �ݐψړ�����
	DirectX::SimpleMath::Vector2 direction_;			// �ړ�����
	DirectX::SimpleMath::Vector3 start_pos_;				// �J�n�ʒu
};

#endif // LIFT_COMPONENT_H_