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
#include "../../../SubSystem/VertexBuffer.h"
#include "../../../SubSystem/IndexBuffer.h"
#include "../../../SubSystem/Shader.h"
#include "../../../SubSystem/Texture.h"



/*----- �\���̒�` -----*/

/*----- �O���錾 -----*/
class GameObject;

//--------------------------------------
// �`��N���X
//--------------------------------------------------
class SpriteComponent :
	public RenderComponent
{
public:
	SpriteComponent(GameObject* _owner, const std::string _imgname, int _drawOrder = 50);
	~SpriteComponent();

	void Init() override;
	void Update() override;
	void Uninit() override;
	void Draw() ;

	// �X�V���ʂ�Ԃ�
	int& GetDrawOrder(void) { return draw_order_; }
	// �R���|�[�l���g��ID��Ԃ�
	TypeID GetComponentType(void) const override { return TypeID::SpriteComponent; }

private:
	void InitBuffers();	// �o�b�t�@�̏�����

	int draw_order_;	// �X�V����

	// �o�b�t�@
	VertexBuffer<VERTEX_3D> vertex_buffer_;
	IndexBuffer index_buffer_;

	Shader shader_;	// �V�F�[�_

	Texture texture_;	// �e�N�X�`��
};
#endif	// SPRITE_COMPONENT_H_