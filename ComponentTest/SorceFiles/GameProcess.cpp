//==================================================
// [GameProcess.h] �Q�[�����s�������W���[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�Q�[���̎��s�������܂Ƃ߂��N���X�̒�`
//==================================================

/*----- �C���N���[�h -----*/
#include "StdAfx.h"
#include "GameProcess.h"
#include "GameManager.h"
#include "Direct3D.h"
#include "SubSystem/Logger.h"


//--------------------------------------------------
// �R���X�g���N�^
//--------------------------------------------------
GameProcess::GameProcess(HWND* _hWnd)
	: game_manager_(nullptr)
	, hWnd_(_hWnd)
{
}

//--------------------------------------------------
// �f�X�g���N�^
//--------------------------------------------------
GameProcess::~GameProcess(void)
{
}

//--------------------------------------------------
// �N������
//--------------------------------------------------
bool GameProcess::StartUp(void)
{
	std::cout << "[�Q�[���v���Z�X] -> �N��\n";
	std::cout << "\n";
	

	// �����������ǂ���
	bool is_init_success;

	is_init_success = GameProcess::Init();

	return is_init_success;
}

//--------------------------------------------------
// ���s����
//--------------------------------------------------
void GameProcess::Run(void)
{
	std::cout << "[�Q�[���v���Z�X] -> ���s\n";
	std::cout << "\n";

	float deltaTime;

	while (true)
	{
		if (true)
			deltaTime = 1.f / 60.f;

		GameProcess::ProcessInput();
		GameProcess::Update(deltaTime);
		GameProcess::GenerateOutput();
		if (true) { break; }
	}
}

//--------------------------------------------------
// ��~����
//--------------------------------------------------
void GameProcess::ShutDown(void)
{
	GameProcess::Uninit();

	std::cout << "[�Q�[���v���Z�X] -> ��~\n";

}

//--------------------------------------------------
// ����������
//--------------------------------------------------
bool GameProcess::Init(void)
{
	std::cout << "[�Q�[���v���Z�X] -> �������������J�n��\n";
	{
		game_manager_ = game_manager_->Create(hWnd_);
		if (false) { return false; }
	}
	std::cout << "[�Q�[���v���Z�X] -> �������������I����\n";
	std::cout << "\n";

	return false;
}

//--------------------------------------------------
// �I������
//--------------------------------------------------
void GameProcess::Uninit(void)
{
	std::cout << "[�Q�[���v���Z�X] -> ���I�������J�n��\n";
	{
		delete game_manager_;
	}


	std::cout << "[�Q�[���v���Z�X] -> ���I�������I����\n";
	std::cout << "\n";


}

//--------------------------------------------------
// ���͏���
//--------------------------------------------------
void GameProcess::ProcessInput(void)
{
	std::cout << "[�Q�[���v���Z�X] -> �����͏����J�n��\n";
	{
		game_manager_->InputAll();
	}
	std::cout << "[�Q�[���v���Z�X] -> �����͏����I����\n";
	std::cout << "\n";
}

//--------------------------------------------------
// �X�V����
//--------------------------------------------------
void GameProcess::Update(float deltaTime)
{
	std::cout << "[�Q�[���v���Z�X] -> ���X�V�����J�n��\n";
	{
		game_manager_->UpdateAll(deltaTime);
	}
	std::cout << "[�Q�[���v���Z�X] -> ���X�V�����I����\n";
	std::cout << "\n";

}

//--------------------------------------------------
// �o�͐�������
//--------------------------------------------------
void GameProcess::GenerateOutput(void)
{
	std::cout << "[�Q�[���v���Z�X] -> ���o�͐��������J�n��\n";
	{
		game_manager_->GenerateOutputAll();
	}
	std::cout << "[�Q�[���v���Z�X] -> ���o�͐��������I����\n";
	std::cout << "\n";
}
//==================================================
//				End of FIle
//==================================================