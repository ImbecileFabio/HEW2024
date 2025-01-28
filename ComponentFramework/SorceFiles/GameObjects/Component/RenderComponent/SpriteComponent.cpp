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

#include "../TransformComponent.h"
#include "AnimationComponent.h"

#include "../../GameObject.h"

#include <wrl/client.h>
using namespace DirectX::SimpleMath;

//--------------------------------------------------
// @brief �R���X�g���N�^
//--------------------------------------------------
SpriteComponent::SpriteComponent(GameObject* _owner, const std::string _imgname, int _drawOrder)
	: RenderComponent(_owner, _drawOrder)
{
	std::cout << std::format("��SpriteComponent�� -> Constructor\n");
	
	// �e�N�X�`���擾
	texture_ = TextureManager::GetInstance().GetTexture(_imgname);
	if (!texture_)
	{
		std::cerr << std::format("��SpriteComponent�� -> Failed to get texture : {}\n", _imgname);
		return;
	}
	// �o�b�t�@������
	this->InitBuffers(texture_->GetCutU(), texture_->GetCutV());	// �摜�̕�������n��

	this->Init();
}
//--------------------------------------------------
// @brief �f�X�g���N�^
//--------------------------------------------------
SpriteComponent::~SpriteComponent()
{
	std::cout << std::format("��SpriteComponent�� -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// @brief ����������
//--------------------------------------------------
void SpriteComponent::Init()
{

}

//--------------------------------------------------
// @brief �I������
//--------------------------------------------------
void SpriteComponent::Uninit()
{
}


//--------------------------------------------------
// @brief �X�V����
//--------------------------------------------------
void SpriteComponent::Update()
{
}

//--------------------------------------------------
// @brief �`�揈��
//--------------------------------------------------
void SpriteComponent::Draw()
{
	Matrix rot;
	Matrix pos;
	Matrix scale;
	
	if(owner_)
	{
		auto transform = owner_->GetTransformComponent();
		if (transform)
		{
			auto si = transform->GetSize();
			auto t = transform->GetPosition();
			auto r = transform->GetRotation();
			auto sc = transform->GetScale();

			auto offsetPos = texture_->GetOffsetPos();	// �I�t�Z�b�g�|�W�V����
			auto offsetSize = texture_->GetOffsetSize();	// �I�t�Z�b�g�T�C�Y

			Vector3 finalPos = { t.x + offsetPos.x, t.y + offsetPos.y, t.z };	// �ŏI�I�Ȉʒu
			Vector3 finalSize = { (si.x * offsetSize.x) * sc.x,  (si.y * offsetSize.y) * sc.y, si.z * si.z };	// �ŏI�I�ȃT�C�Y


			rot = Matrix::CreateFromYawPitchRoll(r.x, r.y, r.z);
			pos = Matrix::CreateTranslation(finalPos);
			scale = Matrix::CreateScale(finalSize);
		}
	}
	else 
	{
		std::cout << std::format("��SpriteComponent�� -> default position\n");
		rot = Matrix::CreateFromYawPitchRoll(0.0f, 0.0f, 0.0f);
		pos = Matrix::CreateTranslation(0.0f, 0.0f, 0.0f);
		scale = Matrix::CreateScale(1.0f, 1.0f, 1.0f);
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



	// ����GPU�ɃZ�b�g
	shader_.SetGPU();
	vertex_buffer_.Modify(vertices_);	// �o�b�t�@�̍X�V
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
	auto frameSize = texture_->GetFrameSize();
	
	current_uv_ = _uv;
	Vector2 uvMin = { current_uv_.x, current_uv_.y };
	Vector2 uvMax = { current_uv_.x + frameSize.x, current_uv_.y + frameSize.y };


	vertices_[0].uv = { (x_flip_ ? uvMax.x : uvMin.x), (y_flip_ ? uvMax.y : uvMin.y)};
	vertices_[1].uv = { (x_flip_ ? uvMin.x : uvMax.x), (y_flip_ ? uvMax.y : uvMin.y)};
	vertices_[2].uv = { (x_flip_ ? uvMax.x : uvMin.x), (y_flip_ ? uvMin.y : uvMax.y)};
	vertices_[3].uv = { (x_flip_ ? uvMin.x : uvMax.x), (y_flip_ ? uvMin.y : uvMax.y)};
}
void SpriteComponent::SetUV()
{
	auto frameSize = texture_->GetFrameSize();

	Vector2 uvMin = current_uv_;
	Vector2 uvMax = { current_uv_.x + frameSize.x, current_uv_.y + frameSize.y };

	vertices_[0].uv = { (x_flip_ ? uvMax.x : uvMin.x), (y_flip_ ? uvMax.y : uvMin.y) };
	vertices_[1].uv = { (x_flip_ ? uvMin.x : uvMax.x), (y_flip_ ? uvMax.y : uvMin.y) };
	vertices_[2].uv = { (x_flip_ ? uvMax.x : uvMin.x), (y_flip_ ? uvMin.y : uvMax.y) };
	vertices_[3].uv = { (x_flip_ ? uvMin.x : uvMax.x), (y_flip_ ? uvMin.y : uvMax.y) };
}



//--------------------------------------------------
// @brief �e�N�X�`���ύX
//--------------------------------------------------
void SpriteComponent::SetTexture(const std::string _imgname)
{
	auto newTexture = TextureManager::GetInstance().GetTexture(_imgname);

	// �����e�N�X�`���Ȃ牽�����Ȃ�
	if (texture_ == newTexture) return;

	// ���������Ⴄ�������o�b�t�@���ď�����
	if (texture_->GetCutU() != newTexture->GetCutU() || texture_->GetCutU() != newTexture->GetCutV())
	{
		this->InitBuffers(newTexture->GetCutU(), newTexture->GetCutV());	// �摜�̕�������n��
	}
	// �e�N�X�`����ύX
	texture_ = newTexture;

	// �I�[�i�[���A�j���[�V�����R���|�[�l���g�������Ă���Ȃ�
	if (auto anmComp = owner_->GetComponent<AnimationComponent>())
	{
		anmComp->ResetAnimation();	// �A�j���[�V���������Z�b�g
	}
}

//--------------------------------------------------
// @brief �F�ύX
//--------------------------------------------------
void SpriteComponent::SetColor(const DirectX::SimpleMath::Vector4& _color)
{
	for (auto& vertex : vertices_)
	{
		vertex.color = _color;		// �F��ύX
	}
}


//--------------------------------------------------
// @param _xFlip X�����], _yFlip Y�����]
// @brief �摜���]
//--------------------------------------------------
void SpriteComponent::SetFlip(bool _xFlip, bool _yFlip)
{
	x_flip_ = _xFlip;
	y_flip_ = _yFlip;

	// UV���W��ύX
	this->SetUV();
}


