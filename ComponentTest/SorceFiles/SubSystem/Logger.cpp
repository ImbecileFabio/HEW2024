//==================================================
// [Logger.h] デバッグログモジュール
// 著者：有馬啓太
//--------------------------------------------------
// 説明：でばっぐ
//==================================================

/*----- インクルード -----*/
#include "Logger.h"
#include "../StdAfx.h"

//--------------------------------------------------
// ログテキスト出力処理
//--------------------------------------------------
void Logger::Log(const std::string& message, LogLevel level)
{
	std::string levelStr;
	switch (level)
	{
	case LogLevel::Info: levelStr = "[INFO]"; break;
	case LogLevel::Warn: levelStr = "[WARN]"; break;
	case LogLevel::Error: levelStr = "[ERROR]"; break;
	}

	std::cout << levelStr << " " << message << std::endl;
}

//--------------------------------------------------
// 初期化処理
//--------------------------------------------------
void Logger::Initialize()
{
	std::cout << "[Logger] -> 初期化処理開始\n";

	AllocConsole();

	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stderr, "CONOUT$", "w", stdout);


	std::cout << "[Logger] -> 初期化処理終了\n";
}


//--------------------------------------------------
// 終了処理
//--------------------------------------------------
void Logger::Sutdown()
{
	std::cout << "[Logger] -> 解放処理開始\n";

	FreeConsole();

	std::cout << "[Logger] -> 解放処理終了\n";

}

//==================================================
//				End of FIle
//==================================================

