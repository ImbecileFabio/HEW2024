//==================================================
// [RenderComponent.cpp] �`�惂�W���[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�`�揈���̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>

#include "../../GameManager.h"
#include "../../Renderer.h"
#include "../GameObject.h"
#include "RenderComponent.h"

#include "../Component.h"

using namespace DirectX::SimpleMath;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
RenderComponent::RenderComponent(GameObject* _owner, int _updateOrder)
	: Component(_owner, _updateOrder)
	, draw_order_(_updateOrder)
{
	std::cout << std::format("��RenderComponent�� -> Constructor\n");
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
RenderComponent::~RenderComponent(void)
{
	std::cout << std::format("��RenderComponent�� -> Destructor\n");

	// �`��I�u�W�F�N�g�Ƃ��ēo�^����
	this->owner_->GetGameManager()->GetRenderer()->RemoveSprite(this);



}

//--------------------------------------------------
// �o�b�t�@������
//--------------------------------------------------
void RenderComponent::InitBuffers()
{
	// ���_�f�[�^

	vertices_.resize(4);

	vertices_[0].position = Vector3(-0.5f, 0.5f, 0.0f);
	vertices_[1].position = Vector3(0.5f, 0.5f, 0.0f);
	vertices_[2].position = Vector3(-0.5f, -0.5f, 0.0f);
	vertices_[3].position = Vector3(0.5f, -0.5f, 0.0f);

	vertices_[0].color = Color(1, 1, 1, 1);
	vertices_[1].color = Color(1, 1, 1, 1);
	vertices_[2].color = Color(1, 1, 1, 1);
	vertices_[3].color = Color(1, 1, 1, 1);

	vertices_[0].uv = Vector2(0, 0);
	vertices_[1].uv = Vector2(1, 0);
	vertices_[2].uv = Vector2(0, 1);
	vertices_[3].uv = Vector2(1, 1);

	// ���_�o�b�t�@����
	vertex_buffer_.Create(vertices_);

	// �C���f�b�N�X�o�b�t�@����
	std::vector<unsigned int> indices;
	indices.resize(4);

	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 2;
	indices[3] = 3;

	// �C���f�b�N�X�o�b�t�@����
	index_buffer_.Create(indices);

	// �V�F�[�_�I�u�W�F�N�g����
	shader_.Create("shader/unlitTextureVS.hlsl", "shader/unlitTexturePS.hlsl");

}
