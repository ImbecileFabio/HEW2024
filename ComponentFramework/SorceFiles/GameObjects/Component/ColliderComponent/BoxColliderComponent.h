//==================================================
// [BoxColliderComponent.h] �`�惂�W���[���w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F�����蔻��̃R���|�[�l���g�@����
//==================================================
#ifndef BOX_COLLIDER_COMPONENT_H_
#define BOX_COLLIDER_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include <memory>
#include <SimpleMath.h>
#include "ColliderBaseComponent.h"
/*----- �\���̐錾 -----*/
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

	void SetPosition(DirectX::SimpleMath::Vector3 _pos) { position_ = _pos; }
	DirectX::SimpleMath::Vector4 GetBoxSize(void) const { return boxSize_; }

private:
	DirectX::SimpleMath::Vector3 position_{ 0.f, 0.f, 0.f };	// �����蔻��̌��_
	DirectX::SimpleMath::Vector4 boxSize_{ 0.f, 0.f, 0.f,0.f };	// �����蔻��̃T�C�Y ��E���E���E�E
};

#endif // BOX_COLLIDER_COMPONENT_H_