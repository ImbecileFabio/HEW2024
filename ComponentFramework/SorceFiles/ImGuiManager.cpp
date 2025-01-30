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
#include "GameObjects/Component/ColliderComponent/BoxColliderComponent.h"
#include "GameObjects/Component/ColliderComponent/CircleColliderComponent.h"
#include "GameObjects/Component/RigidbodyComponent/VelocityComponent.h"
#include "GameObjects/Component/PendulumMovementComponent.h"
#include "GameObjects/Component/EventComponent/ColliderEventComponent.h"
#include "GameObjects/Component/StickMoveComponent.h"
#include "GameObjects/Component/RobotMoveComponent.h"
/*----static�ϐ�------*/
ImGuiManager* ImGuiManager::staticPointer = nullptr;
std::vector<GameObject*>* ImGuiBase::objectList_ = {};
GameObject* ImGuiBase::selectObject_ = {};
constexpr float dragSpeed = 1.0f;
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
    //ImGui::StyleColorsDark();
	//ImGui::StyleColorsLight();
	ImGui::StyleColorsClassic();

    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", 24.0f);  // �t�H���g�̐ݒ�

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
        ImGui::Begin("~(0-0)~", &showFg, ImGuiWindowFlags_AlwaysVerticalScrollbar);
        // �I�u�W�F�N�g����
        if (ImGui::Button("Object Create"))
        {

        }
        if (selectObject_ == nullptr)
        {
        }
        else
        {
            if (objectList_->empty())
            {
                selectObject_ = nullptr;
                return;
            }
            // �I�u�W�F�N�g�̖��O
            ImGui::Text(selectObject_->GetObjectName().c_str());
            // transform�̏��
            auto transform = selectObject_->GetComponent<TransformComponent>();
			auto position = transform->GetPosition();
			auto rotation = transform->GetRotation();
			auto size = transform->GetSize();
			auto scale = transform->GetScale();
            if (ImGui::DragFloat3("position", &position.x, dragSpeed, -1000.0f, 1000.0f, "%.3f"))
            {
				transform->SetPosition(position);
            }
            if (ImGui::DragFloat3("rotation", &rotation.x, dragSpeed, -1000.0f, 1000.0f, "%.3f"))
            {
                transform->SetRotation(rotation);
            }
            if (ImGui::DragFloat3("size", &size.x, dragSpeed, -1000.0f, 1000.0f, "%.3f"))
            {
                transform->SetSize(size);
            }
            if (ImGui::DragFloat3("scale", &scale.x, dragSpeed, -1000.0f, 1000.0f, "%.3f"))
            {
                transform->SetScale(scale);
            }
            ImGui::Separator(); // ��؂��
			ImGui::Text("Object-DeltaTime : %f", selectObject_->GetDeltaTime());
            ImGui::Separator(); // ��؂��
            ImGui::Text("ComponentList");
			for (auto& component : selectObject_->GetComponents())
			{
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.4f, 1.0f, 0.1f, 1.0f)); // �ΐF
                ImGui::Text(component->GetComponentName().c_str());
				ImGui::PopStyleColor();
                ImGui::Separator(); // ��؂��
                ImGui::Text("Component-DeltaTime : %f", component->GetDeltaTime());
                switch (component->GetComponentType())
                {
                case Component::TypeID::SpriteComponent:
                {
                    auto sprite = dynamic_cast<SpriteComponent*>(component);
					int drawOrder = sprite->GetDrawOrder();
					int updateOrder = sprite->GetUpdateOrder();
                    if (ImGui::SliderInt("DrawOrder", &drawOrder, -1000, 1000, "%d"))
                    {
                    }
                    ImGui::Text("UpdateOrder : %d", updateOrder);
                    ImGui::Separator(); // ��؂��
                }
                    break;
                case Component::TypeID::BoxColliderComponent:
                {
                    auto boxCollider = dynamic_cast<BoxColliderComponent*>(component);
					auto boxSize = boxCollider->GetSize();
					int updateOrder = boxCollider->GetUpdateOrder();
                    if (ImGui::DragFloat3("BoxSize", &boxSize.x, dragSpeed, -1000.0f, 1000.0f, "%.3f"))
                    {
                    }
                    ImGui::Text("UpdateOrder : %d", updateOrder);
                    ImGui::Separator(); // ��؂��
				}
				    break;
                case Component::TypeID::RobotMoveComponent:
                {
                    auto robotMove = dynamic_cast<RobotMoveComponent*>(component);
                    float speed = robotMove->GetSpeed();
                    int updateOrder = robotMove->GetUpdateOrder();
                    ImGui::Text("Speed : %f", speed);
                    ImGui::Text("UpdateOrder : %d", updateOrder);
                }
                break;
                case Component::TypeID::CircleColliderComponent:
                {
					auto circleCollider = dynamic_cast<CircleColliderComponent*>(component);
                    auto circleSize = circleCollider->GetCircleSize();
					int updateOrder = circleCollider->GetUpdateOrder();		
                    ImGui::Text("UpdateOrder : %d", updateOrder);
					if (ImGui::DragFloat3("CircleSize", &circleSize.position.x, dragSpeed, -1000.0f, 1000.0f,"%.3f"))
					{
					}
                    ImGui::Separator(); // ��؂��
                }
                    break;
                case Component::TypeID::VelocityComponent:
                {
                    auto velocityComponent = dynamic_cast<VelocityComponent*>(component);
                    auto acceleration = velocityComponent->GetAcceleration();
                    auto velocity = velocityComponent->GetVelocity();
                    auto speedRate = velocityComponent->GetSpeedRate();
					int updateOrder = velocityComponent->GetUpdateOrder();
                    ImGui::Text("UpdateOrder : %d", updateOrder);
                    if (ImGui::DragFloat3("Acceleration", &acceleration.x, dragSpeed, -1000.0f, 1000.0f, "%.3f"))
                    {
                    }
                    if (ImGui::DragFloat3("Velocity", &velocity.x, dragSpeed, -1000.0f, 1000.0f,"%.3f"))
                    {
                    }
                    if (ImGui::DragFloat("SpeedRate", &speedRate, dragSpeed, -1000.0f, 1000.0f, "%.3f"))
                    {
                    }
                    ImGui::Separator(); // ��؂��
                    break;
                }
                case Component::TypeID::PendulumMovementComponent:
                {
					auto pendulumMovement = dynamic_cast<PendulumMovementComponent*>(component);
                    auto velocity     = pendulumMovement->GetPendulumVelocity();
					auto angle        = pendulumMovement->GetPendulumAngle();
                    auto acceleration = pendulumMovement->GetPendulumAcceleration();
                    auto fulcrum      = pendulumMovement->GetPendulumFulcrum();
                    auto length       = pendulumMovement->GetPendulumLength();
					int updateOrder = pendulumMovement->GetUpdateOrder();
					ImGui::Text("UpdateOrder : %d", updateOrder);
                    if (ImGui::DragFloat3("Fulcrum", &fulcrum.x, dragSpeed, -1000.0f, 1000.0f,"%.3f"))
                    {
                        pendulumMovement->SetPendulumFulcrum(fulcrum);
                    }
                    if (ImGui::DragFloat("Angle", &velocity, dragSpeed, -1000.0f, 1000.0f, "%.3f"))
                    {
                        pendulumMovement->SetPendulumVelocity(velocity);
                    }
					if (ImGui::DragFloat("Speed", &angle, dragSpeed, -1000.0f, 1000.0f,"%.3f"))
					{
                        pendulumMovement->SetPendulumAngle(angle);
					}
                    if (ImGui::DragFloat("Acceleration", &acceleration, dragSpeed, -1000.0f, 1000.0f, "%.3f"))
                    {
						pendulumMovement->SetPendulumAcceleration(acceleration);
                    }
					if (ImGui::DragFloat("Length", &length, dragSpeed,-1000.0f, 1000.0f, "%.3f"))
					{
						pendulumMovement->SetPendulumLength(length);
					}
                    ImGui::Separator(); // ��؂��
					break;
                }
                case Component::TypeID::ColliderEventComponent:
                {
					auto colliderEvent = dynamic_cast<ColliderEventComponent*>(component);
					size_t id = colliderEvent->GetId();
					int updateOrder = colliderEvent->GetUpdateOrder();
                    ImGui::Text("UpdateOrder : %d", updateOrder);
					ImGui::Text("ID : %d", id);
                    ImGui::Separator(); // ��؂��
                }
					break;
				case Component::TypeID::StickMoveComponent:
				{
                    auto stickMove    = dynamic_cast<StickMoveComponent*>(component);

                    int updateOrder   = stickMove->GetUpdateOrder();
					ImGui::Text("UpdateOrder : %d", updateOrder);

                    }
                    ImGui::Separator(); // ��؂��
                    break;
                default:
                    break;
                }
			}
        }
        ImGui::End();
    }
}
//-------------------------------------------------
// @brief �V�X�e���̏���\������E�B���h�E
//--------------------------------------------------
void SystemGUI::ShowWindow()
{
    if (showFg)
    {
        if (ImGui::Begin("System", &showFg, ImGuiWindowFlags_AlwaysVerticalScrollbar))
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
		ImGui::End();
    }
}
//--------------------------------------------------
// @brief Object��Component��e�q�`���ŕ\������c���[�`���E�B���h�E
//--------------------------------------------------
void TreeGUI::ShowWindow()
{
    if (showFg)
    {
        if (ImGui::Begin("TreeView", &showFg, ImGuiWindowFlags_AlwaysVerticalScrollbar))
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
        }
        if (objectList_->empty())
        {
            selectObject_ = nullptr;
        }
        ImGui::End();
    }
}

#endif // IMGUI_DEBUG
