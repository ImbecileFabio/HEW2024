//==================================================
// [Lift.h] ���t�g�w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F���t�g�R���|�[�l���g
//==================================================
#ifndef LIFT_H_
#define LIFT_H_
/*----- �C���N���[�h -----*/
#include "../GameObject.h"
#include <SimpleMath.h>
/*----- �O���錾 -----*/
class VelocityComponent;
class SpriteComponent;
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

	SpriteComponent* spriteComponent_ = {};	// �摜�\��
};
#endif // _LIFT_OBJECT_H_