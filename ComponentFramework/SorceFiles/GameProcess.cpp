//==================================================
// [GameProcess.cpp] �Q�[�����s�������W���[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�Q�[���̎��s�������܂Ƃ߂��N���X�̒�`
//		 �E�B���h�E�̍쐬
//==================================================

/*----- �C���N���[�h -----*/
#include "StdAfx.h"
#include "GameProcess.h"
#include "GameManager.h"
#include "Renderer.h"
#define IMGUI_DEBUG	//ImGui���g���Ƃ��̓R�����g�A�E�g���O���Ƃ�����
#ifdef IMGUI_DEBUG
#include "ImGuiManager.h"
#endif
// �E�B���h�E�N���X�A�E�B���h�E���̐ݒ�
const auto ClassName = TEXT("2024 framework �ЂȌ`");
const auto WindowName = TEXT("2024 framework �ЂȌ`(�t�B�[���h�`��)");

HINSTANCE	GameProcess::hInst_ = nullptr;
HWND		GameProcess::hWnd_ = nullptr;
uint32_t	GameProcess::width_ = 0;
uint32_t	GameProcess::height_ = 0;

//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
GameProcess::GameProcess(uint32_t width, uint32_t height)
	: game_manager_(nullptr)
{
	width_ = width;
	height_ = height;

	timeBeginPeriod(1);
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
GameProcess::~GameProcess(void)
{
	timeEndPeriod(1);
}

//--------------------------------------------------
// �N������
//--------------------------------------------------
bool GameProcess::StartUp(void)
{
	std::cout << "[�Q�[���v���Z�X] -> �N��\n";
	std::cout << "\n";

	return GameProcess::Init();
}

//--------------------------------------------------
// ���s����
//--------------------------------------------------
void GameProcess::Run(void)
{
	// ���b�Z�[�W
	MSG msg = {};

	LARGE_INTEGER frequency;
	QueryPerformanceFrequency(&frequency);

	LARGE_INTEGER prevCount;
	QueryPerformanceCounter(&prevCount);

	int fpsCounter = 0;
	int fps = 0;	// �\������fps
	DWORD lastTime = GetTickCount64();
#ifdef IMGUI_DEBUG
	ImGuiManager imGuiManager;
	ImGuiManager::staticPointer = &imGuiManager;
	Renderer* renderer = new Renderer;
	imGuiManager.ImGuiWin32Init(this->hWnd_);	// ImGui��Win32API��������
	imGuiManager.ImGuiD3D11Init(renderer->GetDevice(), renderer->GetDeviceContext());	// ImGui��DirectX11��������
#endif
	//--------------------------------------------------
	// �Q�[�����[�v
	//--------------------------------------------------
	while (true)
	{
		// �V���Ƀ��b�Z�[�W�������
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			// �E�B���h�E�v���V�[�W���Ƀ��b�Z�[�W�𑗂�
			TranslateMessage(&msg);
			DispatchMessage(&msg);

			// �uWM_QUI�v���b�Z�[�W���󂯎�����烋�[�v�𔲂���
			if (msg.message == WM_QUIT) { break; }
		}
		else
		{
			LARGE_INTEGER currCount;
			QueryPerformanceCounter(&currCount);	// ���ݎ��Ԃ��擾
			// 1/60	�b���o�߂�����?
			if (currCount.QuadPart >= prevCount.QuadPart + frequency.QuadPart / 60)
			{
#ifdef IMGUI_DEBUG
				imGuiManager.ImGuiUpdate();		// ImGui�̍X�V����
				imGuiManager.ImGuiShowWindow();	// ImGui�̃E�B���h�E��\��
#endif
				GameProcess::Update();
				GameProcess::GenerateOutput();

				fpsCounter++;
				prevCount = currCount;
			}
			// ���bFPS���E�B���h�E�^�C�g���ɔ��f
			DWORD currTime = GetTickCount64();
			if (currTime - lastTime >= 1000)	//	��b���ƂɍX�V
			{
				fps = fpsCounter;
				fpsCounter = 0;
				lastTime = currTime;

				// �E�B���h�E�^�C�g���̍X�V
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
// ��~����
//--------------------------------------------------
void GameProcess::ShutDown(void)
{
	std::cout << "[�Q�[���v���Z�X] -> ��~\n";

	GameProcess::Uninit();
}

//--------------------------------------------------
// ����������
//--------------------------------------------------
bool GameProcess::Init(void)
{
	std::cout << "[�Q�[���v���Z�X] -> �������������J�n��\n";

	{
		// �E�B���h�E�𐶐�
		InitWnd();

		// �Q�[���}�l�[�W���𐶐�
		game_manager_ = game_manager_->Create();
		if (false) { return false; }
	}
	std::cout << "[�Q�[���v���Z�X] -> �������������I����\n";
	std::cout << "\n";

	return true;
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void GameProcess::Uninit(void)
{
	std::cout << "[�Q�[���v���Z�X] -> ���I�������J�n��\n";
	GameProcess::UninitWnd();
	std::cout << "[�Q�[���v���Z�X] -> ���I�������I����\n";
	std::cout << "\n";

}

//--------------------------------------------------
// �E�B���h�E�̏���������
//--------------------------------------------------
bool GameProcess::InitWnd(void)
{
	std::cout << "[�Q�[���v���Z�X] -> �E�B���h�E�������J�n\n";

	// �C���X�^���X�n���h�����擾
	auto hInst = GetModuleHandle(nullptr);
	if (hInst == nullptr) { return false; }

	// �E�B���h�E�̐ݒ�
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

	// �E�B���h�E�̓o�^
	if (!RegisterClassEx(&wc)) { return false; }

	// �C���X�^���X�n���h���ݒ�
	hInst_ = hInst;
	
	// �E�B���h�E���̃T�C�Y��ݒ�
	RECT rc = {};
	rc.right = static_cast<LONG>(width_);
	rc.bottom = static_cast<LONG>(height_);

	// �E�B���h�E�̃T�C�Y�𒲐�
	auto style = WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU;
	AdjustWindowRect(&rc, style, FALSE);

	// �E�B���h�E�𐶐�.
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

	// �E�B���h�E��\��.
	ShowWindow(hWnd_, SW_SHOWNORMAL);

	// �E�B���h�E���X�V.
	UpdateWindow(hWnd_);

	// �E�B���h�E�Ƀt�H�[�J�X��ݒ�.
	SetFocus(hWnd_);

	std::cout << "[�Q�[���v���Z�X] -> �E�B���h�E�������I��\n";

	// ����I��.
	return true;
}

//--------------------------------------------------
// �E�B���h�E�̏I������
//--------------------------------------------------
void GameProcess::UninitWnd(void)
{
	std::cout << "[�Q�[���v���Z�X] -> �E�B���h�E�I�������J�n\n";

	// �E�B���h�E�̓o�^������
	if(hInst_ != nullptr)
	{
		UnregisterClass(ClassName, hInst_);	
	}

	hInst_ = nullptr;
	hWnd_ = nullptr;

	std::cout << "[�Q�[���v���Z�X] -> �E�B���h�E�I�������J�n\n";
	std::cout << "\n";
}


//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void GameProcess::Update(void)
{
	// �Q�[���I�u�W�F�N�g�̍X�V
	game_manager_->UpdateAll();
}

//--------------------------------------------------
// �o�͐�������
//--------------------------------------------------
void GameProcess::GenerateOutput(void)
{
	// �o�͐���
	game_manager_->GenerateOutputAll();
}

//--------------------------------------------------
// �E�B���h�E�v���V�[�W��
//--------------------------------------------------
#ifdef IMGUI_DEBUG
// ���ꂪ�Ȃ���ImGui�̃E�B���h�E���삪�ł��Ȃ�
extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
#endif
LRESULT CALLBACK GameProcess::WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
#ifdef IMGUI_DEBUG
	if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))	// ���ꂪ�Ȃ���ImGui�̃E�B���h�E���삪�ł��Ȃ�
		return true;
#endif
	switch (uMsg)
	{
	case WM_DESTROY:	// �E�B���h�E�j�����b�Z�[�W
	{
		PostQuitMessage(0);	// �uWM_QUIT�v ���b�Z�[�W�𑗂� -> �A�v���I��
	}
	break;

	case WM_CLOSE:	// �ux�v�{�^���������ꂽ��
	{
		int res = MessageBoxA(NULL, "�����܂��H", "�m�F", MB_OKCANCEL);
		if (res == IDOK)
		{
			DestroyWindow(hWnd);	// �uWM_DESTROY�v���b�Z�[�W�𑗂�
		}
	}
	break;

	case WM_KEYDOWN:	// �L�[���͂����������b�Z�[�W
	{
		if (LOWORD(wParam) == VK_ESCAPE)	// ���͂��ꂽ�L�[��ESC�Ȃ�
		{
			PostMessage(hWnd, WM_CLOSE, wParam, lParam);	// �uWM_CLOSE�v�𑗂�
		}
	}
	break;

	default:	// �󂯎�������b�Z�[�W�ɑ΂��ăf�t�H���g�̏��������s
	{
		return DefWindowProc(hWnd, uMsg, wParam, lParam);
		break;
	}
	}

	return 0;
}
