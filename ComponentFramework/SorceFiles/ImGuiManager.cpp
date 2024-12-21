//==================================================
// [ImGuiManager.cpp] ImGuiを扱うためのCPPファイル
// 著者：
//--------------------------------------------------
// 説明：ImGuiの機能を自作関数としてまとめたもの
//==================================================
#define IMGUI_DEBUG  // 使うときはコメントアウトを外す
#ifdef IMGUI_DEBUG
#include <iostream>
#include "ImGuiManager.h"
/*----static変数------*/
ImGuiManager* ImGuiManager::staticPointer = nullptr;
std::vector<GameObject*>* ImGuiBase::objectList_ = {};
GameObject* ImGuiBase::selectObject_ = {};
//--------------------------------------------------
// @param _hWnd GameProcessで使っているウィンドハンドル
// @brief ImGuiのWin32APIを初期化
//--------------------------------------------------
void ImGuiManager::ImGuiWin32Initialize(HWND _hWnd)
{
    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
    // テーマカラー
    ImGui::StyleColorsDark();

    io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", 22.0f);  // フォントの設定

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(_hWnd);  // ImGuiのWin32の初期化 ImGuiの関数
}
//--------------------------------------------------
// @brief ImGuiのDirectX11を初期化
//--------------------------------------------------
void ImGuiManager::ImGuiD3D11Initialize(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext)
{
    // ここでImGuiのDirectX関連を初期化 rendererから
    ImGui_ImplDX11_Init(_device, _deviceContext);
}
//--------------------------------------------------
// @brief ImGuiのウィンドウを初期化
//--------------------------------------------------
void ImGuiManager::ImGuiInitialize()
{   // ここで作ったウィンドウをリストに追加する
    imGuiWindowList_.push_back(new ObjectStatesGUI());
    imGuiWindowList_.push_back(new SystemGUI());
    imGuiWindowList_.push_back(new TreeGUI());
}
//--------------------------------------------------
// @brief ImGuiの更新処理　これをループの初めに置いておかないと機能しない
//--------------------------------------------------
void ImGuiManager::ImGuiUpdate()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}
//--------------------------------------------------
// @brief ImGuiをウィンドウを一括管理とデータ渡し
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
// @brief 描画処理
//--------------------------------------------------
void ImGuiManager::ImGuiRender()
{
    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
//--------------------------------------------------
// @brief 終了処理
//--------------------------------------------------
void ImGuiManager::ImGuiUnInitialize()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}
//--------------------------------------------------
// @brief 基底クラスのコンストラクタ
//--------------------------------------------------
ImGuiBase::ImGuiBase()
    :showFg(true)
{
}
//--------------------------------------------------
// @brief ゲームオブジェクトの情報を表示するウィンドウ
//--------------------------------------------------
void ObjectStatesGUI::ShowWindow()
{
    // ここが自分で記述したウィンドウ設定
    if (this->showFg)
    {
        ImGui::Begin("~(0-0)~", &showFg);
        // オブジェクト生成
        if (ImGui::Button("Object Create"))
        {

        }
        if (selectObject_ != nullptr)
        {
            // オブジェクトの名前
            ImGui::Text(selectObject_->GetObjectName().c_str());
            // transformの情報
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
            ImGui::Separator(); // 区切り線
            ImGui::Text("ComponentList");
        }
        ImGui::End();
    }
}
//-------------------------------------------------
// @brief システムの情報を表示するウィンドウ
//--------------------------------------------------
void SystemGUI::ShowWindow()
{
    // タブを管理するタブバー
    if (ImGui::BeginTabBar("DebugWindow"), ImGuiWindowFlags_AlwaysVerticalScrollbar)
    {   // システム情報を表示
        if (ImGui::BeginTabItem("System"))
        {
            float fps = ImGui::GetIO().Framerate;
            ImGui::Text("FPS : %f", fps);  // FPSが出た
            if (fps < 30.0f) // FPSが30下回ったときの警告文
            {   // TODO 下回ったときの状態を保存できたら嬉しい
                ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "Warning: FPS < 30.0f");
            }
            if (ImGui::Button("Reset"))
            {
                // ステージ状態を初期化する処理
            }
            ImGui::EndTabItem();
        }
        // デバッグ情報を表示
        if (ImGui::BeginTabItem("Debug Log"))
        {
            ImGui::Text("ERROR!!!");
            ImGui::EndTabItem();
        }
    }
    ImGui::EndTabBar(); // 終了
}
//--------------------------------------------------
// @brief ObjectとComponentを親子形式で表示するツリー形式ウィンドウ
//--------------------------------------------------
void TreeGUI::ShowWindow()
{
    if (ImGui::Begin("TreeView", nullptr, ImGuiWindowFlags_AlwaysVerticalScrollbar))
    {
        // 稼働中のオブジェクトリスト
        if (ImGui::TreeNode("active_objects"))
        {
            // objectList_ の中身を全て表示
            for (auto& obj : *objectList_)
            {
                ImGui::PushID(reinterpret_cast<void*>(obj));
                // オブジェクトの名前を表示（仮に GetName 関数がある場合）
                if (ImGui::Selectable(obj->GetObjectName().c_str()))
				{
                    selectObject_ = obj;
                }
                ImGui::PopID();  // IDをポップして、次の要素に影響しないようにする
            }

            ImGui::TreePop();
        }
        ImGui::End();
    }
}

#endif // IMGUI_DEBUG
