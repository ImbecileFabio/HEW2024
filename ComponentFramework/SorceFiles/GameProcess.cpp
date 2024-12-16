//==================================================
// [GameProcess.cpp] ゲーム実行処理モジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ゲームの実行部分をまとめたクラスの定義
//		 ウィンドウの作成
//==================================================

/*----- インクルード -----*/
#include <Windows.h>
#include <iostream>
#include <format>
#include <string>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")

#include "GameManager.h"
#include "GameProcess.h"
#include "Renderer.h"
#include "InputManager.h"

#define IMGUI_DEBUG	//ImGuiを使うときはコメントアウトを外すといける
#ifdef IMGUI_DEBUG
#include "ImGuiManager.h"
#endif
// ウィンドウクラス、ウィンドウ名の設定
const auto ClassName = TEXT("2024 framework ひな形");
const auto WindowName = TEXT("2024 framework ひな形(フィールド描画)");

// ↓fullscreen設定	コメントを外すとフルスクリーンになる
// #define FULLSCREEN_MODE_

HINSTANCE	GameProcess::hInst_ = nullptr;
HWND		GameProcess::hWnd_ = nullptr;
uint32_t	GameProcess::width_ = 0;		// 画面サイズはmain.cppで設定
uint32_t	GameProcess::height_ = 0;

//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
GameProcess::GameProcess(uint32_t _width, uint32_t _height)
	: game_manager_(nullptr)
{
	width_ = _width;
	height_ = _height;

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
	std::cout << std::format("[GameProcess] -> StartUp\n\n");

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
	DWORD lastTime = static_cast<DWORD>(GetTickCount64());
#ifdef IMGUI_DEBUG
	ImGuiManager imGuiManager;
	ImGuiManager::staticPointer = &imGuiManager;
	imGuiManager.ImGuiWin32Init(this->hWnd_);	// ImGuiのWin32APIを初期化
	imGuiManager.ImGuiD3D11Init(this->game_manager_->GetRenderer()->GetDevice(),
		this->game_manager_->GetRenderer()->GetDeviceContext());	// ImGuiのDirectX11を初期化
	imGuiManager.ImGuiInit();
#endif
	//--------------------------------------------------
	// ゲームループ
	//--------------------------------------------------
	while (true)
	{
		std::cout << std::format("[ GameLoop_Start ]\n");

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
				imGuiManager.ImGuiUpdate();
#endif

				InputManager::GetInstance().Update();	// InputManagerの更新

				GameProcess::Update();					// ゲームの更新処理
				GameProcess::GenerateOutput();			// ゲームの描画処理

				fpsCounter++;
				prevCount = currCount;
			}
			// 毎秒FPSをウィンドウタイトルに反映
			DWORD currTime = static_cast<DWORD>(GetTickCount64());
			if (currTime - lastTime >= 1000)	//	一秒ごとに更新
			{
				fps = fpsCounter;
				fpsCounter = 0;
				lastTime = currTime;

				// ウィンドウタイトルの更新
				std::string windowTitle = std::format("{} - FPS:{}", WindowName, fps);
				SetWindowTextA(hWnd_, windowTitle.c_str());

			}
		}

		std::cout << std::format("[ GameLoop_End ]\n");
	}
#ifdef IMGUI_DEBUG
	imGuiManager.ImGuiUnInit();
#endif
}

//--------------------------------------------------
// 停止処理
//--------------------------------------------------
void GameProcess::ShutDown(void)
{
	std::cout << std::format("[GameProcess] -> ShutDown\n");

	GameProcess::Uninit();
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
bool GameProcess::Init(void)
{
	std::cout << std::format("[GameProcess] -> ◆Init Start◆\n");

	{
		// ウィンドウを生成
		InitWnd();

		// ゲームマネージャを生成
		game_manager_ = game_manager_->Create();
		assert(game_manager_);
	}
	std::cout << std::format("[GameProcess] -> ◇Init Finish◇\n");

	return true;
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void GameProcess::Uninit(void)
{
	std::cout << std::format("[GameProcess] -> ◆Uninit Start◆\n");

	// ゲームマネージャの破棄
	if (game_manager_ != nullptr)
	{
		delete game_manager_;
		game_manager_ = nullptr;
	}

	GameProcess::UninitWnd();
	
	std::cout << std::format("[GameProcess] -> ◇Uninit Finish◇\n\n");
}

//--------------------------------------------------
// ウィンドウの初期化処理
//--------------------------------------------------
bool GameProcess::InitWnd(void)
{
	std::cout << std::format("[GameProcess] -> InitWnd Start\n");

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

#ifdef FULLSCREEN_MODE_
	// ウィンドウスタイルを変更
	SetWindowLong(hWnd_, GWL_STYLE, WS_POPUP);
	// ウィンドウサイズを画面いっぱいに
	SetWindowPos(hWnd_, HWND_TOP, 0, 0, width_, height_, SWP_SHOWWINDOW);
#endif	// FULLSCREEN_MODE_

	// ウィンドウの登録
	if (!RegisterClassEx(&wc)) { return false; }

	// インスタンスハンドル設定
	hInst_ = hInst;
	
	// ウィンドウのサイズを設定
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

	assert(hWnd_);

	// ウィンドウを表示.
	ShowWindow(hWnd_, SW_SHOWNORMAL);

	// ウィンドウを更新.
	UpdateWindow(hWnd_);

	// ウィンドウにフォーカスを設定.
	SetFocus(hWnd_);

	std::cout << std::format("[GameProcess] -> InitWnd Finish\n");

	// 正常終了.
	return true;
}

//--------------------------------------------------
// ウィンドウの終了処理
//--------------------------------------------------
void GameProcess::UninitWnd(void)
{
	std::cout << std::format("[GameProcess] -> UninitWnd Start\n");

	// ウィンドウの登録を解除
	if(hInst_ != nullptr)
	{
		UnregisterClass(ClassName, hInst_);	
	}

	hInst_ = nullptr;
	hWnd_ = nullptr;

	std::cout << std::format("[GameProcess] -> UninitWnd Finish\n\n");
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
		int res = MessageBoxA(NULL, "owaowari", "確認", MB_OKCANCEL);
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
