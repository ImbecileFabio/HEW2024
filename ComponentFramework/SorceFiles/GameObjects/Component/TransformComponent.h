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

using namespace DirectX::SimpleMath;
/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/

//--------------------------------------------------
// �p������R���|�[�l���g
//--------------------------------------------------
class TransformComponent : Component
{
public:
	TransformComponent(class GameObject* _owner, int updateOrder = 100);
	~TransformComponent(void);

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;

	void CallTransform(void);

	DirectX::SimpleMath::Vector3 GetPosition() { return position_; }
	DirectX::SimpleMath::Vector3 GetRotation() { return rotation_; }
	DirectX::SimpleMath::Vector3 GetScale() { return scale_; }

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; }

private:
	// SRT���i�p�����j
	DirectX::SimpleMath::Vector3 position_{0.f, 0.f, 0.f};
	DirectX::SimpleMath::Vector3 rotation_{0.f, 0.f, 0.f};
	DirectX::SimpleMath::Vector3 scale_{100.f, 100.f, 100.f};


};

#endif	// TRANSFORM_COMPONENT_H_