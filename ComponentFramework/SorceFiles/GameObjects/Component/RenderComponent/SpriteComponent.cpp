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
#include "../../../TextureManager.h"
#include "../../../SubSystem/dx11helper.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"

#include <wrl/client.h>
using namespace DirectX::SimpleMath;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
SpriteComponent::SpriteComponent(GameObject* _owner,const std::string _imgname,  int _drawOrder)
	: RenderComponent(_owner, _drawOrder)
{
	std::cout << std::format("��SpriteComponent�� -> Constructor\n");
	
	// �e�N�X�`���擾
	texture_ = TextureManager::GetInstance().GetTexture(_imgname);

	// �o�b�t�@������
	this->InitBuffers(texture_->GetCutU(), texture_->GetCutV());	// �摜�̕�������n��

	this->Init();
}
//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
SpriteComponent::~SpriteComponent()
{
	std::cout << std::format("��SpriteComponent�� -> Destructor\n");

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
	
	auto transform = owner_->GetTransformComponent();
	if (transform)
	{
		auto si = transform->GetSize();
		auto t  = transform->GetPosition();
		auto r  = transform->GetRotation();
		auto sc = transform->GetScale();

		auto finalSize = Vector3(si * sc);	// �ŏI�I�ȃT�C�Y


		rot = Matrix::CreateFromYawPitchRoll(r.x, r.y, r.z);
		pos = Matrix::CreateTranslation(t);
		scale = Matrix::CreateScale(finalSize);
	}
	else 
	{
		std::cout << std::format("��SpriteComponent�� -> default position\n");
		rot = Matrix::CreateFromYawPitchRoll(0.0f, 0.0f, 0.0f);
		pos = Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
		scale = Matrix::CreateScale(100.0f, 100.0f, 100.0f);
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

	texture_->SetGPU();
	material_->SetGPU();

	devicecontext->DrawIndexed(
		4,							// �`�悷��C���f�b�N�X���i�l�p�`�Ȃ�łS�j
		0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
		0);
}

void SpriteComponent::SetUV(const DirectX::SimpleMath::Vector2& _uv)
{
	float cutU = texture_.get()->GetCutU();
	float cutV = texture_.get()->GetCutV();

	vertices_[0].uv = Vector2(_uv.x / cutU, _uv.y / cutV);
	vertices_[1].uv = Vector2((_uv.x + 1.0f) / cutU, _uv.y / cutV);
	vertices_[2].uv = Vector2(_uv.x / cutU, (_uv.y + 1.0f) / cutV);
	vertices_[3].uv = Vector2((_uv.x + 1.0f) / cutU, (_uv.y + 1.0f) / cutV);

	vertex_buffer_.Modify(vertices_);

}


void SpriteComponent::SetTexture(const std::string _imgname)
{
	texture_ = TextureManager::GetInstance().GetTexture(_imgname);
}

//--------------------------------------------------
// �F�ύX
//--------------------------------------------------
void SpriteComponent::SetColor(const DirectX::SimpleMath::Vector4& _color)
{
	for (auto& vertex : vertices_)
	{
		vertex.color = _color;		// �F��ύX
	}

	vertex_buffer_.Modify(vertices_);	// �o�b�t�@����������
}


