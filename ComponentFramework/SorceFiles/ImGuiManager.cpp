//==================================================
// [ImGuiManager.cpp] ImGuiを扱うためのcppファイル
// 著者：尾上莉奈
//--------------------------------------------------
// 説明：ImGuiの機能を自作関数としてまとめたもの
//==================================================
#define DEBUG
#ifdef DEBUG
#include "ImGuiManager.h"
#endif // DEBUG
//--------------------------------------------------
// ImGuiのWin32APIを初期化
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
    ImGui::StyleColorsDark();   // テーマカラー
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplWin32_Init(this->hWnd_);  // ImGuiのWin32の初期化 ImGuiの関数
}
//--------------------------------------------------
// ImGuiのDirectX11を初期化
//--------------------------------------------------
void ImGuiApp::ImGuiD3D11Init()
{
    // ここでImGuiのDirectX関連を初期化 rendererから
    ImGui_ImplDX11_Init(this->device_.Get(), this->deviceContext_.Get());
}
//--------------------------------------------------
// ImGuiの更新処理
//--------------------------------------------------
void ImGuiApp::ImGuiUpdate()
{
    // Start the Dear ImGui frame
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();
}
//--------------------------------------------------
// ウィンドウを表示する関数　テスト用
//--------------------------------------------------
void ImGuiApp::ImGuiShowWindow()
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
// 描画処理
//--------------------------------------------------
void ImGuiApp::ImGuiRender()
{
    // Rendering
    ImGui::Render();
    const float clear_color_with_alpha[4] = { clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w, clear_color.w };
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}
//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void ImGuiApp::ImGuiUnInit()
{
    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}