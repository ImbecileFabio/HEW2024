//==================================================
// [ImGuiManager.cpp] ImGui���������߂�cpp�t�@�C��
// ���ҁF����仓�
//--------------------------------------------------
// �����FImGui�̋@�\������֐��Ƃ��Ă܂Ƃ߂�����
//==================================================
#define DEBUG
#ifdef DEBUG
#include "ImGuiManager.h"
#endif // DEBUG
//--------------------------------------------------
// ImGui��Win32API��������
//--------------------------------------------------
void ImGuiApp::ImGuiWin32Init()
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
    ImGui_ImplWin32_Init(this->hWnd_);  // ImGui��Win32�̏����� ImGui�̊֐�
}
//--------------------------------------------------
// ImGui��DirectX11��������
//--------------------------------------------------
void ImGuiApp::ImGuiD3D11Init()
{
    // ������ImGui��DirectX�֘A�������� renderer����
    ImGui_ImplDX11_Init(this->device_.Get(), this->deviceContext_.Get());
}
//--------------------------------------------------
// ImGui�̍X�V����
//--------------------------------------------------
void ImGuiApp::ImGuiUpdate()
{
    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}
//--------------------------------------------------
// �E�B���h�E��\������֐��@�e�X�g�p
//--------------------------------------------------
void ImGuiApp::ImGuiShowWindow()
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
// �`�揈��
//--------------------------------------------------
void ImGuiApp::ImGuiRender()
{
    // Rendering
    ImGui::Render();
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
//--------------------------------------------------
// �I������
//--------------------------------------------------
void ImGuiApp::ImGuiUnInit()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}