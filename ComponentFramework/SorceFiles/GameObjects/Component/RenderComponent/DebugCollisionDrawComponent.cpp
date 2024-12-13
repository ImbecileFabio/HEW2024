//==================================================
// [DebugCollisionDrawComponent.h] �`��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�ƂĂ��`��R���|�[�l���g�̐錾
//==================================================

/*----- �C���N���[�h -----*/
#include <iostream>
#include <format>
#include <string>

#include "DebugCollisionDrawComponent.h"
#include "../../../GameManager.h"
#include "../../../SubSystem/dx11helper.h"
#include "../../GameObject.h"
#include "../TransformComponent.h"
#include "../ColliderComponent/BoxColliderComponent.h"


#include <wrl/client.h>

using namespace DirectX::SimpleMath;
/*----- �O���錾 -----*/
bool CreateGeometryShader(ID3D11Device* device, ID3D11GeometryShader** geometryShader, ID3D11Buffer** constantBuffer);

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
DebugCollisionDrawComponent::DebugCollisionDrawComponent(GameObject* _owner, int _drawOrder)
	: RenderComponent(_owner, _drawOrder)
{
	std::cout << std::format("��DebugCollisionDrawComponent�� -> Constructor\n");

	// �o�b�t�@������
	InitDebugBuffers();

	this->Init();
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
DebugCollisionDrawComponent::~DebugCollisionDrawComponent()
{
	std::cout << std::format("��DebugCollisionDrawComponent�� -> Destructor\n");

	Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
void DebugCollisionDrawComponent::Init()
{

}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void DebugCollisionDrawComponent::Uninit()
{
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void DebugCollisionDrawComponent::Update()
{
}

//--------------------------------------------------
// �`�揈��
//--------------------------------------------------
void DebugCollisionDrawComponent::Draw()
{
	auto collider = owner_->GetComponent<BoxColliderComponent>();
	if (!collider) { return; }	// �R���C�_�[���Ȃ��ꍇ�͕`�悵�Ȃ�


	const auto& box = collider->GetBoxSize();

	Color debugColor = collider->GetHitFg() ? Color(1, 0, 0, 1) : Color(0, 1, 0, 1);	// true == Red, false == Green
	float thickness = 20.0f;

	 // �l�p�`�̊e�ӂ�`��
	DrawLine({ box.y, box.w }, { box.z, box.w }, debugColor, thickness); // ���
	DrawLine({ box.z, box.w }, { box.z, box.x }, debugColor, thickness); // �E��
	DrawLine({ box.z, box.x }, { box.y, box.x }, debugColor, thickness); // ����
	DrawLine({ box.y, box.x }, { box.y, box.w }, debugColor, thickness); // ����
}





// �����蔻��̐���`��
void DebugCollisionDrawComponent::DrawLine(const Vector2& _start, const Vector2& _end, const Color& _color, const float& _thickness) {
	// ���̕����x�N�g��
	DirectX::SimpleMath::Vector2 direction = _end - _start;
	direction.Normalize();

	// ���������x�N�g�����v�Z
	DirectX::SimpleMath::Vector2 perpendicular = { -direction.y, direction.x };

	// ���̎l�p�`�����̒��_���v�Z
	DirectX::SimpleMath::Vector2 topLeft = _start + perpendicular * (_thickness / 2);
	DirectX::SimpleMath::Vector2 topRight = _end + perpendicular * (_thickness / 2);
	DirectX::SimpleMath::Vector2 bottomLeft = _start - perpendicular * (_thickness / 2);
	DirectX::SimpleMath::Vector2 bottomRight = _end - perpendicular * (_thickness / 2);



	index_buffer_.Create({ 0, 1, 2, 1, 3, 2 });


	shader_.SetGeometryGPU();
	vertex_buffer_.SetGPU();
	index_buffer_.SetGPU();


	// �o�b�t�@���Z�b�g
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Renderer::GetDeviceContext()->DrawIndexed(6, 0, 0);
}



//--------------------------------------------------------------------------------------
// �W�I���g���[�V�F�[�_�𐶐�����
//--------------------------------------------------------------------------------------
bool CreateGeometryShader(ID3D11Device* device, ID3D11GeometryShader** geometryShader, ID3D11Buffer** constantBuffer) {
	// �V�F�[�_�[�o�C�i�����R���p�C��
	ID3D10Blob* gsBlob = nullptr;
	HRESULT hr = D3DCompileFromFile(
		L"GeometryuShader.hlsl",
		nullptr, nullptr, "gs_main", "hs_5_0",
		D3DCOMPILE_ENABLE_STRICTNESS, 0, &gsBlob, nullptr);
	assert(SUCCEEDED(hr));

	// �W�I���g���V�F�[�_���쐬
	hr = device->CreateGeometryShader(gsBlob->GetBufferPointer(), gsBlob->GetBufferSize(), nullptr, geometryShader);
	assert(SUCCEEDED(hr));
	gsBlob->Release();

	// �萔�o�b�t�@���쐬
	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(GeometryShaderBuffer);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = device->CreateBuffer(&bufferDesc, nullptr, constantBuffer);
	assert(SUCCEEDED(hr));
}
