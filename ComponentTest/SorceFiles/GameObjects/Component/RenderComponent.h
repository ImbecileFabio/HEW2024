//==================================================
// [RenderComponent.h] �`��R���|�[�l���g�̃x�[�X�R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�`��R���|�[�l���g�̃x�[�X�̃N���X��`
//==================================================
#ifndef RENDER_COMPONENT_H_
#define RENDER_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include "../Component.h"

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/



//--------------------------------------------------
// �e�N�X�`���[�`��N���X
//--------------------------------------------------
class RenderComponent : public Component
{
public:	
	RenderComponent(class GameObject* owner, int drawOrder = 100);
	~RenderComponent(void);

	TypeID GetComponentType(void) const override { return TypeID::RenderComponent; }

private:
protected:
};

#endif	// RENDER_COMPONENT_H_
//==================================================
//				End of FIle
//==================================================
