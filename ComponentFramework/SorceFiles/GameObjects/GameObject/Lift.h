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
//--------------------------------------------------
// ���t�g�I�u�W�F�N�g
//--------------------------------------------------
class Lift : public GameObject
{
public:
	enum class MoveState
	{
		length,	// �c�ړ�
		side,	// ���ړ�
	};

	Lift(MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos,GameManager* _gameManager);
	~Lift(void);

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;
	DirectX::SimpleMath::Vector3 maxPos_;	// �������̍ő���W
	DirectX::SimpleMath::Vector3 minPos_;	// �������̍ő���W
	TypeID GetType(void) override { return TypeID::Lift; }
private:
	bool switchFg_;			// �X�C�b�`�t���O
	MoveState moveState_;	// �ړ����

	class ColliderBaseComponent* collider_base_component_ = {};
	class EventBaseComponent* collider_event_component_ = {};
	class RenderComponent* spriteComponent_		= {};	// �摜�\��
	class VelocityComponent* velocityComponent_ = {};

	void OnCollisionEnter(GameObject* _other = nullptr) override;
};
#endif // _LIFT_OBJECT_H_
