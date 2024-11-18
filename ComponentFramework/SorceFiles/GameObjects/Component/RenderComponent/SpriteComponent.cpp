//==================================================
// [SpriteComponent.h] �`��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�ƂĂ��`��R���|�[�l���g�̐錾
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>
#include <cassert>
#include <string>

#include "SpriteComponent.h"
#include "../../../GameManager.h"
#include "../../../Renderer.h"
#include "../../../SubSystem/dx11helper.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"

#include <wrl/client.h>
using namespace DirectX::SimpleMath;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
SpriteComponent::SpriteComponent(GameObject* _owner,const std::string _imgname,  int _drawOrder)
	: RenderComponent(_owner)
	, draw_order_(_drawOrder)
{
	std::format("{}", "��SpriteComponent�� -> Constructor\n");

	// �e�N�X�`���ǂݍ���
	bool sts = texture_.Load(_imgname);
	assert(sts == true);

	// �o�b�t�@������
	InitBuffers();
	

	// �`��I�u�W�F�N�g�Ƃ��ēo�^
	this->owner_->GetGameManager()->GetRenderer()->AddSprite(this);
	object_name_ = std::string("�s���ȃI�u�W�F�N�g");
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
SpriteComponent::~SpriteComponent()
{
	std::cout << std::format("{}{}\n", "��SpriteComponent�� -> Destructor", object_name_);

	Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void SpriteComponent::Init()
{

}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void SpriteComponent::Uninit()
{
}

//--------------------------------------------------
// �o�b�t�@������
//--------------------------------------------------
void SpriteComponent::InitBuffers()
{
	// ���_�f�[�^
	std::vector<VERTEX_3D>	vertices;

	vertices.resize(4);

	vertices[0].position = Vector3(-10, 10, 0);
	vertices[1].position = Vector3(10, 10, 0);
	vertices[2].position = Vector3(-10, -10, 0);
	vertices[3].position = Vector3(10, -10, 0);

	vertices[0].color = Color(1, 1, 1, 1);
	vertices[1].color = Color(1, 1, 1, 1);
	vertices[2].color = Color(1, 1, 1, 1);
	vertices[3].color = Color(1, 1, 1, 1);

	vertices[0].uv = Vector2(0, 0);
	vertices[1].uv = Vector2(1, 0);
	vertices[2].uv = Vector2(0, 1);
	vertices[3].uv = Vector2(1, 1);

	// ���_�o�b�t�@����
	vertex_buffer_.Create(vertices);

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

//--------------------------------------------------
// ���O���`���鏈��
//--------------------------------------------------
void SpriteComponent::SetObjectName(std::string _objectName)
{
	object_name_ = _objectName;
}


//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void SpriteComponent::Update()
{
}

//--------------------------------------------------
// �`�揈��
//--------------------------------------------------
void SpriteComponent::Draw()
{
	Matrix rot;
	Matrix pos;
	Matrix scale;
	
	auto transform = owner_->GetComponent<TransformComponent>();
	if (transform)
	{
		auto t = transform->GetPosition();
		auto r = transform->GetRotation();
		auto s = transform->GetScale();
		rot = Matrix::CreateFromYawPitchRoll(r.y, r.x, r.z);
		pos = Matrix::CreateTranslation(t);
		scale = Matrix::CreateScale(s);
	}
	else 
	{
		std::cout << std::format("{}	��{}��\n", "��SpriteComponent�� -> Faild Get Transform", object_name_);
		rot = Matrix::CreateFromYawPitchRoll(0.f, 0.f, 0.f);
		pos = Matrix::CreateTranslation(0.f, 0.f, 0.f);
		scale = Matrix::CreateScale(1.f, 1.f, 1.f);
	}
	
	Matrix worldmtx;
	worldmtx = scale * rot * pos;
	Renderer::SetWorldMatrix(&worldmtx); // GPU�ɃZ�b�g

	// �`��̏���
	ID3D11DeviceContext* devicecontext;
	devicecontext = Renderer::GetDeviceContext();
	assert(devicecontext);

	// �g�|���W�[���Z�b�g�i�v���~�e�B�u�^�C�v�j
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);

	shader_.SetGPU();
	vertex_buffer_.SetGPU();
	index_buffer_.SetGPU();

	texture_.SetGPU();

	devicecontext->DrawIndexed(
		4,							// �`�悷��C���f�b�N�X���i�l�p�`�Ȃ�łS�j
		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0);
}

