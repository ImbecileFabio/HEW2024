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
private:
	SpriteComponent* spriteComponent = {};
	ColliderBaseComponent* colliderComponent = {};
private:
	// �h���N���X��
};
#endif // _TEST_COLLIDER_OBJECT_H_