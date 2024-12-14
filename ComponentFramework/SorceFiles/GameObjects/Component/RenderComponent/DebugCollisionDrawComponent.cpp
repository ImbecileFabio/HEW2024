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

	auto devicecontext = Renderer::GetDeviceContext();

	shader_.SetGeometryGPU();
	constant_buffer_.SetGPU();


	// �g�|���W�[���|�C���g���X�g�ɐݒ�
	devicecontext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_POINTLIST);

	// �`��
	devicecontext->Draw(1, 0);
}








