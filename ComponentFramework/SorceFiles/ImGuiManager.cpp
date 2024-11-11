//==================================================
// [ImGuiManager.cpp] ImGuiを扱うためのCPPファイル
// 著者：
//--------------------------------------------------
// 説明：ImGuiの機能を自作関数としてまとめたもの
//==================================================
#define IMGUI_DEBUG  // 使うときはコメントアウトを外す
#ifdef IMGUI_DEBUG
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
    // Setup Dear ImGui style
    ImGui::StyleColorsDark();   // テーマカラー
    //ImGui::StyleColorsLight();

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
// @brief ImGuiの更新処理　これをループの初めに置いておかないと機能しない
//--------------------------------------------------
void ImGuiManager::ImGuiUpdate()
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}
//--------------------------------------------------
// @brief ウィンドウを表示する関数　テスト用
//--------------------------------------------------
void ImGuiManager::ImGuiShowWindow()
{
    // ここが自分で記述したウィンドウ設定
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
// @brief 描画処理
//--------------------------------------------------
void ImGuiManager::ImGuiRender()
{
    ImGui::Render();
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
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
#endif // IMGUI_DEBUG