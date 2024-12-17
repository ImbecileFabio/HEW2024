//==================================================
// [Pendulum.h] �U��q�I�u�W�F�N�g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�U��q�̐�����s���N���X
//==================================================
#ifndef PENDULUM_H_
#define PENDULUM_H_

/*----- �C���N���[�h -----*/
#include <memory>
#include <cmath>

#include "../GameObject.h"

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// �v���C���[�I�u�W�F�N�g
//--------------------------------------------------
class Pendulum
	: public GameObject
{
public:
	Pendulum(GameManager* _gameManager);
	~Pendulum(void);

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Pendulum; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	// �q�I�u�W�F�N�g
	class TimeZone* timeZone_ = nullptr;
	class Stick*	stick_	  = nullptr;
	// ���L����R���|�[�l���g
	class PendulumMovementComponent* pendulum_component_{};
	class RenderComponent*				sprite_component_   {};
	class ColliderBaseComponent*	    collider_component_ {};
	class ChildrenComponent*			children_component_ {};
	class EventBaseComponent*			collider_event_component{};
};
#endif	// PENDULUM_H_