//==================================================
// [Component.h] �R���|�[�l���g�x�[�X�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�R���|�[�l���g�̑匳
//==================================================
#ifndef COMPONENT_H_
#define COMPONENT_H_

/*----- �C���N���[�h -----*/
#include "GameObject.h"
/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/


//--------------------------------------------------
// �R���|�[�l���g�N���X
//--------------------------------------------------
class Component
{
public:
	enum class TypeID
	{
		None = -1
		// �x�[�X�N���X
		, Component

		// �����ɒǉ������R���|�[�l���g�������Ă���
		// �����_�����O
		, RenderComponent
		, SpriteComponent

		// �p������
		, TransformComponent

		// �J����
		, CameraComponent

		// �R���|�[�l���g�̍ő�l
		, MAX
	};

	static const char* ComponentTypeNames[static_cast<int>(TypeID::MAX)];

public:
	Component(GameObject* gameObject, int updateOrder = 100);
	virtual ~Component();

	virtual void Init(void) = 0;
	virtual void Uninit(void) = 0;
	virtual void Update(void) = 0;

	virtual void OnUpdateWorldTransform();

	GameObject* GetOwner(void) const { return owner_; }
	int GetUpdateOrder(void) const { return update_order_; }

	virtual TypeID GetComponentType() const = 0;

	// ���[�h, �Z�[�u
	virtual void LoadProperties(void);
	virtual void SaveProperties(void);

private:
	GameObject* owner_{};	// �����i�R���|�[�l���g�j�̏��L��
	int update_order_{};			// �������g�̍X�V����
};


#endif	// COMPONENT_H_