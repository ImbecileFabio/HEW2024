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

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameObject;
//--------------------------------------------------
// �p������R���|�[�l���g
//--------------------------------------------------
class TransformComponent : Component
{
public:
	TransformComponent(std::shared_ptr<GameObject> _owner, int updateOrder = 100);
	~TransformComponent();

	void Init(void) override;
	void Uninit(void) override;
	void Update(void) override;


	auto& GetPosition() { return position_; }
	auto& GetRotation() { return rotation_; }
	auto& GetScale() { return scale_; }

	void SetPosition(DirectX::SimpleMath::Vector3 _pos) { position_ = _pos; }
	void SetRotation(DirectX::SimpleMath::Vector3 _rot) { rotation_ = _rot; }
	void SetScale(DirectX::SimpleMath::Vector3 _sca) { scale_ = _sca; }

	virtual TypeID GetComponentType() const override { return TypeID::TransformComponent; }

private:
	// SRT���i�p�����j
	DirectX::SimpleMath::Vector3 position_{};
	DirectX::SimpleMath::Vector3 rotation_{};
	DirectX::SimpleMath::Vector3 scale_{};


};

#endif	// TRANSFORM_COMPONENT_H_