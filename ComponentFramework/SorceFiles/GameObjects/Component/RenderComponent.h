//==================================================
// [RenderComponent.h] �`�惂�W���[���w�b�_
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�I�u�W�F�N�g�̕`�������@�\�̐錾
//==================================================
#ifndef RENDER_COMPONENT_H_
#define RENDER_COMPONENT_H_

/*----- �C���N���[�h -----*/
#include <memory>

#include "../Component.h"
#include "../../SubSystem/VertexBuffer.h"
#include "../../SubSystem/IndexBuffer.h"
#include "../../SubSystem/ConstantBuffer.h"
#include "../../SubSystem/Shader.h"

/*----- �\���̐錾 -----*/

/*----- �O���錾 -----*/
class GameObject;

//--------------------------------------------------
// �`��R���|�[�l���g�̃x�[�X�N���X
//--------------------------------------------------
class RenderComponent : public Component
{
public:
	RenderComponent(GameObject* _owner, int _drawOrder = 50);
	~RenderComponent();

	void Init(void) override {};
	void Uninit(void) override {};
	void Update(void) override {};
	
	virtual void Draw(void) = 0;

	// �X�V���ʂ�Ԃ�
	int& GetDrawOrder(void) { return draw_order_; }


	virtual TypeID GetComponentType(void) const override { return TypeID::RenderComponent; }

protected:
	int draw_order_;	// �X�V����

	void InitBuffers();	// �o�b�t�@�̏�����
	void InitGeometryBuffers();	// �f�o�b�O�p�o�b�t�@�̏�����

	// �o�b�t�@
	VertexBuffer<VERTEX_3D> vertex_buffer_;
	IndexBuffer index_buffer_;
	// �萔�o�b�t�@
	ConstantBuffer<GeometryShaderBuffer> constant_buffer_;	


	Shader shader_;	// �V�F�[�_

	std::vector<VERTEX_3D> vertices_;	// ���_�f�[�^

};

#endif	// RENDER_COMPONENT_H_