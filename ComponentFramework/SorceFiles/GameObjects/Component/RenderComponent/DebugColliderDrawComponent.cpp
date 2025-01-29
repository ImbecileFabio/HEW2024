//==================================================
// [DebugColliderDrawComponent.h] �`��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�ƂĂ��`��R���|�[�l���g�̐錾
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>
#include <string>

#include "DebugColliderDrawComponent.h"
#include "../../../GameManager.h"
#include "../../../Renderer.h"
#include "../../../SubSystem/dx11helper.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"
#include "../ColliderComponent/BoxColliderComponent.h"


#include <wrl/client.h>

using namespace DirectX::SimpleMath;




//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
DebugColliderDrawComponent::DebugColliderDrawComponent(GameObject* _owner, int _drawOrder)
	: RenderComponent(_owner, _drawOrder)
{
	// �o�b�t�@������
	this->InitDebugBuffers();
	this->Init();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
DebugColliderDrawComponent::~DebugColliderDrawComponent()
{
	Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void DebugColliderDrawComponent::Init()
{

}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void DebugColliderDrawComponent::Uninit()
{
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void DebugColliderDrawComponent::Update()
{
}

//--------------------------------------------------
// �`�揈��
//--------------------------------------------------
void DebugColliderDrawComponent::Draw()
{
	auto collider = owner_->GetComponent<ColliderBaseComponent>();
	if (collider && collider->GetComponentType() == TypeID::BoxColliderComponent)
	{
		auto boxCollider = static_cast<BoxColliderComponent*>(collider);

		Matrix rot;
		Matrix pos;
		Matrix scale;

		auto transform = owner_->GetTransformComponent();
		if (transform)
		{
			auto si = boxCollider->GetSize();
			auto t = transform->GetPosition();
			auto r = transform->GetRotation();
			auto sc = transform->GetScale();

			auto finalSize = Vector3(si * sc);	// �ŏI�I�ȃT�C�Y


			rot = Matrix::CreateFromYawPitchRoll(r.x, r.y, r.z);
			pos = Matrix::CreateTranslation(t);
			scale = Matrix::CreateScale(finalSize);
		}
		else
		{
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

		devicecontext->DrawIndexed(
			4,							// �`�悷��C���f�b�N�X���i�l�p�`�Ȃ�łS�j
			0,							// �ŏ��̃C���f�b�N�X�o�b�t�@�̈ʒu
			0);
	}
}



//--------------------------------------------------
// �f�o�b�O�p�̃o�b�t�@������
//--------------------------------------------------
void DebugColliderDrawComponent::InitDebugBuffers()
{
	// ���_�f�[�^
	vertices_.resize(4);

	vertices_[0].position = Vector3(-0.5f, 0.5f, 0);
	vertices_[1].position = Vector3(0.5f, 0.5f, 0);
	vertices_[2].position = Vector3(-0.5f, -0.5f, 0);
	vertices_[3].position = Vector3(0.5f, -0.5f, 0);


	vertices_[0].color = Color(1.0f, 0.0f, 0.0f, 0.1f);
	vertices_[1].color = Color(1.0f, 0.0f, 0.0f, 0.1f);
	vertices_[2].color = Color(1.0f, 0.0f, 0.0f, 0.1f);
	vertices_[3].color = Color(1.0f, 0.0f, 0.0f, 0.1f);

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
	shader_.Create(
		"shader/drawColliderVS.hlsl",
		"shader/drawColliderPS.hlsl");
}