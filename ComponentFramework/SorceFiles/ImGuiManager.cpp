//==================================================
// [ImGuiManager.cpp] ImGui���������߂�CPP�t�@�C��
// ���ҁF
//--------------------------------------------------
// �����FImGui�̋@�\������֐��Ƃ��Ă܂Ƃ߂�����
//==================================================
#define IMGUI_DEBUG  // �g���Ƃ��̓R�����g�A�E�g���O��
#ifdef IMGUI_DEBUG
#include "ImGuiManager.h"
/*----static�ϐ�------*/
ImGuiManager* ImGuiManager::staticPointer = nullptr;
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
    // �e�[�}�J���[
    ImGui::StyleColorsDark();

	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", 20.0f);  // �t�H���g�̐ݒ�
   
    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(_hWnd);  // ImGui��Win32�̏����� ImGui�̊֐�
}
//--------------------------------------------------
// @brief ImGui��DirectX11��������
//--------------------------------------------------
void ImGuiManager::ImGuiD3D11Init(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext)
{
    // ������ImGui��DirectX�֘A�������� renderer����
    ImGui_ImplDX11_Init(_device, _deviceContext);
}
//--------------------------------------------------
// @brief ImGui�̃E�B���h�E��������
//--------------------------------------------------
void ImGuiManager::ImGuiInit()
{

	imGuiWindowVec.push_back(new ObjectStatesGUI());
}
//--------------------------------------------------
// @brief ImGui�̍X�V�����@��������[�v�̏��߂ɒu���Ă����Ȃ��Ƌ@�\���Ȃ�
//--------------------------------------------------
void ImGuiManager::ImGuiUpdate()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}
//--------------------------------------------------
// @brief �E�B���h�E��\������֐��@�e�X�g�p
//--------------------------------------------------
void ImGuiManager::ImGuiShowWindow()
{
	for (const auto& window : imGuiWindowVec)
	{
		window->ShowWindow();
	}
}
//--------------------------------------------------
// @brief �`�揈��
//--------------------------------------------------
void ImGuiManager::ImGuiRender()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
//--------------------------------------------------
// @brief �I������
//--------------------------------------------------
void ImGuiManager::ImGuiUnInit()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}
//--------------------------------------------------
// @brief �Q�[���I�u�W�F�N�g�̏���\������E�B���h�E
//--------------------------------------------------
void ObjectStatesGUI::ShowWindow()
{
    // �����������ŋL�q�����E�B���h�E�ݒ�
    if (this->showFg)
    {
        ImGui::Begin("~(0-0)~", &showFg);
		// transform�̏��
        if (ImGui::DragFloat3("position", &position_.x, 1.0f ,-100.0f, 100.0f, "%.3f"))
        {
			std::cout << position_.x << std::endl;
        }
        if (ImGui::DragFloat3("rotation", &rotation_.x, 1.0f, -100.0f, 100.0f, "%.3f"))
        {
            // �����Œl����͂��Ă���Ƃ��̏����������\��
        }
        if (ImGui::DragFloat3("scale", &scale_.x, 1.0f, -100.0f, 100.0f, "%.3f"))
        {

        }
        ImGui::End();
    }
}



#endif // IMGUI_DEBUG
