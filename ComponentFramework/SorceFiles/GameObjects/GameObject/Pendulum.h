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
private:
	// ���L����R���|�[�l���g
	class RenderComponent*		   sprite_component_   {};
	class ColliderBaseComponent*	   collider_component_ {};
	class PendulumMovementComponent* pendulum_component_ {};
	class TimeZoneComponent*	       time_zone_component_{};
};
#endif	// PENDULUM_H_