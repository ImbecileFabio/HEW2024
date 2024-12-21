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
std::vector<GameObject*>* ImGuiBase::objectList_ = {};
GameObject* ImGuiBase::selectObject_ = {};
//--------------------------------------------------
// @param _hWnd GameProcess�Ŏg���Ă���E�B���h�n���h��
// @brief ImGui��Win32API��������
//--------------------------------------------------
void ImGuiManager::ImGuiWin32Initialize(HWND _hWnd)
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
void ImGuiManager::ImGuiD3D11Initialize(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext)
{
    // ������ImGui��DirectX�֘A�������� renderer����
    ImGui_ImplDX11_Init(_device, _deviceContext);
}
//--------------------------------------------------
// @brief ImGui�̃E�B���h�E��������
//--------------------------------------------------
void ImGuiManager::ImGuiInitialize()
{   // �����ō�����E�B���h�E�����X�g�ɒǉ�����
    imGuiWindowList_.push_back(new ObjectStatesGUI());
    imGuiWindowList_.push_back(new SystemGUI());
    imGuiWindowList_.push_back(new TreeGUI());
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
//--------------------------------------------------
void ImGuiManager::ImGuiShowWindow()
{
    if (showFg)
    {
        for (const auto& window : imGuiWindowList_)
        {
            window->ShowWindow();
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
void ImGuiManager::ImGuiUnInitialize()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}
//--------------------------------------------------
// @brief ���N���X�̃R���X�g���N�^
//--------------------------------------------------
ImGuiBase::ImGuiBase()
    :showFg(true)
{
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
        // �I�u�W�F�N�g����
        if (ImGui::Button("Object Create"))
        {

        }
        if (selectObject_ != nullptr)
        {
            // �I�u�W�F�N�g�̖��O
            ImGui::Text(selectObject_->GetObjectName().c_str());
            // transform�̏��
            auto transform = selectObject_->GetComponent<TransformComponent>();
			auto position = transform->GetPosition();
			auto rotation = transform->GetRotation();
			auto scale = transform->GetScale();
            if (ImGui::DragFloat3("position", &position.x, 1.0f, -1000.0f, 1000.0f, "%.3f"))
            {
				transform->SetPosition(position);
            }
            if (ImGui::DragFloat3("rotation", &rotation.x, 1.0f, -1000.0f, 1000.0f, "%.3f"))
            {
                transform->SetRotation(rotation);
            }
            if (ImGui::DragFloat3("scale", &scale.x, 1.0f, -1000.0f, 1000.0f, "%.3f"))
            {
                transform->SetScale(scale);
            }
            ImGui::Separator(); // ��؂��
            ImGui::Text("ComponentList");
        }
        ImGui::End();
    }
}
//-------------------------------------------------
// @brief �V�X�e���̏���\������E�B���h�E
//--------------------------------------------------
void SystemGUI::ShowWindow()
{
    // �^�u���Ǘ�����^�u�o�[
    if (ImGui::BeginTabBar("DebugWindow"), ImGuiWindowFlags_AlwaysVerticalScrollbar)
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
void TreeGUI::ShowWindow()
{
    if (ImGui::Begin("TreeView", nullptr, ImGuiWindowFlags_AlwaysVerticalScrollbar))
    {
        // �ғ����̃I�u�W�F�N�g���X�g
        if (ImGui::TreeNode("active_objects"))
        {
            // objectList_ �̒��g��S�ĕ\��
            for (auto& obj : *objectList_)
            {
                ImGui::PushID(reinterpret_cast<void*>(obj));
                // �I�u�W�F�N�g�̖��O��\���i���� GetName �֐�������ꍇ�j
                if (ImGui::Selectable(obj->GetObjectName().c_str()))
				{
                    selectObject_ = obj;
                }
                ImGui::PopID();  // ID���|�b�v���āA���̗v�f�ɉe�����Ȃ��悤�ɂ���
            }

            ImGui::TreePop();
        }
        ImGui::End();
    }
}

#endif // IMGUI_DEBUG
