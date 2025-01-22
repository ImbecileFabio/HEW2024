//==================================================
// [TransformComponent.h] �p������R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�p������R���|�[�l���g�̃x�[�X
// Position, Rotation, Scale�̏�������
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
	TransformComponent(GameObject* _owner, int updateOrder = 0);
	~TransformComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	void SetSize(const float _x, const float _y)	{ SetSize(Vector3(_x, _y, 1.0f)); }
	void SetSize(const Vector3 _size)				{ size_ = _size; }

	void SetPosition(const float _x, const float _y, const float _z = 0.0f)	{ SetPosition(Vector3(_x, _y, _z)); }
	void SetPositionY(const float _y)										{ SetPosition(Vector3(position_.x, _y, position_.z)); }
	void SetPosition(const Vector3 _position)								{ position_ = _position; }

	void SetRotation(const float _z)			{ SetRotation(Vector3(0.0f, 0.0f, _z)); }
	void SetRotation(const Vector3 _rotation)	{ rotation_ = _rotation; }

	void SetScale(const float _x,const float _y)		{ SetScale(Vector3(_x, _y, 1.0f)); };
	void SetScale(const Vector3 _scale)					{ scale_ = _scale; }


	auto GetSize()     const { return size_; }
	auto GetPosition() const { return position_; }
	auto GetRotation() const { return rotation_; }
	auto GetScale()    const { return scale_; }
	

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; }


private:
	DirectX::SimpleMath::Vector3 size_{100.0f, 100.0f, 1.0f};	// �T�C�Y

	// SRT���i�p�����j
	DirectX::SimpleMath::Vector3 position_{ 0.0f, 0.0f, 0.0f };	// �ʒu
	DirectX::SimpleMath::Vector3 rotation_{ 0.0f, 0.0f, 0.0f };	// ��]
	DirectX::SimpleMath::Vector3 scale_{ 1.0f, 1.0f, 1.0f };		// �T�C�Y
};

#endif	// TRANSFORM_COMPONENT_H_