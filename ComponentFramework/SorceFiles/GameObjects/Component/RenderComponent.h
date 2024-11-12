//==================================================
// [RenderComponent.h] �`�惂�W���[���w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�I�u�W�F�N�g�̕`�������@�\�̐錾
//==================================================
#ifndef RENDER_COMPONENT_H_
#define RENDER_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include "../Component.h"

/*----- �\���̐錾 -----*/

/*----- �O���錾 -----*/

//--------------------------------------------------
// �`��R���|�[�l���g�̃x�[�X�N���X
//--------------------------------------------------
class RenderComponent : public Component
{
public:
	RenderComponent(class GameObject* _owner, int _drawOrder = 100);
	~RenderComponent();

	void Init(void) override {};
	void Uninit(void) override;
	void Update(void) override {};

	virtual TypeID GetComponentType(void) const override { return TypeID::RenderComponent; }

private:

};

#endif	// RENDER_COMPONENT_H_