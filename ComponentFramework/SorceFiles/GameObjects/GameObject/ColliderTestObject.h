//==================================================
// [TestColliderObject.h] �`�惂�W���[���w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F�����蔻����e�X�g����I�u�W�F�N�g
//==================================================
#ifndef TEST_COLLIDER_OBJECT_H_
#define TEST_COLLIDER_OBJECT_H_
/*----- �C���N���[�h -----*/
#include <memory>
#include "../GameObject.h"
/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameObject;
class ColliderBaseComponent;
class SpriteComponent;
class CallBackManager;
class AngularVelocityComponent;
class PendulumMovementComponent;
//--------------------------------------------------
// �����蔻��e�X�g����I�u�W�F�N�g
//--------------------------------------------------
class ColliderTestObject : public GameObject
{
public:
	ColliderTestObject(GameManager* _gameManager);
	~ColliderTestObject(void);
	
	void InitGameObject(void) override;
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::ColliderTestObject; }
private:
	SpriteComponent* spriteComponent_ = {};
	ColliderBaseComponent* colliderComponent_ = {};

	// �y���f�������̓����̃e�X�g
	AngularVelocityComponent* angVelCom_ = {};
	PendulumMovementComponent* penCom_ = {};	
	
private:
	// �����蔻��������������I�u�W�F�N�g��ColliderManager�ɓo�^����
	// GameManager���Ȃ���GetRenderer()���g���Ȃ����@RIP
	//ColliderManager* p_colliderManager_ = {};
	//CallBackManager* p_callBackManager_ = {};	// �R�[���o�b�N���g�p�������I�u�W�F�N�g�ɔz�u
};
#endif // _TEST_COLLIDER_OBJECT_H_