//==================================================
// [TransformComponent.h] �p������R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�p������R���|�[�l���g�̃x�[�X
//==================================================
#ifndef TRANSFORM_COMPONENT_H_
#define TRANSFORM_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include <SimpleMath.h>
#include "../Component.h"
#include "../../subSystem/dx11helper.h"


/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/

//--------------------------------------------------
// �p������R���|�[�l���g
//--------------------------------------------------
class TransformComponent : Component
{
public:
	TransformComponent(class GameObject* owner, int updateOrder = 100);
	~TransformComponent(void);

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	void CallTransform(void);

	DirectX::SimpleMath::Vector3 GetPosition() const { return position_; }
	DirectX::SimpleMath::Vector3 GetRotation() const { return rotation_; }
	DirectX::SimpleMath::Vector3 GetScale() const { return scale_; }

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; }

private:
	// SRT���i�p�����j
	DirectX::SimpleMath::Vector3 position_ = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 rotation_ = DirectX::SimpleMath::Vector3(0.0f, 0.0f, 0.0f);
	DirectX::SimpleMath::Vector3 scale_ = DirectX::SimpleMath::Vector3(1.0f, 1.0f, 1.0f);


};

#endif	// TRANSFORM_COMPONENT_H_
//==================================================
//				End of FIle
//==================================================

