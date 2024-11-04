//==================================================
// [VertexComponent.h] 
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F
//==================================================


/*----- �C���N���[�h -----*/
#include "../../StdAfx.h"
#include "VertexComponent.h"

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
VertexComponent::VertexComponent(GameObject* owner, int updateOrder)
	:Component(owner, updateOrder)
{
}
	

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
VertexComponent::~VertexComponent(void)
{
}

//=======================================
//����������
//=======================================
void VertexComponent::Init()
{
	// ���_�f�[�^
	std::vector<VERTEX_3D>	vertices;

	vertices.resize(4);

	vertices[0].position = Vector3(-10, 0, 10);
	vertices[1].position = Vector3(10, 0, 10);
	vertices[2].position = Vector3(-10, 0, -10);
	vertices[3].position = Vector3(10, 0, -10);

	vertices[0].color = Color(1, 1, 1, 1);
	vertices[1].color = Color(1, 1, 1, 1);
	vertices[2].color = Color(1, 1, 1, 1);
	vertices[3].color = Color(1, 1, 1, 1);

	vertices[0].uv = Vector2(0, 0);
	vertices[1].uv = Vector2(0, 0);
	vertices[2].uv = Vector2(0, 0);
	vertices[3].uv = Vector2(0, 0);

	// ���_�o�b�t�@����
	vertex_buffer_.Create(vertices);
}
