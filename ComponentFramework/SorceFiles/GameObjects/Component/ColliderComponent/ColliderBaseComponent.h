//==================================================
// [ColliderBaseComponent.h] �����蔻��̊��N���X�R���|�[�l���g�̃w�b�_�t�@�C��
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

using namespace DirectX::SimpleMath;
/*----- �\���̐錾 -----*/
struct AABB {
	Vector2 min_;		// ��`�̍���
	Vector2 max_;		// ��`�̉E��
};

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
	virtual ~ColliderBaseComponent();

	void Init(void) override {};
	void Uninit(void) override {};
	void Update(void) override {};

	virtual bool CheckCollisionCollider(ColliderBaseComponent* _other) = 0;
	virtual bool CheckCollisionCollider(CircleColliderComponent* _other)= 0;
	virtual bool CheckCollisionCollider(BoxColliderComponent* _other) = 0;

	bool GetHitFg(void) { return hitFg_; }
	void SetHitFg(bool _hitFg) { hitFg_ = _hitFg; }
	// �قڋ�`�p
	void SetSize(const float& _x, const float& _y) { SetSize(Vector3(_x, _y, 1.0f)); }
	void SetSize(const Vector3& _size) { size_ = _size; }
	auto GetSize(void) { return size_; }

	void SetOffset(const float _x, const float _y) { SetOffset(Vector3(_x, _y, 0.0f)); }
	void SetOffset(const Vector3 _offset) { offset_ = _offset; }
	auto GetOffset(void) { return offset_; }

	TypeID GetComponentType(void) const override { return TypeID::ColliderBaseComponent; }
protected:
	bool hitFg_ = false;	// �������Ă��邩�ǂ���
	Vector3 size_{ 100.0f, 100.0f, 0.0f };		// �T�C�Y
	Vector3 offset_{0.0f, 0.0f, 0.0f};		// �I�t�Z�b�g
};
#endif // COLLIDER_BASE_COMPONENT_H_