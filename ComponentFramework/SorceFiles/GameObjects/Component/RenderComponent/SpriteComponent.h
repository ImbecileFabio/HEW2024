//==================================================
// [SpriteComponent.h] �`��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�`��R���|�[�l���g�̐錾
//==================================================
#ifndef SPRITE_COMPONENT_H_
#define SPRITE_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include <memory>
#include <string>

#include "../RenderComponent.h"
#include "../../../SubSystem/Texture.h"



/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameObject;

//--------------------------------------------------
// �`��N���X
//--------------------------------------------------
class SpriteComponent :
	public RenderComponent
{
public:
	SpriteComponent(GameObject* _owner, const std::string _imgname, int _drawOrder = 10);
	~SpriteComponent();

	void Init() override;
	void Update() override;
	void Uninit() override;
	void Draw();

	// �F��ς���
	void SetColor(const DirectX::SimpleMath::Vector4& _color);

	// �R���|�[�l���g��ID��Ԃ�
	TypeID GetComponentType(void) const override { return TypeID::SpriteComponent; }

private:
	Texture texture_;	// �e�N�X�`��
};
#endif	// SPRITE_COMPONENT_H_