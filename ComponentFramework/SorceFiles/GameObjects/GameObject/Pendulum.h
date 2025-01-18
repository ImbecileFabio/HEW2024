//==================================================
// [Pendulum.h] �U��q�I�u�W�F�N�g�w�b�_
// ���ҁF���J����
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
	Pendulum(GameManager* _gameManager, Vector3 _fulcrum, bool _movement, float _pendulumAngle);
	~Pendulum(void);

	void InitGameObject(void)   override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Pendulum; }

	void OnCollisionEnter(GameObject* _other = nullptr) override;
private:
	// �q�I�u�W�F�N�g
	class TimeZone* time_zone_{};
	class Stick*		stick_{};
	// ���L����R���|�[�l���g
	class RenderComponent*			 sprite_component_	 {};
	class ColliderBaseComponent*	 collider_component_ {};
	class PendulumMovementComponent* pendulum_component_ {};
	class EventBaseComponent*	collider_event_component_{};
	class ChildrenComponent*		children_component_	 {};
};
#endif	// PENDULUM_H_