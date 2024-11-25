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

/*----- �\���̒�` -----*/



/*----- �O���錾 -----*/
class SpriteComponent;
class PendulumComponent;
//--------------------------------------------------
// �v���C���[�I�u�W�F�N�g
//--------------------------------------------------
class Pendulum
	: public GameObject
{
public:
	Pendulum(GameManager* _gameManager);
	~Pendulum(void);
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::Pendulum; }

private:
	// ���L����R���|�[�l���g
	SpriteComponent* sprite_component_{};
	PendulumComponent* pendulum_component_{};
};
#endif	// PENDULUM_H_