//==================================================
// [GameProcess.h] ゲーム実行処理モジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：ゲームの実行部分をまとめたクラスの定義
//==================================================

/*----- インクルード -----*/
#include "StdAfx.h"
#include "GameProcess.h"
#include "GameManager.h"
#include "Direct3D.h"
#include "SubSystem/Logger.h"


//--------------------------------------------------
// コンストラクタ
//--------------------------------------------------
GameProcess::GameProcess(HWND* _hWnd)
	: game_manager_(nullptr)
	, hWnd_(_hWnd)
{
}

//--------------------------------------------------
// デストラクタ
//--------------------------------------------------
GameProcess::~GameProcess(void)
{
}

//--------------------------------------------------
// 起動処理
//--------------------------------------------------
bool GameProcess::StartUp(void)
{
	std::cout << "[ゲームプロセス] -> 起動\n";
	std::cout << "\n";
	

	// 成功したかどうか
	bool is_init_success;

	is_init_success = GameProcess::Init();

	return is_init_success;
}

//--------------------------------------------------
// 実行処理
//--------------------------------------------------
void GameProcess::Run(void)
{
	std::cout << "[ゲームプロセス] -> 実行\n";
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
// 停止処理
//--------------------------------------------------
void GameProcess::ShutDown(void)
{
	GameProcess::Uninit();

	std::cout << "[ゲームプロセス] -> 停止\n";

}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
bool GameProcess::Init(void)
{
	std::cout << "[ゲームプロセス] -> ◆初期化処理開始◆\n";
	{
		game_manager_ = game_manager_->Create(hWnd_);
		if (false) { return false; }
	}
	std::cout << "[ゲームプロセス] -> ◇初期化処理終了◇\n";
	std::cout << "\n";

	return false;
}

//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void GameProcess::Uninit(void)
{
	std::cout << "[ゲームプロセス] -> ◆終了処理開始◆\n";
	{
		delete game_manager_;
	}


	std::cout << "[ゲームプロセス] -> ◇終了処理終了◇\n";
	std::cout << "\n";


}

//--------------------------------------------------
// 入力処理
//--------------------------------------------------
void GameProcess::ProcessInput(void)
{
	std::cout << "[ゲームプロセス] -> ◆入力処理開始◆\n";
	{
		game_manager_->InputAll();
	}
	std::cout << "[ゲームプロセス] -> ◇入力処理終了◇\n";
	std::cout << "\n";
}

//--------------------------------------------------
// 更新処理
//--------------------------------------------------
void GameProcess::Update(float deltaTime)
{
	std::cout << "[ゲームプロセス] -> ◆更新処理開始◆\n";
	{
		game_manager_->UpdateAll(deltaTime);
	}
	std::cout << "[ゲームプロセス] -> ◇更新処理終了◇\n";
	std::cout << "\n";

}

//--------------------------------------------------
// 出力生成処理
//--------------------------------------------------
void GameProcess::GenerateOutput(void)
{
	std::cout << "[ゲームプロセス] -> ◆出力生成処理開始◆\n";
	{
		game_manager_->GenerateOutputAll();
	}
	std::cout << "[ゲームプロセス] -> ◇出力生成処理終了◇\n";
	std::cout << "\n";
}
//==================================================
//				End of FIle
//==================================================