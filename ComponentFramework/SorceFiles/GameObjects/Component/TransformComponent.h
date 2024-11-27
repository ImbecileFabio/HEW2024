//==================================================
// [TransformComponent.h] �p������R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�p������R���|�[�l���g�̃x�[�X
//==================================================
#ifndef TRANSFORM_COMPONENT_H_
#define TRANSFORM_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include <memory>
#include <SimpleMath.h>

#include "../Component.h"

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameObject;


using namespace DirectX::SimpleMath;
//--------------------------------------------------
// �p������R���|�[�l���g
//--------------------------------------------------
class TransformComponent : public Component
{
public:
	TransformComponent(GameObject* _owner, int updateOrder = 50);
	~TransformComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	// Setter
	void SetPosition(const Vector3& _position) { position_ = _position; }
	void SetRotation(const Vector3& _rotation) { position_ = _rotation; }
	void SetScale(const Vector3& _scale) { position_ = _scale; }
	// Getter
	auto& GetPosition() const { return position_; }
	auto& GetRotation() const { return rotation_; }
	auto& GetScale() const { return scale_; }

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; }


private:
	// SRT���i�p�����j
	DirectX::SimpleMath::Vector3 position_{ 0.f, 0.f, 0.f };
	DirectX::SimpleMath::Vector3 rotation_{ 0.f, 0.f, 0.f };
	DirectX::SimpleMath::Vector3 scale_{ 1.f, 1.f, 1.f };


};

#endif	// TRANSFORM_COMPONENT_H_