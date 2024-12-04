//==================================================
// [ImGuiManager.cpp] ImGui���������߂�CPP�t�@�C��
// ���ҁF
//--------------------------------------------------
// �����FImGui�̋@�\������֐��Ƃ��Ă܂Ƃ߂�����
//==================================================
#define IMGUI_DEBUG  // �g���Ƃ��̓R�����g�A�E�g���O��
#ifdef IMGUI_DEBUG
#include <iostream>
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

    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", 22.0f);  // �t�H���g�̐ݒ�

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
{   // �����ō�����E�B���h�E�����X�g�ɒǉ�����
    imGuiWindowVec.push_back(new ObjectStatesGUI());
    imGuiWindowVec.push_back(new SystemGUI());
    imGuiWindowVec.push_back(new TreeGUI());
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
// @brief ImGui���E�B���h�E���ꊇ�Ǘ��ƃf�[�^�n��
// @param _r GameObjectList�̎Q��
//--------------------------------------------------
void ImGuiManager::ImGuiShowWindow(std::vector<GameObject*>& _r)
{
    if (showFg)
    {
        for (const auto& window : imGuiWindowVec)
        {
            window->ShowWindow(_r);
        }
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
void ObjectStatesGUI::ShowWindow(std::vector<GameObject*>& _activeObjects)
{
    // �����������ŋL�q�����E�B���h�E�ݒ�
    if (this->showFg)
    {
        ImGui::Begin("~(0-0)~", &showFg);
        // �I�u�W�F�N�g����
        if (ImGui::Button("Object seisei"))
        {

        }
        // �I�u�W�F�N�g�̖��O
        ImGui::Text("ObjectName, %s", "Player_HOGE");
        // transform�̏��
        if (ImGui::DragFloat3("position", &position_.x, 1.0f, -100.0f, 100.0f, "%.3f"))
        {
        }
        if (ImGui::DragFloat3("rotation", &rotation_.x, 1.0f, -100.0f, 100.0f, "%.3f"))
        {
            // �����Œl����͂��Ă���Ƃ��̏����������\��
        }
        if (ImGui::DragFloat3("scale", &scale_.x, 1.0f, -100.0f, 100.0f, "%.3f"))
        {

        }
        ImGui::Separator(); // ��؂��
        ImGui::Text("ComponentList");
        if (ImGui::Button("AddComponent"))
        {

        }
        if (ImGui::Button("ReMoveComponent"))
        {

        }
        ImGui::End();
    }
}
//--------------------------------------------------
// @brief �V�X�e���̏���\������E�B���h�E
//--------------------------------------------------
void SystemGUI::ShowWindow(std::vector<GameObject*>& _activeObjects)
{
    // �^�u���Ǘ�����^�u�o�[
    if (ImGui::BeginTabBar("DebugWindow"))
    {   // �V�X�e������\��
        if (ImGui::BeginTabItem("System"))
        {
            float fps = ImGui::GetIO().Framerate;
            ImGui::Text("FPS : %f", fps);  // FPS���o��
            if (fps < 30.0f) // FPS��30��������Ƃ��̌x����
            {   // TODO ��������Ƃ��̏�Ԃ�ۑ��ł����������
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Warning: FPS < 30.0f");
            }
            if (ImGui::Button("Reset"))
            {
                // �X�e�[�W��Ԃ����������鏈��
            }
            ImGui::EndTabItem();
        }
        // �f�o�b�O����\��
        if (ImGui::BeginTabItem("Debug Log"))
        {
            ImGui::Text("ERROR!!!");
            ImGui::EndTabItem();
        }
    }
    ImGui::EndTabBar(); // �I��
}
//--------------------------------------------------
// @brief Object��Component��e�q�`���ŕ\������c���[�`���E�B���h�E
//--------------------------------------------------
void TreeGUI::ShowWindow(std::vector<GameObject*>& _activeObjects)
{
    if (ImGui::Begin("TreeView"), nullptr ,ImGuiWindowFlags_AlwaysVerticalScrollbar)
    {
        // �ғ����̃I�u�W�F�N�g���X�g
        if (ImGui::TreeNode("active_objects"))
        {
            ImGui::TreePop();
        }
        ImGui::Separator();
        // ��������ҋ@���̃I�u�W�F�N�g���X�g
        if (ImGui::TreeNode("stand_by_objects"))
        {
            ImGui::TreePop();
        }
        ImGui::End();
    }
}

#endif // IMGUI_DEBUG

