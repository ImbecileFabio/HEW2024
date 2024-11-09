//==================================================
// [ImGuiManager.h] ImGui���������߂̃w�b�_�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����FGUI���g����悤�ɂ���w�b�_�@�J���̂Ƃ������g��
//==================================================
#pragma once
#define DEBUG	// �f�o�b�O���[�h �����Ɛ������ď����܂�
#ifdef DEBUG	// �f�o�b�O���[�h�̂Ƃ��̂݃w�b�_��Ǎ�
#include <wrl/client.h>				// ComPtr �R���|�^
#include "ImGui/imgui_impl_dx11.h"	// �ǉ�����ImGui�t�H���_����  
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"
#include "Renderer.h"
#include "Windows.h"
#include "d3d11.h"
#include "SimpleMath.h"
#endif
/*--ImGui�̋@�\���֐��̒��ɓ��ꂽ�N���X--*/
class ImGuiApp
{
public:
	void ImGuiWin32Init();
	void ImGuiD3D11Init();
	void ImGuiUpdate();		// �Q�[�����[�v�̂͂��߂ɍs���X�V����
	void ImGuiShowWindow();	// �E�B���h�E��\��
	void ImGuiRender();		// �`��
	void ImGuiUnInit();		// �I��
	// �Z�b�^�[�֐�
	void SetPosition(DirectX::SimpleMath::Vector3 _position) { position_ = _position; }
	void SetRotation(DirectX::SimpleMath::Vector3 _rotation) { rotation_ = _rotation; }
	void SetScale	(DirectX::SimpleMath::Vector3 _scale) { scale_ = _scale; }
private:
	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	DirectX::SimpleMath::Vector3 position_ = {0.0f, 0.0f, 0.0f};
	DirectX::SimpleMath::Vector3 rotation_ = {0.0f, 0.0f, 0.0f};
	DirectX::SimpleMath::Vector3 scale_	   = {0.0f, 0.0f, 0.0f};

	HWND hWnd_;													// ImGui�̃E�B���h�E�n���h��
	Microsoft::WRL::ComPtr<ID3D11Device>			   device_;	// ImGui�Ŏg��DirectX11�f�o�C�X
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> deviceContext_;	// ImGui�Ŏg��DirectX11�R���e�L�X�g
	// �t���O�ϐ��@���Ƃŏ���
	bool showWindow = true;			// ImGui�̃E�B���h�E���
	bool showWindowAnother = false;	// ������ʂ̃E�B���h�E
	bool showWindowObject = true;	// �I�u�W�F�N�g�̏���\������E�B���h�E
};

