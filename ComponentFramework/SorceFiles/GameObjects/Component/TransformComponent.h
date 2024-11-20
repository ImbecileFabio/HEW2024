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
//--------------------------------------------------
// �p������R���|�[�l���g
//--------------------------------------------------
class TransformComponent : Component
{
public:
	TransformComponent(GameObject* _owner, int updateOrder = 50);
	~TransformComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;


	auto& GetPosition() { return position_; }
	auto& GetRotation() { return rotation_; }
	auto& GetScale() { return scale_; }

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; }

	/////////////////////////////////////////////////////////
	// ����public�ɂ��Ă��邪�A�{����private�ɂ���
	// SRT���i�p�����j
	DirectX::SimpleMath::Vector3 position_{ 0.f, 0.f, 0.f };
	DirectX::SimpleMath::Vector3 rotation_{ 0.f, 0.f, 0.f };
	DirectX::SimpleMath::Vector3 scale_{ 1.f, 1.f, 1.f };
	/////////////////////////////////////////////////////////

private:
	//// SRT���i�p�����j
	//DirectX::SimpleMath::Vector3 position_{ 0.f, 0.f, 0.f };
	//DirectX::SimpleMath::Vector3 rotation_{ 0.f, 0.f, 0.f };
	//DirectX::SimpleMath::Vector3 scale_{ 1.f, 1.f, 1.f };


};

#endif	// TRANSFORM_COMPONENT_H_