//==================================================
// [PendulumComponent.h] �U��q���W���[���w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�U��q�̓�������߂�@�\�̐錾
//==================================================
#ifndef PENDULUM_COMPONENT_H_
#define PENDULUM_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include <memory>

#include "../Component.h"
/*----- �\���̐錾 -----*/






/*----- �O���錾 -----*/
class GameObject;

//--------------------------------------------------
// �U��q�R���|�[�l���g�N���X
//--------------------------------------------------
class PendulumComponent : public Component
{
public:
	PendulumComponent(GameObject* _owner, float _rength = 30.f, float _angle = 0,  int _updateOrder = 50);
	~PendulumComponent();

	void Init(void) override {};
	void Uninit(void) override;
	void Update(void) override;

	

	virtual TypeID GetComponentType(void) const override { return TypeID::PendulumComponent; }

private:
	float angle_{};		// �p�x
	float rength_{};	// ����
	float angularVelocity_{}; // �p���x


};

#endif	// PENDULUM_COMPONENT_H_