//==================================================
// [ColliderBaseComponent.h] �`�惂�W���[���w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F�����蔻��̃x�[�X�R���|�[�l���g
// �I�u�W�F�N�g��ColliderBaseComponent��ǉ����āA
// �C���X�^���X��������Ƃ���Box||CircleComponent���g���Ă�������
//==================================================
#ifndef COLLIDER_BASE_COMPONENT_H_
#define COLLIDER_BASE_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include <memory>
#include <SimpleMath.h>
#include "../../Component.h"
/*----- �\���̐錾 -----*/
/*----- �O���錾 -----*/
class CircleColliderComponent;
class BoxColliderComponent;
//--------------------------------------------------
// �����蔻��x�[�X�N���X
//--------------------------------------------------
class ColliderBaseComponent :public Component
{
public:
	ColliderBaseComponent(GameObject* _owner, int _updateOrder = 50);
	~ColliderBaseComponent();

	void Init(void) override {};
	void Uninit(void) override {};
	void Update(void) override {};

	virtual bool CheckCollisionCollider(ColliderBaseComponent* _other) = 0;
	virtual bool CheckCollisionCollider(CircleColliderComponent* _other)= 0;
	virtual bool CheckCollisionCollider(BoxColliderComponent* _other) = 0;

	TypeID GetComponentType(void) const override { return TypeID::ColliderBaseComponent; }
protected:
};

#endif // COLLIDER_BASE_COMPONENT_H_