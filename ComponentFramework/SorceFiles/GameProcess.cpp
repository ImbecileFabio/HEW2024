//==================================================
// [GameProcess.cpp] ゲーム実行処理モジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ゲームの実行部分をまとめたクラスの定義
//		 ウィンドウの作成
//==================================================

/*----- インクルード -----*/
#include "StdAfx.h"
#include "GameProcess.h"
#include "GameManager.h"
#include "Renderer.h"
#define IMGUI_DEBUG	//ImGuiを使うときはコメントアウトを外すといける
#ifdef IMGUI_DEBUG
#include "ImGuiManager.h"
#endif
// ウィンドウクラス、ウィンドウ名の設定
const auto ClassName = TEXT("2024 framework ひな形");
const auto WindowName = TEXT("2024 framework ひな形(フィールド描画)");

HINSTANCE	GameProcess::hInst_ = nullptr;
HWND		GameProcess::hWnd_ = nullptr;
uint32_t	GameProcess::width_ = 0;
uint32_t	GameProcess::height_ = 0;

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
GameProcess::GameProcess(uint32_t width, uint32_t height)
	: game_manager_(nullptr)
{
	width_ = width;
	height_ = height;

	timeBeginPeriod(1);
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
GameProcess::~GameProcess(void)
{
	timeEndPeriod(1);
}

//--------------------------------------------------
// 起動処理
//--------------------------------------------------
bool GameProcess::StartUp(void)
{
	std::cout << "[ゲームプロセス] -> 起動\n";
	std::cout << "\n";

	return GameProcess::Init();
}

//--------------------------------------------------
// 実行処理
//--------------------------------------------------
void GameProcess::Run(void)
{
	// メッセージ
	MSG msg = {};

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER prevCount;
	QueryPerformanceCounter(&prevCount);

	int fpsCounter = 0;
	int fps = 0;	// 表示するfps
	DWORD lastTime = GetTickCount64();
#ifdef IMGUI_DEBUG
	ImGuiManager imGuiManager;
	ImGuiManager::staticPointer = &imGuiManager;
	Renderer* renderer = new Renderer;
	imGuiManager.ImGuiWin32Init(this->hWnd_);	// ImGuiのWin32APIを初期化
	imGuiManager.ImGuiD3D11Init(renderer->GetDevice(), renderer->GetDeviceContext());	// ImGuiのDirectX11を初期化
#endif
	//--------------------------------------------------
	// ゲームループ
	//--------------------------------------------------
	while (true)
	{
		// 新たにメッセージがあれば
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// ウィンドウプロシージャにメッセージを送る
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// 「WM_QUI」メッセージを受け取ったらループを抜ける
			if (msg.message == WM_QUIT) { break; }
		}
		else
		{
			LARGE_INTEGER currCount;
			QueryPerformanceCounter(&currCount);	// 現在時間を取得
			// 1/60	秒が経過したか?
			if (currCount.QuadPart >= prevCount.QuadPart + frequency.QuadPart / 60)
			{
#ifdef IMGUI_DEBUG
				imGuiManager.ImGuiUpdate();		// ImGuiの更新処理
				imGuiManager.ImGuiShowWindow();	// ImGuiのウィンドウを表示
#endif
				GameProcess::Update();
				GameProcess::GenerateOutput();

				fpsCounter++;
				prevCount = currCount;
			}
			// 毎秒FPSをウィンドウタイトルに反映
			DWORD currTime = GetTickCount64();
			if (currTime - lastTime >= 1000)	//	一秒ごとに更新
			{
				fps = fpsCounter;
				fpsCounter = 0;
				lastTime = currTime;

				// ウィンドウタイトルの更新
				std::string windowTitle = std::string(WindowName) + " - FPS:" + std::to_string(fps);
				SetWindowTextA(hWnd_, windowTitle.c_str());

			}
		}
	}
#ifdef IMGUI_DEBUG
	renderer->Uninit();
	delete renderer;
	imGuiManager.ImGuiUnInit();
#endif
}

