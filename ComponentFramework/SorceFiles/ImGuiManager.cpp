//==================================================
// [ImGuiManager.cpp] ImGui���������߂�cpp�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����FImGui�̋@�\������֐��Ƃ��Ă܂Ƃ߂�����
//==================================================
#define IMGUI_MANAGER_H_  // �g���Ƃ��̓R�����g�A�E�g���O��
#ifdef IMGUI_MANAGER_H_
#include "ImGuiManager.h"
//--------------------------------------------------
// @param _hWnd GameProcess�Ŏg���Ă���E�B���h�n���h��
// @brief ImGui��Win32API��������
//--------------------------------------------------
void ImGuiManager::ImGuiWin32Init(HWND _hWnd)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();   // �e�[�}�J���[
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(_hWnd);  // ImGui��Win32�̏����� ImGui�̊֐�
}
//--------------------------------------------------
// @brief ImGui��DirectX11��������
//--------------------------------------------------
void ImGuiManager::ImGuiD3D11Init()
{
    // ������ImGui��DirectX�֘A�������� renderer����
	renderer_ = new Renderer();
    ImGui_ImplDX11_Init(this->renderer_->GetDevice(), this->renderer_->GetDeviceContext());
}
//--------------------------------------------------
// @brief ImGui�̍X�V����
//--------------------------------------------------
void ImGuiManager::ImGuiUpdate()
{
    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}
//--------------------------------------------------
// �E�B���h�E��\������֐��@�e�X�g�p
//--------------------------------------------------
void ImGuiManager::ImGuiShowWindow()
{
    // �����������ŋL�q�����E�B���h�E�ݒ�
    if (showWindowObject)
    {
        ImGui::Begin("Transform", &showWindowObject);
		ImGui::Text("Position %f, %f, %f", position_.x, position_.y, position_.z);
		ImGui::Text("Rotation %f, %f, %f", rotation_.x, rotation_.y, rotation_.z);
		ImGui::Text("Scale    %f, %f, %f",    scale_.x,    scale_.y,    scale_.z);
        ImGui::End();
    }
}
//--------------------------------------------------
// @brief �`�揈��
//--------------------------------------------------
void ImGuiManager::ImGuiRender()
{
    // Rendering
    renderer_->Begin();
    ImGui::Render();
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
    renderer_->End();
}
//--------------------------------------------------
// @brief �I������
//--------------------------------------------------
void ImGuiManager::ImGuiUnInit()
{
	renderer_->Uninit();
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}
#endif // IMGUI_MANAGER_H_