//==================================================
// [main.cpp] メインモジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：とてもメイン
//==================================================

/*----- インクルード -----*/
#include "StdAfx.h"
#include "GameProcess.h"

//--------------------------------------------------
// エントリポイント
//--------------------------------------------------
int main(void)
{
#if defined(DEBUG) || defined(_DEBUG)
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
#endif	// DEBUG || _DEBUG

		// アプリケーション実行
	GameProcess gp(SCREEN_WIDTH, SCREEN_HEIGHT);
	gp.StartUp();
	gp.Run();
	gp.ShutDown();

	return 0;
}
