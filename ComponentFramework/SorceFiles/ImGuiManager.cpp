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
//--------------------------------------------------
// @param _hWnd GameProcessで使っているウィンドハンドル
// @brief ImGuiのWin32APIを初期化
//--------------------------------------------------
void ImGuiManager::ImGuiWin32Init(HWND _hWnd)
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
void ImGuiManager::ImGuiD3D11Init(ID3D11Device* _device, ID3D11DeviceContext* _deviceContext)
{
    // ここでImGuiのDirectX関連を初期化 rendererから
    ImGui_ImplDX11_Init(_device, _deviceContext);
}
//--------------------------------------------------
// @brief ImGuiのウィンドウを初期化
//--------------------------------------------------
void ImGuiManager::ImGuiInit()
{   // ここで作ったウィンドウをリストに追加する
    imGuiWindowVec.push_back(new ObjectStatesGUI());
    imGuiWindowVec.push_back(new SystemGUI());
    imGuiWindowVec.push_back(new TreeGUI());
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
// @param _r GameObjectListの参照
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
void ImGuiManager::ImGuiUnInit()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}
//--------------------------------------------------
// @brief ゲームオブジェクトの情報を表示するウィンドウ
//--------------------------------------------------
void ObjectStatesGUI::ShowWindow(std::vector<GameObject*>& _activeObjects)
{
    // ここが自分で記述したウィンドウ設定
    if (this->showFg)
    {
        ImGui::Begin("~(0-0)~", &showFg);
        // オブジェクト生成
        if (ImGui::Button("Object seisei"))
        {

        }
        // オブジェクトの名前
        ImGui::Text("ObjectName, %s", "Player_HOGE");
        // transformの情報
        if (ImGui::DragFloat3("position", &position_.x, 1.0f, -100.0f, 100.0f, "%.3f"))
        {
        }
        if (ImGui::DragFloat3("rotation", &rotation_.x, 1.0f, -100.0f, 100.0f, "%.3f"))
        {
            // ここで値を入力しているときの処理を実装予定
        }
        if (ImGui::DragFloat3("scale", &scale_.x, 1.0f, -100.0f, 100.0f, "%.3f"))
        {

        }
        ImGui::Separator(); // 区切り線
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
// @brief システムの情報を表示するウィンドウ
//--------------------------------------------------
void SystemGUI::ShowWindow(std::vector<GameObject*>& _activeObjects)
{
    // タブを管理するタブバー
    if (ImGui::BeginTabBar("DebugWindow"))
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
void TreeGUI::ShowWindow(std::vector<GameObject*>& _activeObjects)
{
    if (ImGui::Begin("TreeView"), nullptr ,ImGuiWindowFlags_AlwaysVerticalScrollbar)
    {
        // 稼働中のオブジェクトリスト
        if (ImGui::TreeNode("active_objects"))
        {
            ImGui::TreePop();
        }
        ImGui::Separator();
        // ここから待機中のオブジェクトリスト
        if (ImGui::TreeNode("stand_by_objects"))
        {
            ImGui::TreePop();
        }
        ImGui::End();
    }
}

#endif // IMGUI_DEBUG

