//==================================================
// [ColliderComponent.h] �`�惂�W���[���w�b�_
// ���ҁF����仓�
//--------------------------------------------------
// �����F�����蔻��̃R���|�[�l���g�@����
//==================================================
#ifndef COLLIDER_COMPONENT_H_
#define COLLIDER_COMPONENT_H_
/*----- �C���N���[�h -----*/
#include <memory>
#include <SimpleMath.h>
#include "../Component.h"
/*----- �\���̐錾 -----*/
struct CIRCLE
{
	DirectX::SimpleMath::Vector3 position;
	float radius;
};
/*----- �O���錾 -----*/
class GameObject;

//--------------------------------------------------
// �l�p�`�̓����蔻��
//--------------------------------------------------
class BoxColliderComponent :public Component
{
public:
	BoxColliderComponent(GameObject* _owner, int _updateOrder = 50);
	~BoxColliderComponent();

	void Init  (void) override;
	void Uninit(void) override;
	void Update(void) override;

	void CheckCollision(const DirectX::SimpleMath::Vector4& _other);

	TypeID GetComponentType(void) const override { return TypeID::BoxColliderComponent; }

	void SetPosition(DirectX::SimpleMath::Vector3 _pos)  { position_ = _pos; }
	DirectX::SimpleMath::Vector4 GetBoxSize(void) const	 { return boxSize_; }

	bool testFg;
private:
	DirectX::SimpleMath::Vector3 position_{ 0.f, 0.f, 0.f };	// �����蔻��̌��_
	DirectX::SimpleMath::Vector4 boxSize_ { 0.f, 0.f, 0.f,0.f };// �����蔻��̃T�C�Y ��E���E���E�E
};

class CircleColliderComponent :public Component
{
public:
	CircleColliderComponent(GameObject* _owner, int _updateOrder = 50);
	~CircleColliderComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	void CheckCollision(const CIRCLE& _other);

	TypeID GetComponentType(void) const override { return TypeID::CircleColliderComponent; }

	void SetPosition(DirectX::SimpleMath::Vector3 _pos) { circle_.position = _pos; }
	CIRCLE GetCircleSize(void) const { return circle_; }

	bool testFg;
private:
	CIRCLE circle_;	// ���_�E���a
};

#endif // COLLIDER_COMPONENT_H_