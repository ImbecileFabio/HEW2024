//==================================================
// [Logger.h] �f�o�b�O���O���W���[��
// ���ҁF�L�n�[��
//--------------------------------------------------
// �����F�ł΂���
//==================================================

/*----- �C���N���[�h -----*/
#include "Logger.h"
#include "../StdAfx.h"

//--------------------------------------------------
// ���O�e�L�X�g�o�͏���
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
// ����������
//--------------------------------------------------
void Logger::Initialize()
{
	std::cout << "[Logger] -> �����������J�n\n";

	AllocConsole();

	freopen_s((FILE**)stdout, "CONOUT$", "w", stdout);
	freopen_s((FILE**)stderr, "CONOUT$", "w", stdout);


	std::cout << "[Logger] -> �����������I��\n";
}


//--------------------------------------------------
// �I������
//--------------------------------------------------
void Logger::Sutdown()
{
	std::cout << "[Logger] -> ��������J�n\n";

	FreeConsole();

	std::cout << "[Logger] -> ��������I��\n";

}

//==================================================
//				End of FIle
//==================================================

