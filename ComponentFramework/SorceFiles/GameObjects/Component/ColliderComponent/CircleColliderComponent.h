//==================================================
// [BoxColliderComponent.h] �`�惂�W���[���w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F�����蔻��̃R���|�[�l���g�@����
//==================================================
#ifndef CIRCLE_COLLIDER_COMPONENT_H_
#define CIRCLE_COLLIDER_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include <memory>
#include <iostream>
#include <SimpleMath.h>
#include "ColliderBaseComponent.h"
/*----- �\���̐錾 -----*/
struct CIRCLE
{
	DirectX::SimpleMath::Vector3 position;
	float radius;
};
//--------------------------------------------------
// �~�̓����蔻��
//--------------------------------------------------
class CircleColliderComponent :public ColliderBaseComponent
{
public:
	CircleColliderComponent(GameObject* _owner, int _updateOrder = 50);
	~CircleColliderComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	bool CheckCollisionCollider(ColliderBaseComponent* _other) override;
	bool CheckCollisionCollider(CircleColliderComponent* _other) override;
	bool CheckCollisionCollider(BoxColliderComponent* _other) override;

	TypeID GetComponentType(void) const override { return TypeID::CircleColliderComponent; }

	void SetPosition(DirectX::SimpleMath::Vector3 _pos) { circle_.position = _pos; }
	CIRCLE GetCircleSize(void) const { return circle_; }
private:
	CIRCLE circle_;	// ���_�E���a
};

#endif 
// _CIRCLE_COLLIDER_COMPONENT_H_	
//{
	//	for (auto& otherCol : targetCols) {
	//		playerCol->CheckCollisionCollider(otherCol);
	//	}
	//}

	//class ColliderBaseComponent {
	//public:
	//	virtual bool CheckCollisionCollider(ColliderBaseComponent* _other) = 0;
	//	virtual bool CheckCollisionCollider(CircleColliderComponent* _other) = 0;
	//	virtual bool CheckCollisionCollider(BoxColliderComponent* _other) = 0;
	//}

	//bool CheckCollisionCollider(ColliderBaseComponent* _other) override {
	//	return _other->CheckCollisionCollider(this);
	//}
	//bool CheckCollisionCollider(CircleColliderComponent* _other) override {

	//}
	//bool CheckCollisionCollider(BoxColliderComponent* _other) override {

	//}