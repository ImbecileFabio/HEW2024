//==================================================
// [LiftComponent.h] ���t�g�R���|�[�l���g�w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F���t�g�R���|�[�l���g
//==================================================
#ifndef LIFT_COMPONENT_H_
#define LIFT_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include "../Component.h"
#include <SimpleMath.h>
/*----- �O���錾 -----*/
class GameObject;
class Pendulum;
class LiftComponent : public Component
{
public:
	enum class MoveState
	{
		length,		// �c�ړ�
		side,		// ���ړ�
		diagonal,	// �΂߈ړ�
	};

	LiftComponent(Pendulum* _pendulum, MoveState _moveState, DirectX::SimpleMath::Vector3 _maxPos, DirectX::SimpleMath::Vector3 _minPos,
		GameObject* _owner, int _updateOrder = 50);
	~LiftComponent(void);
	
	void Init  () override;
	void Uninit() override;
	void Update() override;

	TypeID GetComponentType(void) const override { return TypeID::LiftComponent; }

	DirectX::SimpleMath::Vector3 GetMaxPos(void) const { return maxPos_; }
	DirectX::SimpleMath::Vector3 GetMinPos(void) const { return minPos_; }
private:
	DirectX::SimpleMath::Vector3 maxPos_;	// �������̍ő���W
	DirectX::SimpleMath::Vector3 minPos_;	// �������̍ő���W

	Pendulum* pendulum_;			// ���t�g�̓����ƘA��������U��q�̎Q��
	bool switchFg_;					// �X�C�b�`�t���O
	MoveState moveState_;			// �ړ����
};

#endif // _LIFT_COMPONENT_H_