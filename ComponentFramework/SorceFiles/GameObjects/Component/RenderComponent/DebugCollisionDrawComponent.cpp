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

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
DebugCollisionDrawComponent::DebugCollisionDrawComponent(GameObject* _owner, int _drawOrder)
	: RenderComponent(_owner, _drawOrder)
{
	std::cout << std::format("��DebugCollisionDrawComponent�� -> Constructor\n");

	// �o�b�t�@������
	InitGeometryBuffers();

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


	// �o�b�t�@���Z�b�g
	Renderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Renderer::GetDeviceContext()->DrawIndexed(6, 0, 0);
}



