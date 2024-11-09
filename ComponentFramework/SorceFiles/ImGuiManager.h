//==================================================
// [ImGuiManager.h] ImGui���������߂̃w�b�_�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����FGUI���g����悤�ɂ���w�b�_�@�J���̂Ƃ������g��
//==================================================
#pragma once
#define IMGUI_MANAGER_H_	// ImGui���g���Ƃ��̓R�����g�A�E�g���O���Ƃ�����
#ifdef IMGUI_MANAGER_H_
#include "ImGui/imgui_impl_dx11.h"	// �ǉ�����ImGui�t�H���_����  
#include "ImGui/imgui_impl_win32.h"
#include "ImGui/imgui.h"
#include "Renderer.h"
#include "Windows.h"
#include "d3d11.h"
#include "SimpleMath.h"
/*--ImGui�̋@�\���֐��̒��ɓ��ꂽ�N���X--*/
class ImGuiManager
{
public:
	void ImGuiWin32Init(HWND _hWnd);
	void ImGuiD3D11Init();
	void ImGuiUpdate();		// �Q�[�����[�v�̂͂��߂ɍs���X�V����
	void ImGuiShowWindow();	// �E�B���h�E��\��
	void ImGuiRender();		// �`��
	void ImGuiUnInit();		// �I��
private:
	Renderer* renderer_ = nullptr;	// ID3D11Device��ID3D11DeviceContext���ق�������

	ImVec4 clear_color = ImVec4(0.45f, 0.55f, 0.60f, 1.00f);

	DirectX::SimpleMath::Vector3 position_ = {0.0f, 0.0f, 0.0f};
	DirectX::SimpleMath::Vector3 rotation_ = {0.0f, 0.0f, 0.0f};
	DirectX::SimpleMath::Vector3 scale_	   = {0.0f, 0.0f, 0.0f};

	bool showWindowObject = true;	// �E�B���h�E��\�����邩�ǂ���
};

#endif // IMGUI_MANAGER_H_
