//==================================================
// [ScanColliderComponent.h] ���m�p�̓����蔻��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F���{�b�g�ɓ��ڂ��邽�߂ɍ쐬
// ����ǂ̏����Ƃ邽�߂̃R���C�_�[
// 
//==================================================
#ifndef SCAN_COLLIDER_COMPONENT_H_
#define SCAN_COLLIDER_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include <memory>
#include <SimpleMath.h>
#include "ColliderBaseComponent.h"

using namespace DirectX::SimpleMath;


/*----- �O���錾 -----*/
class TransformComponent;

//--------------------------------------------------
// �l�p�`�̓����蔻��
//--------------------------------------------------
class ScanColliderComponent :public ColliderBaseComponent
{
public:
	ScanColliderComponent(GameObject* _owner, int _updateOrder = 5);
	~ScanColliderComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;


	bool CheckCollisionCollider(ColliderBaseComponent* _other) override;
	bool CheckCollisionCollider(BoxColliderComponent* _other) override;
	bool CheckCollisionCollider(CircleColliderComponent* _other) override;


	TypeID GetComponentType(void) const override { return TypeID::ScanColliderComponent; }


	// AABB�Z�b�^�[
	void SetAABB(const AABB& _localHitbox) { local_hit_box_ = _localHitbox; }


	// �����蔻��̈ʒu�����肵����
	void SetWorldHitBox(Vector3 _position);
	void SetWorldHitBox(const AABB& _worldHitbox) { world_hit_box_ = _worldHitbox; }
	auto GetWorldHitBox(void) const { return world_hit_box_; }


private:
	AABB local_hit_box_{};	// �����蔻��̋�`
	AABB world_hit_box_{};	// �����蔻��̋�`
};

#endif // SCAN_COLLIDER_COMPONENT_H_