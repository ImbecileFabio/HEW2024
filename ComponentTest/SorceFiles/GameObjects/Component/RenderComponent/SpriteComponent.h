//==================================================
// [SpriteComponent.h] �`��R���|�[�l���g�w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�`��R���|�[�l���g�̒�`�H
//==================================================
#ifndef SPRITE_COMPONENT_H_
#define SPRITE_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include "../RenderComponent.h"
#include <string>

/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/

//--------------------------------------------------
// �`��R���|�[�l���g�̃x�[�X�N���X
//--------------------------------------------------
class SpriteComponent : public RenderComponent
{
public:
	SpriteComponent(class GameObject* owner, int drawOrder = 100);
	~SpriteComponent(void);

	void SetObjectName(std::string objectName);
	virtual void Draw(void);

	int GetDrawOrder(void) { return draw_order_; };

	TypeID GetComponentType(void) const override { return TypeID::SpriteComponent; }

protected:
	int draw_order_;
	std::string object_name_;

};


#endif	// SPRITE_COMPONENT_H_
//==================================================
//				End of FIle
//==================================================
