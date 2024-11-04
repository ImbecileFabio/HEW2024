//==================================================
// [SpriteComponent.h] �`��R���|�[�l���g
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�ƂĂ��`��R���|�[�l���g�̐錾
//==================================================

/*----- �C���N���[�h -----*/
#include "../../../StdAfx.h"
#include "SpriteComponent.h"
#include "../../GameObject.h"
#include "../../../GameManager.h"
#include "../../../Renderer.h"
#include "../../../SubSystem/dx11helper.h"

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
SpriteComponent::SpriteComponent(GameObject* _owner,const wchar_t* _imgname,  int _drawOrder)
	: RenderComponent(_owner)
	, draw_order_(_drawOrder)
{
	// �e�N�X�`���ǂݍ���
	HRESULT hr = DirectX::CreateWICTextureFromFileEx(Renderer::GetDevice(), Renderer::GetDeviceContext(), _imgname, 0, D3D11_USAGE_DEFAULT, D3D11_BIND_SHADER_RESOURCE, 0, 0, DirectX::WIC_LOADER_IGNORE_SRGB, nullptr, &texture_view_);
	if (FAILED(hr)) {
		MessageBoxA(NULL, "�e�N�X�`���ǂݍ��ݎ��s", "�G���[", MB_ICONERROR | MB_OK);
		return;
	}

	this->owner_->GetGameManager()->GetRenderer()->AddSprite(this);

	object_name_ = std::string("�s���ȃI�u�W�F�N�g");
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
SpriteComponent::~SpriteComponent(void)
{
}

//--------------------------------------------------
// ���O���`����֐�
//--------------------------------------------------
void SpriteComponent::SetObjectName(std::string _objectName)
{
	object_name_ = _objectName;
}

void SpriteComponent::Draw(void)
{
	std::cout << "��" + object_name_ + "�� -> �`��\n";

	
}
