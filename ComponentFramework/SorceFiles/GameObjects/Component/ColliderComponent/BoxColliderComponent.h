//==================================================
// [BoxColliderComponent.h] �l�p�̓����蔻��R���|�[�l���g�̃w�b�_�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����F�l�p�̓����蔻��̃R���|�[�l���g
// 
// 24/12/21 arima AABB�֘A��ǉ����Ă݂�
//==================================================
#ifndef BOX_COLLIDER_COMPONENT_H_
#define BOX_COLLIDER_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include <memory>
#include <SimpleMath.h>
#include "ColliderBaseComponent.h"

using namespace DirectX::SimpleMath;

/*----- �\���̒�` -----*/
struct AABB {
	Vector2 min_;		// ��`�̍���
	Vector2 max_;		// ��`�̉E��
};

/*----- �O���錾 -----*/
class TransformComponent;

//--------------------------------------------------
// �l�p�`�̓����蔻��
//--------------------------------------------------
class BoxColliderComponent :public ColliderBaseComponent
{
public:
	BoxColliderComponent(GameObject* _owner, int _updateOrder = 50);
	~BoxColliderComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;


	bool CheckCollisionCollider(ColliderBaseComponent* _other) override;
	bool CheckCollisionCollider(CircleColliderComponent* _other) override;
	bool CheckCollisionCollider(BoxColliderComponent* _other) override;

	TypeID GetComponentType(void) const override { return TypeID::BoxColliderComponent; }

	// �����蔻��̈ʒu�����肵����
	void SetWorldHitBox(Vector3 _position);
	auto GetWorldHitBox(void) const { return hit_box_; }
	

private:
	AABB hit_box_{};	// �����蔻��̋�`
};

#endif // BOX_COLLIDER_COMPONENT_H_