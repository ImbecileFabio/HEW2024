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
    // テーマカラー
    ImGui::StyleColorsDark();

	io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\meiryo.ttc", 20.0f);  // フォントの設定
   
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
{

	imGuiWindowVec.push_back(new ObjectStatesGUI());
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
	for (const auto& window : imGuiWindowVec)
	{
		window->ShowWindow();
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
void ObjectStatesGUI::ShowWindow()
{
    // ここが自分で記述したウィンドウ設定
    if (this->showFg)
    {
        ImGui::Begin("~(0-0)~", &showFg);
		// transformの情報
        if (ImGui::DragFloat3("position", &position_.x, 1.0f ,-100.0f, 100.0f, "%.3f"))
        {
			std::cout << position_.x << std::endl;
        }
        if (ImGui::DragFloat3("rotation", &rotation_.x, 1.0f, -100.0f, 100.0f, "%.3f"))
        {
            // ここで値を入力しているときの処理を実装予定
        }
        if (ImGui::DragFloat3("scale", &scale_.x, 1.0f, -100.0f, 100.0f, "%.3f"))
        {

        }
        ImGui::End();
    }
}



#endif // IMGUI_DEBUG
