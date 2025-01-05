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
	enum class MoveState
	{
		length,		// �c�ړ�
		side,		// ���ړ�
		diagonal,	// �΂߈ړ�
	};
	Lift(GameManager* _gameManager);
	Lift(Lift::MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos,GameManager* _gameManager);

	~Lift(void);

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Lift; }	
	void OnCollisionEnter(GameObject* _other = nullptr) override;

	void SetMaxPos(DirectX::SimpleMath::Vector3 _maxPos);
	void SetMinPos(DirectX::SimpleMath::Vector3 _minPos);
	void SetPendulum(Pendulum* _pendulum);
	void SetMoveState(Lift::MoveState _moveState);

private:
	class ColliderBaseComponent* collider_base_component_ = {};
	class EventBaseComponent*	collider_event_component_ = {};
	class RenderComponent*		sprite_component_		  = {};	// �摜�\��
	class VelocityComponent*	velocity_component_		  = {};

	DirectX::SimpleMath::Vector3 maxPos_;	// �������̍ő���W
	DirectX::SimpleMath::Vector3 minPos_;	// �������̍ő���W

	DirectX::SimpleMath::Vector2 direction_;// �ړ�����

	Pendulum* pendulum_;					// �A�����������U��q
	bool switchFg_;							// �X�C�b�`�t���O
	MoveState moveState_;					// �ړ����
};
#endif // _LIFT_OBJECT_H_