//--------------------------------------------------
// 停止処理
//--------------------------------------------------
void GameProcess::ShutDown(void)
{
	std::cout << "[ゲームプロセス] -> 停止\n";

	GameProcess::Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
bool GameProcess::Init(void)
{
	std::cout << "[ゲームプロセス] -> ◆初期化処理開始◆\n";

	{
		// ウィンドウを生成
		InitWnd();

		// ゲームマネージャを生成
		game_manager_ = game_manager_->Create();
		if (false) { return false; }
	}
	std::cout << "[ゲームプロセス] -> ◇初期化処理終了◇\n";
	std::cout << "\n";

	return true;
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void GameProcess::Uninit(void)
{
	std::cout << "[ゲームプロセス] -> ◆終了処理開始◆\n";
	GameProcess::UninitWnd();
	std::cout << "[ゲームプロセス] -> ◇終了処理終了◇\n";
	std::cout << "\n";

}

//--------------------------------------------------
// ウィンドウの初期化処理
//--------------------------------------------------
bool GameProcess::InitWnd(void)
{
	std::cout << "[ゲームプロセス] -> ウィンドウ初期化開始\n";

	// インスタンスハンドルを取得
	auto hInst = GetModuleHandle(nullptr);
	if (hInst == nullptr) { return false; }

	// ウィンドウの設定
	WNDCLASSEX wc = {};
	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor = LoadCursor(hInst, IDC_ARROW);
	wc.hbrBackground = GetSysColorBrush(COLOR_BACKGROUND);
	wc.lpszMenuName = nullptr;
	wc.lpszClassName = ClassName;
	wc.hIconSm = LoadIcon(hInst, IDI_APPLICATION);

	// ウィンドウの登録
	if (!RegisterClassEx(&wc)) { return false; }

	// インスタンスハンドル設定
	hInst_ = hInst;
	
	// ウィンドウ巣のサイズを設定
	RECT rc = {};
	rc.right = static_cast<LONG>(width_);
	rc.bottom = static_cast<LONG>(height_);

	// ウィンドウのサイズを調整
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rc, style, FALSE);

	// ウィンドウを生成.
	hWnd_ = CreateWindowEx(
		0,
		//        WS_EX_TOPMOST,
		ClassName,
		WindowName,
		style,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		rc.right - rc.left,
		rc.bottom - rc.top,
		nullptr,
		nullptr,
		hInst_,
		nullptr);

	if (hWnd_ == nullptr)
	{
		return false;
	}

	// ウィンドウを表示.
	ShowWindow(hWnd_, SW_SHOWNORMAL);

	// ウィンドウを更新.
	UpdateWindow(hWnd_);

	// ウィンドウにフォーカスを設定.
	SetFocus(hWnd_);

	std::cout << "[ゲームプロセス] -> ウィンドウ初期化終了\n";

	// 正常終了.
	return true;
}

//--------------------------------------------------
// ウィンドウの終了処理
//--------------------------------------------------
void GameProcess::UninitWnd(void)
{
	std::cout << "[ゲームプロセス] -> ウィンドウ終了処理開始\n";

	// ウィンドウの登録を解除
	if(hInst_ != nullptr)
	{
		UnregisterClass(ClassName, hInst_);	
	}

	hInst_ = nullptr;
	hWnd_ = nullptr;

	std::cout << "[ゲームプロセス] -> ウィンドウ終了処理開始\n";
	std::cout << "\n";
}


//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void GameProcess::Update(void)
{
	// ゲームオブジェクトの更新
	game_manager_->UpdateAll();
}

//--------------------------------------------------
// 出力生成処理
//--------------------------------------------------
void GameProcess::GenerateOutput(void)
{
	// 出力生成
	game_manager_->GenerateOutputAll();
}

//--------------------------------------------------
// ウィンドウプロシージャ
//--------------------------------------------------
#ifdef IMGUI_DEBUG
// これがないとImGuiのウィンドウ操作ができない
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif
LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#ifdef IMGUI_DEBUG
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))	// これがないとImGuiのウィンドウ操作ができない
		return true;
#endif
	switch (uMsg)
	{
	case WM_DESTROY:	// ウィンドウ破棄メッセージ
	{
		PostQuitMessage(0);	// 「WM_QUIT」 メッセージを送る -> アプリ終了
	}
	break;

	case WM_CLOSE:	// 「x」ボタンが押されたら
	{
		int res = MessageBoxA(NULL, "おわります？", "確認", MB_OKCANCEL);
		if (res == IDOK)
		{
			DestroyWindow(hWnd);	// 「WM_DESTROY」メッセージを送る
		}
	}
	break;

	case WM_KEYDOWN:	// キー入力があったメッセージ
	{
		if (LOWORD(wParam) == VK_ESCAPE)	// 入力されたキーがESCなら
		{
			PostMessage(hWnd, WM_CLOSE, wParam, lParam);	// 「WM_CLOSE」を送る
		}
	}
	break;

	default:	// 受け取ったメッセージに対してデフォルトの処理を実行
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	}

	return 0;
}
