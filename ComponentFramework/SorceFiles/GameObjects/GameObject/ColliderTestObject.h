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
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::ColliderTestObject; }
	// Object���ƂɏՓ˂����m�����Ƃ��̏����������Ƃ����͂�
	void OnCollisionEnter2D(GameObject& _other) override;	// �����蔻��̑S�̏���
	void OnCollisionExit2D(GameObject& _other) override {};	// �����蔻��̏I������
	void OnCollisionStay2D(GameObject& _other) override {};	// �����蔻��̌p������
	void OnTriggerEnter2D(GameObject& _other) override {};	// �g���K�[�̑S�̏���
	void OnTriggerExit2D(GameObject& _other) override {};	// �g���K�[�̏I������
	void OnTriggerStay2D(GameObject& _other) override {};	// �g���K�[�̌p������

private:
	SpriteComponent* spriteComponent_ = {};
	ColliderBaseComponent* colliderComponent_ = {};

	// �y���f�������̓����̃e�X�g
	AngularVelocityComponent* angVelCom_ = {};
	PendulumMovementComponent* penCom_ = {};	
	
private:

};
#endif // _TEST_COLLIDER_OBJECT_H_