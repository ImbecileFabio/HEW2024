//==================================================
// [ColliderTestObject.h] �����蔻����e�X�g����I�u�W�F�N�g�w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F�v���C���[�̑��삨��ѐ�����s���N���X
//==================================================
#ifndef COLLIDERTESTOBJECT_H_
#define COLLIDERTESTOBJECT_H_

/*----- �C���N���[�h -----*/
#include <memory>
#include <array>
#include "../GameObject.h"
/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class SpriteComponent;
class BoxColliderComponent;
class CircleColliderComponent;
//--------------------------------------------------
// �����蔻��e�X�g�p�I�u�W�F�N�g
//--------------------------------------------------
class ColliderTestObject
	: public GameObject
{
public:
	ColliderTestObject(GameManager* _gameManager);
	~ColliderTestObject(void);
	void UpdateGameObject(void) override;

	TypeID GetType(void) override { return TypeID::ColliderTestObject; }

private:
	// ���L����R���|�[�l���g
	SpriteComponent* sprite_component_{};		// �X�v���C�g
	CircleColliderComponent* circle_collider_component_{};		// �����蔻��i�l�p�j
};
#endif	// COLLIDERTESTOBJECT_H_